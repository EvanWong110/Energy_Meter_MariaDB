/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "OLEDCR.h"

#define SDApin D1
#define SCKpin D2

SSD1306Wire OledDisp(0x3c, SDApin, SCKpin);

//void OLED::Init(int SDApin, int SCKpin){
//}


void OLED::ShowMessage(char* message)
{
    OledDisp.clear();
    OledDisp.setColor(WHITE);
    OledDisp.setTextAlignment(TEXT_ALIGN_CENTER);
    OledDisp.setFont(ArialMT_Plain_16);
    OledDisp.drawString((OledDisp.getWidth()/2), (OledDisp.getHeight()/2), message);
    OledDisp.display();
}

int OLED::ShowCompleteView(char* data)
{
    OledDisp.clear();                                                                                
    OledDisp.setTextAlignment(TEXT_ALIGN_CENTER);                                                    
    OledDisp.setFont(ArialMT_Plain_16);                                                              
    OledDisp.drawRect(0, 0, OledDisp.getWidth(), OledDisp.getHeight());               // Retangulo principal borda branca
    OledDisp.fillRect(0, 0, OledDisp.getWidth(), (OledDisp.getHeight()/2)-8);         // Retangulo interno preenchimento branco

    char buff[30];
    //sprintf(buff, "%s", data);
    char * pch;
    pch = strtok (buff, "=");
    Serial.println(pch);
    OledDisp.setColor(BLACK);                                                       
    OledDisp.drawString((OledDisp.getWidth()/2),5,pch);   // Imprime o nome do parametro
    OledDisp.setColor(WHITE);                                                       
    pch = strtok (NULL, "=");
    Serial.println(pch);
    OledDisp.drawString((OledDisp.getWidth()/2),(OledDisp.getHeight()/2), pch); // Imprime o valor com a unidade de medida
    OledDisp.display();

}
