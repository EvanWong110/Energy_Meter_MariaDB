 /* Nome do arquivo: Core.ino
 * Este é o arquivo main() que possui o setup e o loop principal do programa
 * 
 * Feito por Cristian Fernando Ritter
 * Para o trabalho de conclusão de curso de Engenharia Mecatrônica IfSC - Florianópolis
 * Todos os direitos reservados
 */

#include <ESP8266WiFi.h>      
#include <time.h>             
#include <math.h>
#include "ADE7753CR.h"
#include "OLEDCR.h"
#include "PUBLISHERCR.h"
#include "SERIALCR.h"

#define SDA_PIN D1  // OLED SDA Pin
#define SCK_PIN D2  // OLED SCK Pin
#define LED_EXTERNAL D3  
#define SW_PIN D4  // Display change views
#define CSPIN D8  // ADE7753 SPI Enable Pin
#define time_between_uploads 7000 //ms                        // Tempo entre uploads
#define debaunce_time 250                                      // Debaunce da chave do display
#define serial_speed 115200        // Serial port speed

const char* ssid = "Home";         // WiFi network name
const char* wifi_password = "07111993"; // WiFi network password
char* mqtt_server = "192.168.000.251";  // IP of the MQTT broker
const char* mqtt_username = "energymeter"; // MQTT username
const char* mqtt_password = "energymeter"; // MQTT password
const char* mqtt_topic = "home/energymeter";
char* dev_id = "0";
char* dev_abstract = "Cristian's Bedroom";
const char* clientID = "client_livingroom"; // MQTT client ID
const char* ntp_primary = "pool.ntp.org";     // Servidores de fuso horário
const char* ntp_secondary = "time.nist.gov";
unsigned long last_upload_time = 0;         // Uso interno nos threads
boolean offline_mode = false;
int ind = 0;
char display_buffer;

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 
SSD1306Wire display(0x3c, SDA_PIN, SCK_PIN);
OLED OLED;
ADE7753 ADE7753;
ADE7753::Measurement buff[200];
ADE7753::Measurement* atual;
Publisher Publisher;
Serials Serials;

//cria rotinas que rodam a cada ciclo de tempo especifico 
boolean threadTo(unsigned long* last_time, unsigned long default_time){ 
   unsigned long now = millis();
   if (now - *last_time > default_time) {
      *last_time = now;
      return true;
   }  
   else 
      return false;  
}

unsigned long setClock() { 
  configTime(0 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Getting NTP time sync... ");
  time_t now = time(nullptr);
  return now;  
}

void piscaled(int quantidade, int tempo){
  int i;
  for (i=0; i<quantidade; i++){
    digitalWrite(LED_EXTERNAL, LOW);
    delay(tempo);
    digitalWrite(LED_EXTERNAL, HIGH);
    delay(tempo);
  }
}
        
void setup(){
  Serial.begin(9600);            // Inicia comunicação Serial.
  WiFi.begin(ssid, wifi_password);
  pinMode(SW_PIN, INPUT);            
  pinMode(LED_EXTERNAL, OUTPUT);
  ADE7753.Init(CSPIN);
  OLED.Init(&display);
  atual = &buff[0];
}

void loop() {
    //verify internet connection
    if ( (WiFi.status() != WL_CONNECTED) || !client.connect(clientID, mqtt_username, mqtt_password) ){
        offline_mode = true;  
    }
    else{
        offline_mode = false;  
    }
   
    //Serial Received Verify
    if (Serial.available()){
      Serials.ExecutaComandoSerial(&ADE7753);
    }

    atual->voltage = ADE7753.ReadVRMS()*598.5;  //fator reducao do trafo + divisores de tensao
    atual->current = ADE7753.ReadIRMS()*20.09;  //fator reducao do sensor usado
    atual->aparent_power = atual->current * atual->voltage;
    atual->frequency = 1/(ADE7753.ReadPERIOD(3579545));
    ADE7753.ReadEnergy(120, &atual->FP);
    atual->active_power = atual->aparent_power * atual->FP;
    atual->reactive_power = atual->aparent_power * sin(acos(atual->FP));

    ADE7753.DisplayBufferUpdate((atual), (&display_buffer), ADE7753.GetDisplayPosition(), !digitalRead(SW_PIN)); //salva dados no buffer "Parameter=value"
    OLED.ShowCompleteView(&display, &display_buffer);  //shows buffer content on display 

   //Payload Upload
      if (threadTo(&last_upload_time, time_between_uploads)) {         
            Serial.println(ind);
            piscaled(1, 100);
            atual->timestamp = setClock();
            if (!offline_mode){
                while (ind > 0){
                    Publisher.PublishMessage(dev_id, dev_abstract, *atual, &client, mqtt_topic);
                    ind--;
                    atual = &buff[ind];
                }
                Publisher.PublishMessage(dev_id, dev_abstract, *atual, &client, mqtt_topic);
            }
            else 
            {
                ind++;
                atual = &buff[ind];
            }
      }
}
