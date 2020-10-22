/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "OLEDCR.h"

#define SDApin D1
#define SCKpin D2

SSD1306Wire display(0x3c, SDApin, SCKpin);

void OLED::Init(){
   // SSD1306Wire OledDisp(0x3c, SDApin, SCKpin);
   display.init();
   display.flipScreenVertically();
   display.clear();
}


void OLED::ShowMessage(char* message)
{/*
    oleddisp.clear();
    oleddisp.setColor(WHITE);
    oleddisp.setTextAlignment(TEXT_ALIGN_CENTER);
    oleddisp.setFont(ArialMT_Plain_16);
    oleddisp.drawString((oleddisp.getWidth()/2), (oleddisp.getHeight()/2), message);
    oleddisp.display();*/
}

void OLED::ShowCompleteView(char* data)
{
   //display.clear();                                                                                
  //  oleddisp.setTextAlignment(TEXT_ALIGN_CENTER);                                                    
  //  oleddisp.setFont(ArialMT_Plain_16);                                                              
  //  oleddisp.drawRect(0, 0, oleddisp.getWidth(), oleddisp.getHeight());               // Retangulo principal borda branca
  //  oleddisp.fillRect(0, 0, oleddisp.getWidth(), (oleddisp.getHeight()/2)-8);         // Retangulo interno preenchimento branco

    char * ptr;
    ptr = strtok(data, "=");
    Serial.println(ptr);
    ptr = strtok(NULL, "=");
    Serial.println(ptr);
      
  //  oleddisp.setColor(BLACK);                                                       
  //  oleddisp.drawString((oleddisp.getWidth()/2),5,toptext);   // Imprime o nome do parametro
  //  oleddisp.setColor(WHITE);                                                       
  
  //  Serial.println(ptr);
  //  oleddisp.drawString((oleddisp.getWidth()/2),(oleddisp.getHeight()/2), ptr); // Imprime o valor com a unidade de medida
   // oleddisp.display();

}
