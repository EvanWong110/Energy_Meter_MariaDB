#include "SERIALCR.h"

void Serials::ReceiveSerial(char* received){
   char message[100];
   int charsRead = 0;
   while(!Serial.available()){}
   if (Serial.available() > 0) 
   {  // Is the Serial object sending something?
      charsRead = Serial.readBytesUntil('\n', message, sizeof(message) - 1);   // Yep, so read it...
      message[charsRead] = '\0';                        // Now make it a C string...
      Serial.print("Comando recebido: ");
      strcpy(received, message);
      Serial.println(received);
   }
}

void Serials::ExecutaComandoSerial(ADE7753* ADE7753){  
   if (Serial.available()) {
      char received[100] = "";
      ReceiveSerial(received);
      Serial.println("SELECIONE UMA OPCAO:");
      Serial.println("1 - Disable CH1");
      Serial.println("2 - Enable CH1");
      Serial.println("3 - Disable CH2");
      Serial.println("4 - Enable CH2");
      Serial.println("5 - Set VRMSOS"); 
      ReceiveSerial(received);
      int option = atoi(received);
      switch (option){
          case 0:
          //do nothing
          break;
          case 1:
             /* code */
             Serial.println("Selecionada opção 1. ");
             ADE7753->DisableCH1();
             break;
          case 2:
             /* code */
             ADE7753->EnableCH1();
             break;
          case 3:
             /* code */
             ADE7753->DisableCH2();
             break;
          case 4:
             /* code */
             ADE7753->EnableCH2();
            break;
          case 5:
             Serial.println("Value input: ");
             ReceiveSerial(received);           
             Serial.println(ADE7753->SetVRMSOS(atoi(received)));
             /* code */
             break; 
      }
   }
}
