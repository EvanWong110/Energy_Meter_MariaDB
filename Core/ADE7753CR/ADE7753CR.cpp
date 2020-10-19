/*
  ADE7753.CR.h - Library for use with ADE7753.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ADE7753CR.h"
#include "SPI.h"


//public

void ADE7753::Init(int CSpin)
{
  SPI.begin();
  pinMode(CSpin, OUTPUT);
  _CSpin = CSpin;
}

void ADE7753::Closes()
{
 SPI.endTransaction();
}

char ResetaStatusReg(){
    read16(RSTSTATUS)
}

float ReadVRMS(){  //returns a % of full range [0.5Vin]
    unsigned long reg_value;
    float calculado;
    aguardapassagemporzero();
    reg_value = read24(VRMS);
    Serial.print("VRMS BIN Value: ");
    Serial.println(reg_value,BIN);
    calculado = (reg_value/1561400)*100;
    return calculado;
}
  
float ReadIRMS(){
    unsigned long reg_value;
    float calculado;
    aguardapassagemporzero();
    reg_value = read24(IRMS);
    calculado = (reg_value /1868467)*100;   //returns a % of full range [0.5Vin]
    return calculado;
}

float ReadPERIOD(int CLKIN){  //returns period in seconds
    unsigned long reg_value;
    float period;
    reg_value = read16(PERIOD);
    period = (8*reg_value)/CLKIN;
    return period;
}
  
//private

void ADE7753::Enable()
{
  digitalWrite(CSpin,LOW);  
}

void ADE7753::Disable()
{
  digitalWrite(CSpin,HIGH);  
}

unsigned long ADE7753::read8(unsigned long reg){
    enables();
    unsigned char b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(150);
    disables();
    return (unsigned long)b0;
}
    
unsigned long ADE7753::read16(unsigned long reg){
    enables();
    unsigned char b1,b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b1=SPI.transfer(0x81); //DUMMY BITS
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(50);
    disables();
    return ((unsigned long)b1<<8 | (unsigned long)b0);            
}

unsigned long ADE7753::read24(unsigned long reg){
    enables();
    unsigned char b2,b1,b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b2=SPI.transfer(0x81);
    delayMicroseconds(5);
    b1=SPI.transfer(0x81);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(50);
    disables();
    return ((unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0);            
}
void Write8(unsigned long reg, unsigned long value){
    enables();
    SPI.transfer( (reg | 0b10000000) );  // utilizado para colocar 1 no MSB indicando gravacao no registrador
    delayMicroseconds(5);
    SPI.transfer(value); 
    delayMicroseconds(50);
    disables();
}
void Write16(unsigned long reg, unsigned long value){
    enables();
    SPI.transfer( (reg | 0b10000000) );  //colocar 1 no MSB indica gravacao no registrador
    delayMicroseconds(5);
    SPI.transfer(value>>8); //envia os 8 bits mais significativos
    delayMicroseconds(5);
    SPI.transfer(value&0xFF); //envia os 8 bits menos significativos
    delayMicroseconds(50);
    disables();
}
void WaitZeroCross(){  //returns 0 when ZeroCross
    unsigned long value = 1;
    unsigned long conta_millis = millis();
    while (!value) {
        if (millis() > conta_millis+100) 
            break; 
        value = (0b10000 & read16(STATUS));    
    }
}



   