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

#define SDA_PIN      D1  // OLED SDA Pin
#define SCK_PIN      D2  // OLED SCK Pin
#define LED_EXTERNAL  D3  
#define SW_DISPLAY   D4  // Display change views
#define CSPIN        D8  // ADE7753 SPI Enable Pin
#define time_between_uploads 7000 //ms                        // Tempo entre uploads
#define debaunce_time 250                                      // Debaunce da chave do display
#define serial_speed 115200        // Serial port speed

const char* ssid = "Home";         // WiFi network name
const char* wifi_password = "07111993"; // WiFi network password
char* mqtt_server = "192.168.000.251";  // IP of the MQTT broker
const char* mqtt_username = "energymeter"; // MQTT username
const char* mqtt_password = "energymeter"; // MQTT password
const char* mqtt_topic = "home/energymeter";
const char* clientID = "client_livingroom"; // MQTT client ID
const char* ntp_primary = "pool.ntp.org";     // Servidores de fuso horário
const char* ntp_secondary = "time.nist.gov";
unsigned long last_upload_time = 0;         // Uso interno nos threads
unsigned long last_debaunce_time = 0;              

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
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
  }
  return now;  
}

void piscaled(int quantidade, int tempo){
  int i;
  for (i=0; i<quantidade; i++){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_EXTERNAL, LOW);
    delay(tempo);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_EXTERNAL, HIGH);
    delay(tempo);
  }
}
        
void setup(){
//  Serial.begin(9600);            // Inicia comunicação Serial.
  WiFi.begin(ssid, wifi_password);
  pinMode(SW_DISPLAY, INPUT);            
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_EXTERNAL, OUTPUT);
  ADE7753.Init(CSPIN);
}

void loop() {
   //WIFI Connecting
    while (WiFi.status() != WL_CONNECTED) {
         Serial.print("Connecting to ");
         Serial.println(ssid);
         delay(500);
         if (WiFi.status() == WL_CONNECTED){
            Serial.print("IP: ");
            Serial.println(WiFi.localIP());
         }
    }
   
    //MQTT Connecting
    while (!client.connect(clientID, mqtt_username, mqtt_password)) {
        Serial.println("Connecting to MQTT Broker...");
    }

    //Serial Received Verify
    if (Serial.available()){
      Serials.ExecutaComandoSerial();
    }

   //Display View Update
   if (!digitalRead(SW_DISPLAY) && threadTo(&last_debaunce_time, debaunce_time)) {      
      ADE7753.DisplayBufferCreator(1, &atual); //salva dados no buffer "Parameter=value"
      OLED.ShowCompleteView(display, atual.display_buffer);  //shows buffer content on display 
   }

   //Payload Upload
   if (threadTo(&last_upload_time, time_between_uploads)) {         
      piscaled(1, 10);
      atual.voltage = ADE7753.ReadVRMS();
      atual.timestamp = setClock();
      Publisher.CreateMessage(atual);
      Publisher.PublishMessage(&client, mqtt_topic);
   }
}
