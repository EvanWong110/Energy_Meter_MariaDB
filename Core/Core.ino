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
#include <PubSubClient.h>     // Biblioteca para publicacao MQTT na AWS
#include "ADE7753CR.h"

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



SSD1306Wire display(0x3c, SDA_PIN, SCK_PIN);
ADE7753 ADE7753;
ADE7753::Measurement atual;
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 

void connect_WIFI(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  display_msg("Inicializando...");
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

void displayInit(){                 //Inicializa o display
  display.init();
  display.flipScreenVertically();
  display.clear();
}

void display_msg(String texto){     // Envia mensagens diversas para o display
  display.clear();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString((display.getWidth()/2), (display.getHeight()/2), texto);
  display.display();
}

void displayUpdate(int * current_view){                                      // Atualiza dados do display  
  display.clear();                                                                                
  display.setTextAlignment(TEXT_ALIGN_CENTER);                                                    
  display.setFont(ArialMT_Plain_16);                                                              
  display.drawRect(0, 0, display.getWidth(), display.getHeight());               // Retangulo principal borda branca
  display.fillRect(0, 0, display.getWidth(), (display.getHeight()/2)-8);         // Retangulo interno preenchimento branco
  char parametro[20], medicao[20];
  switch(* current_view){
    case 0:
        strcpy(parametro, "Tensão");
        sprintf(medicao, "%.2f V",atual.voltage);
    break;
    case 1:
        strcpy(parametro, "Corrente");
        sprintf(medicao, "%.2f A",atual.current);
    break;
    case 2:
        strcpy(parametro, "Pot. AT");
        sprintf(medicao, "%.2f W",atual.active_power);
    break;
    case 3:
        strcpy(parametro, "Pot. RE");
        sprintf(medicao, "%.2f VAr",atual.reactive_power);
    break;
    case 4:
        strcpy(parametro, "Pot. AP");
        sprintf(medicao, "%.2f VA",atual.aparent_power);
    break;
    case 5:
        strcpy(parametro, "ID");
        sprintf(medicao, "%s",atual.id);
    break;
    case 6:
        strcpy(parametro, "FREQ");
        sprintf(medicao, "%.2f Hz",atual.frequency);    
    break;
    case 7:
        strcpy(parametro, "FP");
        sprintf(medicao, "%.2f",atual.FP);    
    break;
    default:
    * current_view = 0;
  }
  display.setColor(BLACK);                                                       
  display.drawString((display.getWidth()/2),5,parametro);   // Imprime o nome do parametro
  display.setColor(WHITE);                                                       
  display.drawString((display.getWidth()/2),(display.getHeight()/2), medicao); // Imprime o valor com a unidade de medida
  display.display();
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

void createMessage(char * msg_to_publish, ADE7753::Measurement atual) {
Serial.println("Creating message: ");
char buff[1000] = "";
int ponteiro;
int soma_ponteiros = 0;
ponteiro = snprintf(buff, 50, "{\n");
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"id\" : \"%s\",\n", atual.id);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"timestamp\" : \"%d\",\n", atual.timestamp);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"tensao\" : \"%f\",\n", atual.voltage);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"corrente\" : \"%f\",\n", atual.current);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"frequencia\" : \"%f\",\n", atual.frequency);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_at\" : \"%f\",\n", atual.active_power);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_re\" : \"%f\",\n", atual.reactive_power);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_ap\" : \"%f\",\n", atual.aparent_power);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"FP\" : \"%f\"\n", atual.FP);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "}");
strcpy(msg_to_publish, buff);
}

void publish_message(char* msg_to_publish){   
    Serial.print("Publishing message: ");
    Serial.println(msg_to_publish);
    client.beginPublish("home/energymeter", String(msg_to_publish).length(), false);
    client.print(msg_to_publish);
    client.endPublish();
    Serial.println("");
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
  displayInit();                         // Inicializa displayOLED
  display.drawString(0, 0, "Inicializando");
  display.display();
  delay(1000);
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
      displayUpdate(&display_current_view);                 // Muda tela do display
   }

   if (threadTo(&last_upload_time, time_between_uploads)) {         // Faz upload das informações mais recentes
      piscaled(2, 50);
      //  strcpy(atual.id, $id);
      atual.voltage = ADE7753.ReadVRMS();
      atual.timestamp = setClock();
      displayUpdate(&display_current_view);
      createMessage(msg_to_publish, atual);
      publish_message(msg_to_publish);
   }
//    resetastatus();
}
