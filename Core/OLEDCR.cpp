/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "OLEDCR.h"

#define SDApin D1
#define SCKpin D2

SSD1306Wire oledDisp(0x3c, SDApin, SCKpin);

//void OLED::Init(int SDApin, int SCKpin){
    //SSD1306Wire OledDisp(0x3c, SDApin, SCKpin);
//}


void OLED::ShowMessage(char* message)
{
    oleddisp.clear();
    oleddisp.setColor(WHITE);
    oleddisp.setTextAlignment(TEXT_ALIGN_CENTER);
    oleddisp.setFont(ArialMT_Plain_16);
    oleddisp.drawString((oleddisp.getWidth()/2), (oleddisp.getHeight()/2), message);
    oleddisp.display();
}

int OLED::ShowCompleteView(char* data)
{
    oleddisp.clear();                                                                                
    oleddisp.setTextAlignment(TEXT_ALIGN_CENTER);                                                    
    oleddisp.setFont(ArialMT_Plain_16);                                                              
    oleddisp.drawRect(0, 0, oleddisp.getWidth(), oleddisp.getHeight());               // Retangulo principal borda branca
    oleddisp.fillRect(0, 0, oleddisp.getWidth(), (oleddisp.getHeight()/2)-8);         // Retangulo interno preenchimento branco

    char toptext[30];
    char bottomtext[30];
    strcpy(toptext, data);
    strcpy(bottomtext, data);
    char* ptr;
    ptr = strchr(toptext, '=');
    *ptr = 0;
    ptr = strchr(bottomtext, '=');
    bottomtext = ptr;
    
    Serial.println(pch);
    oleddisp.setColor(BLACK);                                                       
    oleddisp.drawString((oleddisp.getWidth()/2),5,toptext);   // Imprime o nome do parametro
    oleddisp.setColor(WHITE);                                                       
  
    Serial.println(pch);
    oleddisp.drawString((oleddisp.getWidth()/2),(oleddisp.getHeight()/2), bottomtext); // Imprime o valor com a unidade de medida
    oleddisp.display();

}
