/* * Nome do arquivo: funcoes_ADE7753.h
 * Este arquivo armazena funcoes relacionadas a R/W de registradores do ADE7753 
 */

#include <math.h>
#define CLOCKIN 3579545            // Clock do ADE


// Lista de registradores 
#define WAVEFORM 0x01
#define AENERGY 0x02
#define RAENERGY 0x03
#define LAENERGY 0x04
#define VAENERGY 0x05
#define RVAENERGY 0x06
#define LVAENERGY 0x07
#define LVARENERGY 0x08
#define MODE 0x09
#define IRQEN 0x0A
#define STATUS 0x0B
#define RSTSTATUS 0x0C
#define CH1OS 0x0D
#define CH2OS 0x0E
#define GAIN 0x0F
#define PHCAL 0x10
#define APOS 0x11
#define WGAIN 0x12
#define WDIV 0x13
#define CFNUM 0x14
#define CFDEN 0x15
#define IRMS 0x16
#define VRMS 0x17
#define IRMSOS 0x18
#define VRMSOS 0x19
#define VAGAIN 0x1A
#define VADIV 0x1B
#define LINECYC 0x1C
#define ZXTOUT 0x1D
#define SAGCYC 0x1E
#define SAGLVL 0x1F
#define IPKLVL 0x20
#define VPKLVL 0x21
#define IPEAK 0x22
#define RSTIPEAK 0x23
#define VPEAK 0x24
#define RSTVPEAK 0x25
#define TEMP 0x26
#define PERIOD 0x27

#define MODE_VALUE_16BITS 0b0000000010001100    //   < CYCMODE=1 cycle energy acumulation mode >     
#define IRQEN_VALUE_16BITS   0b1000 //   0x131F
#define APOS_VALUE_16BITS 0x0100    // < APOS = 0x0100)  This 16-bit register allows small offsets in the active power calculation to be removed
//#define IRMSOS_VALUE_12BITS 0b00000000000    //OFFSET
#define VRMSOS_VALUE_12BITS 0b000000000000   //OFFSET
#define LINECYC_VALUE_16BITS 1000  // < 2000 ciclos 8,3 de acumulacao

void write8(unsigned long reg, unsigned long value);
void write16(unsigned long reg, unsigned long value);

char *registers[] = {"WAVEFORM", "AENERGY", "RAENERGY", "LAENERGY", "VAENERGY", "RVAENERGY",
                     "LVAENERGY", "LVARENERGY", "MODE", "IRQEN", "STATUS", "RSTSTATUS", 
                     "CH1OS", "CH2OS", "GAIN", "PHCAL", "APOS", "WGAIN", 
                     "WDIV", "CFNUM", "CFDEN", "IRMS", "VRMS", "IRMSOS", 
                     "VRMSOS", "VAGAIN", "VADIV", "LINECYC", "ZXTOUT", "SAGCYC", 
                     "SAGLVL", "IPKLVL", "VPKLVL", "IPEAK", "RSTIPEAK", "VPEAK", 
                     "RSTVPEAK", "TEMP", "PERIOD"};

void enableChip(){
  SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE1));
  digitalWrite(CS_PIN,LOW);
  delayMicroseconds(50);
}

void disableChip(){
  digitalWrite(CS_PIN,HIGH);  
  SPI.endTransaction();
  delayMicroseconds(50);
}

unsigned long read24(unsigned long reg){  //Le um registrador de 24bits
  enableChip();
  unsigned char b2,b1,b0;  //tres variaveis de 8 bits
  SPI.transfer(reg | 0b00000000);       //inicia a comunicacao
  delayMicroseconds(5);
  b2=SPI.transfer(0x81);   //envia um dummy e recebe 8 bits por vez
  delayMicroseconds(5);
  b1=SPI.transfer(0x81);
  delayMicroseconds(5);
  b0=SPI.transfer(0x81);
  delayMicroseconds(150);
  disableChip();             
  return ((unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0);             
}
 
unsigned long read16(unsigned long reg){
    enableChip();
    unsigned char b1,b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b1=SPI.transfer(0x81);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(150);
    disableChip();
    return ((unsigned long)b1<<8 | (unsigned long)b0);            
}

unsigned long read8(unsigned long reg){
  enableChip();
    unsigned char b0;
    SPI.transfer(reg | 0b00000000);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(150);
    disableChip();
    return (unsigned long)b0;            
}

void write8(unsigned long reg, unsigned long value){ // value 8bits
   enableChip();
   SPI.transfer( (reg | 0b10000000) );  // utilizado para colocar 1 no MSB indicando gravacao no registrador
   delayMicroseconds(20);
   SPI.transfer(value&0xFF); //envia os 8 bits menos significativos
   delayMicroseconds(100);
   disableChip();  
}

void write16(unsigned long reg, unsigned long value){ // value 16bits
   enableChip();
   SPI.transfer( (reg | 0b10000000) );  //colocar 1 no MSB indica gravacao no registrador
   delayMicroseconds(20);
   SPI.transfer(value>>8); //envia os 8 bits mais significativos
   delayMicroseconds(20);
   SPI.transfer(value&0xFF); //envia os 8 bits menos significativos
   delayMicroseconds(100);
   disableChip();  
}
/*
unsigned long valorMedio( int qtde_amostras, unsigned long (*function)(unsigned long), unsigned long reg ){
  //exemplo de uso -> unsigned long measure = (valorMedio(10, read24, VRMS));
  unsigned long media = 0;
  for (int x=0; x<qtde_amostras; x++)
    {
      media = media + (*function)(reg);
    }  
    media = media / qtde_amostras;
    return media;
}
*/

int aguardapassagemporzero(){ //retorna 0 se for bem sucedido
  unsigned long value = 1;
  unsigned long conta_millis = millis();
  while (!value) {
   if (millis() > conta_millis+100) break; 
   value = (0b10000 & read16(STATUS));    
  }
}

float retV() {
    unsigned long measure = 0;
    float calculado = 0;
    aguardapassagemporzero();
    measure = read24(VRMS);
    Serial.print(" registrador: ");
    Serial.println(measure,BIN);
    calculado = (measure*0.500)/1561400;
    return calculado;
}

float retHz() {  //le periodo e retorna frequencia
    unsigned long reg_value;
    float calculado;
    reg_value = read16(PERIOD);
    calculado = CLOCKIN/(8*reg_value);
    return calculado;
}

float retI() {  //le corrente
    unsigned long measure;
    float calculado;
    aguardapassagemporzero();
    measure = read24(IRMS);
    calculado = (measure*10.00)/1868467;   //10 amperes correspondem ao max de 0.5V no circuito
    return calculado;
}

//unsigned long retW(){                         //le potencia ativa
//    float calculado;
//    calculado = atual.pot_ap*atual.FP;  //  pot aparente * cos(teta)
//    return calculado;
//}

//float retVA(){
//   float calculado = atual.tensao*atual.corrente;  //tensao * corrente
//   return calculado; /
//}

//float retVAr(){
//   float calculado = atual.pot_ap* sin(acos(atual.FP) );   //pot aparente * sen(teta)
//   if (isnan(calculado))
//     return 0;
//   else
//     return calculado; 
//}

//float retFP(){
//   const String reg = "FP";
//   float aenergy = read24(RAENERGY);
//   float vaenergy = read24(RVAENERGY);
//   float calculado = (vaenergy / (aenergy));
//   if (isnan(calculado))
//     return 0;
//   else
//     return calculado; 
//}

void reseta_status(){
  read16(RSTSTATUS);
}
