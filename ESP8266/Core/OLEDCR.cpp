/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "OLEDCR.h"

void OLED::Init(SSD1306Wire* display){
   display->init();
   display->flipScreenVertically();
   display->clear();
}

void OLED::ShowMessage(SSD1306Wire* display, char* message){
    
    display->clear();
    display->setColor(WHITE);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_16);
    display->drawString((display->getWidth()/2), (display->getHeight()/2), message);
    display->display();
}

void OLED::ShowCompleteView(SSD1306Wire* display, char* data){
    char container1[30];
    char container2[30];
    display->clear();                                                                                
    display->setTextAlignment(TEXT_ALIGN_CENTER);                                                    
    display->setFont(ArialMT_Plain_16);                                                              
    display->drawRect(0, 0, display->getWidth(), display->getHeight());               // Retangulo principal borda branca
    display->fillRect(0, 0, display->getWidth(), (display->getHeight()/2)-8);         // Retangulo interno preenchimento branco
    char * ptr;
    ptr = strtok(data, "=");
    strcpy(container1, ptr);
    ptr = strtok(NULL, "=");
    strcpy(container2, ptr);
    display->setColor(BLACK);                                                       
    display->drawString((display->getWidth()/2),5,container1);   // Imprime o nome do parametro
    display->setColor(WHITE);                                                       
    display->drawString((display->getWidth()/2),(display->getHeight()/2), container2); // Imprime o valor com a unidade de medida
    display->display();
}
