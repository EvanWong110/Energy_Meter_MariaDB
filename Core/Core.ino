 /* Nome do arquivo: Core.ino
 * Este é o arquivo main() que possui o setup e o loop principal do programa
 * 
 * Feito por Cristian Fernando Ritter
 * Para o trabalho de conclusão de curso de Engenharia Mecatrônica IfSC - Florianópolis
 * Todos os direitos reservados
 */

#include <ESP8266WiFi.h>      
#include <time.h>             
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
const char* dev_id = "0";
const char* dev_abstract = "Cristian's Bedroom";
const char* clientID = "client_livingroom"; // MQTT client ID
const char* ntp_primary = "pool.ntp.org";     // Servidores de fuso horário
const char* ntp_secondary = "time.nist.gov";
unsigned long last_upload_time = 0;         // Uso interno nos threads
unsigned long last_debaunce_time = 0;              
boolean offline_mode = false;

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 
SSD1306Wire display(0x3c, SDA_PIN, SCK_PIN);
OLED OLED;
ADE7753 ADE7753;
ADE7753::Measurement atual;
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
  Serial.print("Getting NTP time sync... ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
  }
  Serial.println(" OK");
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
  delay(2000);
  if (digitalRead(SW_PIN) == LOW){
    offline_mode = true;  //allows offline tests
    Serial.println(digitalRead(SW_PIN));
  }
}

void loop() {
    while (WiFi.status() != WL_CONNECTED) {
         if (offline_mode) break;
         Serial.print("Connecting to ");
         Serial.print(ssid);
         Serial.println("...");
         delay(1000);
         if (WiFi.status() == WL_CONNECTED){
            Serial.print("IP: ");
            Serial.println(WiFi.localIP());
         }
    }
   
    //MQTT Connecting
    while (!client.connect(clientID, mqtt_username, mqtt_password)) {
        if (offline_mode) break;
        Serial.println("Connecting to MQTT Broker...");
    }

    //Serial Received Verify
    if (Serial.available()){
      Serials.ExecutaComandoSerial(&ADE7753);
    }

   //Display View Update
   if (!digitalRead(SW_PIN) && threadTo(&last_debaunce_time, debaunce_time)) {      
      ADE7753.DisplayBufferCreator(&atual, ADE7753.GetDisplayPosition()); //salva dados no buffer "Parameter=value"
      OLED.ShowCompleteView(&display, atual.display_buffer);  //shows buffer content on display 
   }

   //Payload Upload
   if (threadTo(&last_upload_time, time_between_uploads)) {         
      piscaled(1, 100);
      atual.voltage = ADE7753.ReadVRMS();
      atual.current = ADE7753.ReadIRMS();
      strcpy(atual.dev_id, dev_id);
      strcpy(atual.dev_abstract, dev_abstract);
      if (!offline_mode){
          atual.timestamp = setClock();
      }
      Publisher.CreateMessage(atual);
      if (!offline_mode){
            Publisher.PublishMessage(&client, mqtt_topic);
      }
   }
}
