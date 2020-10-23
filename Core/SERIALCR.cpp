#include "SERIALCR.h"

void Serials::ReceiveSerial(char* received){
   char message[100];
   int charsRead = 0;
   if (Serial.available() > 0) 
   {  // Is the Serial object sending something?
      charsRead = Serial.readBytesUntil('\n', message, sizeof(message) - 1);   // Yep, so read it...
      message[charsRead] = '\0';                        // Now make it a C string...
      Serial.print("Comando recebido: ");
      Serial.println(message);
      strcpy(received, message);
   }
}

void Serials::ExecutaComandoSerial(){
   
   if (Serial.available()) {
      char received[100] = "";
      ReceiveSerial(received);
      Serial.println("SELECIONE UMA OPCAO:");
      Serial.println("1 - ");
      Serial.println("2 - ");
      Serial.println("3 - ");
      Serial.println("4 - ");
      Serial.println("5 - "); 
      while(!Serial.available()){}
      ReceiveSerial(received);
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
