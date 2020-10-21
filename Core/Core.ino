/* Nome do arquivo: Core.ino
 * Este é o arquivo main() que possui o setup e o loop principal do programa
 * 
 * Feito por Cristian Fernando Ritter
 * Para o trabalho de conclusão de curso de Engenharia Mecatrônica IfSC - Florianópolis
 * Todos os direitos reservados
 */
//#define CS_PIN D8                  // SPI Pin

#include <ESP8266WiFi.h>      // Bibliote de suporte a wifi do módulo ESP8266
#include <SPI.h>              // Biblioteca de suporte a comunicação SPI
#include "SSD1306Wire.h"      // Bibliote de suporte ao Display OLED
#include <time.h>             // Biblioteca com funções relacionadas a fuso horário
#include <PubSubClient.h>     // Biblioteca para publicacao MQTT na AWS
//#include "funcoes_ADE7753.h"  // funcões dos registradores ADE7753
#include "ADE7753CR.h"

ADE7753 ADE7753;


typedef struct {
    char id[20] = "0";
    long timestamp = 0;
    float tensao = 0;
    float corrente = 0;
    float frequencia = 0;
    float pot_at = 0;
    float pot_re = 0;
    float pot_ap = 0;
    float FP = 0;
    bool sobretensao = 0;
    bool sobrecorrente = 0;
    bool crossing_timeout = 0;
    bool pot_positiva = 0;
} mensagem;

mensagem atual;


#include "funcoes_OLED.h"
#include "Config.h"           // Arquivo com diversas definicoes do sketch

void setup()
{
  Serial.begin(9600);            // Inicia comunicação Serial.
  displayInit();                         // Inicializa displayOLED
  display.drawString(0, 0, "testando");
  display.display();
  delay(1000);
  connect_WIFI();
  connect_MQTT();
  setClock();                            // atualiza hora do sistema (para a autenticar o certificado e gerar o timestamp)
  pinMode(SW_DISPLAY, INPUT);            
//  pinMode(CS_PIN,OUTPUT);                
//  digitalWrite(CS_PIN, HIGH);            // habilita comunicação no ADE7753 - disabled by default
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  SPI.begin();                           // Inicia comunicação SPI
//  configADE();                           // Configura registradores do ADE7753

ADE7753.Init(D8);
}

unsigned long last_upload_time = 0;         // Uso interno nos threads
unsigned long last_debaunce_time = 0;              

char msg_to_publish[1000];                 // Armazena a string a ser enviada para o broker
unsigned long status_register = 0;         // Armazena o valor do registrador de status do ADE
int display_current_view = 0;              // Armazena a informacao da tela apresentada no display

void verificar_comando_serial(){
   if (Serial.available()) {
      char user_command[100] = "";
      String arg1, arg2, arg3;
      ler_serial(user_command);
      
      if (!strcmp(user_command, "regconfig")){
         int i;
         Serial.println("Aguardando comando...");
         Serial.println("Ex. write16,0x01,0000111100001111");
         while(!Serial.available()){}
         ler_serial(user_command);     
         arg1 = (getValue(user_command,',',0));
         arg2 = (getValue(user_command,',',1));
         arg3 = (getValue(user_command,',',2));
         
         char reg[20];
         arg2.toCharArray(reg, sizeof(reg));
         long int reg_int = strtol(reg, 0, 16);
         char value[30];
         arg3.toCharArray(value, sizeof(value));
         long int value_int = strtol(value, 0, 2);
                  
         if (arg1 == "write16"){
//             write16(reg_int, value_int);
         }
         if (arg1 == "write8"){
//             write8(reg_int, value_int);
         }
         if (arg1 == "read24"){
//             Serial.print(registers[reg_int-1]);
             Serial.print(" => ");
//             Serial.println(read24(reg_int),BIN);
         }
         if (arg1 == "read16"){
//             Serial.print(registers[reg_int-1]);
             Serial.print(" => ");
//             Serial.println(read16(reg_int),BIN);
         }
         if (arg1 == "read8"){
//            Serial.print(registers[reg_int-1]);
            Serial.print(" => ");
//            Serial.println(read8(reg_int),BIN);
         }

      }
      if (!strcmp(user_command, "wificonfig")){
         int i;
         Serial.println("Aguardando comando...");
         Serial.println("Ex. ip,192.168.0.1");
         while(!Serial.available()){}
         ler_serial(user_command);     
         arg1 = (getValue(user_command,',',0));
         arg2 = (getValue(user_command,',',1));
         arg1.toCharArray(user_command, sizeof(user_command));
         if (!strcmp(user_command, "ip")){
            arg2.toCharArray(mqtt_server, sizeof(mqtt_server));
         }        
      }   
   } 
}

        
void loop() {
    verificar_comando_serial();
    
    if (!digitalRead(SW_DISPLAY) && threadTo(&last_debaunce_time, debaunce_time)) {      
        display_current_view++;       
        displayUpdate(&display_current_view);                 // Muda tela do display
    }

    if (threadTo(&last_upload_time, time_between_uploads)) {         // Faz upload das informações mais recentes
        piscaled(2, 50);
     //   strcpy(atual.id, $id);
     //   atual.tensao = retV();
      atual.tensao = ADE7753.ReadVRMS();
      //  atual.frequencia = retHz();
    //    atual.corrente = retI();
//        atual.FP = retFP();
//        atual.pot_at = retW();
//        atual.pot_re = retVAr();
//        atual.pot_ap = retVA();
       // atual.timestamp = setClock();
  //      displayUpdate(&display_current_view);
        createMessage(msg_to_publish, atual);
        publish_message(msg_to_publish);
    }
//    resetastatus();
}
