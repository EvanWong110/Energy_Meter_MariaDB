/* Nome do arquivo: Core.ino
 * Este é o arquivo main() que possui o setup e o loop principal do programa
 * 
 * Feito por Cristian Fernando Ritter
 * Para o trabalho de conclusão de curso de Engenharia Mecatrônica IfSC - Florianópolis
 * Todos os direitos reservados
 */

#include <ESP8266WiFi.h>      // Bibliote de suporte a wifi do módulo ESP8266
#include <SPI.h>              // Biblioteca de suporte a comunicação SPI
#include "SSD1306Wire.h"      // Bibliote de suporte ao Display OLED
#include <time.h>             // Biblioteca com funções relacionadas a fuso horário
#include "ADE7753CR.h"
#include "OLEDCR.h"
#include "publisher.h"

#define SDA_PIN      D1                 // display Pin
#define SCK_PIN      D2                 // display Pin
#define LEDPIN       D3
#define SW_DISPLAY   D4              // Chave para mudança de tela
#define CSPIN        D8                  // SPI Pin
#define $id "0"
#define time_between_uploads 7000 //ms                        // Tempo entre uploads
#define debaunce_time 250                                      // Debaunce da chave do display
#define serial_speed 115200        // Serial port speed


const char* ssid = "Home";         // WiFi network name
const char* wifi_password = "07111993"; // WiFi network password
char* mqtt_server = "192.168.000.251";  // IP of the MQTT broker
const char* mqtt_username = "energymeter"; // MQTT username
const char* mqtt_password = "energymeter"; // MQTT password
const char* clientID = "client_livingroom"; // MQTT client ID
const char* ntp_primary = "pool.ntp.org";     // Servidores de fuso horário
const char* ntp_secondary = "time.nist.gov";
//const int columns_number=9;
unsigned long last_upload_time = 0;         // Uso interno nos threads
unsigned long last_debaunce_time = 0;              
char msg_to_publish[1000];                 // Armazena a string a ser enviada para o broker
unsigned long status_register = 0;         // Armazena o valor do registrador de status do ADE
int display_current_view = 0;              // Armazena a informacao da tela apresentada no display

ADE7753 ADE7753;
OLED OLED;
ADE7753::Measurement atual;
SSD1306Wire display(0x3c, SDA_PIN, SCK_PIN);
PubSubClient client(mqtt_server, 1883, wifiClient); 
WiFiClient wifiClient;
Publisher Publisher;

void connect_WIFI(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_MQTT(){
  while (!client.connect(clientID, mqtt_username, mqtt_password)) {
     Serial.println("Connecting to MQTT Broker!");
  }
}

boolean threadTo(unsigned long* last_time, unsigned long default_time) {  //cria rotinas que rodam a cada ciclo de tempo especifico
    long now = millis();
    if (now - *last_time > default_time) {
        *last_time = now;
        return true;
    }  
    else 
        return false;  
}
long setClock() {        // Set time via NTP, as required for x.509 validation  
  configTime(0 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
  }
  Serial.println("Done.");
  return now;  
}

void ler_serial(char * received){
   char message[100];
   int charsRead = 0;
   if (Serial.available() > 0) {      // Is the Serial object sending something?
      charsRead = Serial.readBytesUntil('\n', message, sizeof(message) - 1);   // Yep, so read it...
      message[charsRead] = '\0';                        // Now make it a C string...
      strcpy(received, message);
      Serial.print("Comando recebido: ");
      Serial.println(received);
      }
   }


void piscaled(int quantidade, int tempo){
  int i;
  for (i=0; i<quantidade; i++){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LEDPIN, LOW);
    delay(tempo);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LEDPIN, HIGH);
    delay(tempo);
  }
}

void CheckSerial(){
   if (Serial.available()) {
      char received[100] = "";
      ler_serial(received);
      Serial.println("SELECIONE UMA OPCAO:");
      Serial.println("1 - ");
      Serial.println("2 - ");
      Serial.println("3 - ");
      Serial.println("4 - ");
      Serial.println("5 - "); 
      while(!Serial.available()){}
      ler_serial(received);
      switch ((int) received)
      {
      case 1:
         /* code */
         break;
      case 2:
         /* code */
         break;
      case 3:
         /* code */
         break;
      case 4:
         /* code */
         break;
      case 5:
         /* code */
         break; 
      default:
         break;
      }
   }
}
        
void setup()
{
  Serial.begin(9600);            // Inicia comunicação Serial.
//  displayInit();                         // Inicializa displayOLED
  connect_WIFI();
  connect_MQTT();
  setClock();                            // atualiza hora do sistema (para a autenticar o certificado e gerar o timestamp)
  pinMode(SW_DISPLAY, INPUT);            
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  ADE7753.Init(CSPIN);
}

void loop() {
   if (!digitalRead(SW_DISPLAY) && threadTo(&last_debaunce_time, debaunce_time)) {      
      display_current_view++;       
//      displayUpdate(&display_current_view);                 // Muda tela do display
      ADE7753.DisplayBufferCreator(1, atual); //salva dados no buffer "Parameter=value"
      OLED.ShowCompleteView(display, &atual.display_buffer);  //shows buffer content on display 
   }

   if (threadTo(&last_upload_time, time_between_uploads)) {         // Faz upload das informações mais recentes
      piscaled(2, 50);
      //  strcpy(atual.id, $id);
      atual.voltage = ADE7753.ReadVRMS();
      atual.timestamp = setClock();
   //  displayUpdate(&display_current_view);
      Publisher.CreateMessage(atual);
      Publisher.PublishMessage(client);
   }

//    resetastatus();
}
