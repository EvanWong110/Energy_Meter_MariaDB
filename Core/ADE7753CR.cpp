/*
  ADE7753CR.h - Library for use with ADE7753.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/

#include "ADE7753CR.h"

//public
void ADE7753::Init(int CSpin)
{
    _CSpin = CSpin;
    pinMode(_CSpin, OUTPUT);
    SPI.begin();
    SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE1));
}

void ADE7753::Closes()
{
    SPI.endTransaction();
}

void ADE7753::EnableHPF(){
    UnsetBits(MODE, DISHPF);
}

void ADE7753::DisableHPF(){
    SetBits(MODE, DISHPF);
}

void ADE7753::EnableLPF2(){
    UnsetBits(MODE, DISLPF2);
}

void ADE7753::DisableLPF2(){
    SetBits(MODE, DISLPF2);
}

void ADE7753::EnableCF(){
    UnsetBits(MODE, DISCF);
}

void ADE7753::DisableCF(){
    SetBits(MODE, DISCF);
}
void ADE7753::EnableSAGDetection(){
    UnsetBits(MODE, DISSAG);
} 

void ADE7753::DisableSAGDetection(){
    SetBits(MODE, DISSAG);
}

void ADE7753::DisableADConverters(){
    SetBits(MODE, ASUSPEND);
}

void ADE7753::EnableADConverters(){
    UnsetBits(MODE, ASUSPEND);
}

void ADE7753::StartTemperatureMeasurement(){
    SetBits(MODE, TEMPSEL);
}

void ADE7753::SoftReset(){
    SetBits(MODE, SWRST);
    delayMicroseconds(18);
}

void ADE7753::EnableAcummulationMode(){
    SetBits(MODE, CYCMODE); 
}

void ADE7753::DisableAcummulationMode(){
    UnsetBits(MODE, CYCMODE); 
}

void ADE7753::DisableCH1(){  
    SetBits(MODE, DISCH1);
}

void ADE7753::DisableCH2(){
    SetBits(MODE, DISCH2);
}

void ADE7753::EnableCH1(){
    UnsetBits(MODE, DISCH1);
}

void ADE7753::EnableCH2(){
    UnsetBits(MODE, DISCH2);
}

void ADE7753::DisableSwap(){
    UnsetBits(MODE, SWAP);
}

void ADE7753::EnableSwap(){
    SetBits(MODE, SWAP);
}

void ADE7753::SelectWaveformDataRate(int datarate){
    switch (datarate)
    {
    case 1:
        UnsetBits(MODE, DTRT10);
        SetBits(MODE, DTRT10_01);
        break;
    case 2:
        UnsetBits(MODE, DTRT10);
        SetBits(MODE, DTRT10_10);
        break;
    case 3:
        SetBits(MODE, DTRT10_11);
        break;
    default:
        UnsetBits(MODE, DTRT10);
        break;
    }
}

void ADE7753::SelectWaveformDataSource(int datasource){
    switch (datasource)
    {
    case 2:
        UnsetBits(MODE, WAVSEL10);
        SetBits(MODE, WAVSEL10_10);
        break;
    case 3:
        SetBits(MODE, WAVSEL10_11);
        break;
    default:
        UnsetBits(MODE, WAVSEL10);
        break;
    }
}    
    
void ADE7753::EnableOnlyPositive(){
    SetBits(MODE, POAM);
}

void ADE7753::DisableOnlyPositive(){
    UnsetBits(MODE, POAM);
}

void ADE7753::EnableIRQActiveEnergyHalfFull(){
    SetBits(IRQEN, AEHF);
}

void ADE7753::DisableIRQActiveEnergyHalfFull(){
    UnsetBits(IRQEN, AEHF);
}

void ADE7753::EnableIRQSAG(){
    SetBits(IRQEN, SAG);
}

void ADE7753::DisableIRQSAG(){
    UnsetBits(IRQEN, SAG);
}

void ADE7753::EnableIRQCycleEnergyAcumulationEnd(){
    SetBits(IRQEN, CYCEND);   
}

void ADE7753::DisableIRQCycleEnergyAcumulationEnd(){
    UnsetBits(IRQEN, CYCEND);   
}

void ADE7753::EnableIRQNewWaveformData(){
    SetBits(IRQEN, WSMP);   
}

void ADE7753::DisableIRQNewWaveformData(){
    UnsetBits(IRQEN, WSMP);   
}

void ADE7753::EnableIRQZeroCrossing(){
    SetBits(IRQEN, ZX);   
}

void ADE7753::DisableIRQZeroCrossing(){
    UnsetBits(IRQEN, ZX);   
}

void ADE7753::EnableIRQTemperatureResults(){
    SetBits(IRQEN, TEMP);   
}

void ADE7753::DisableIRQTemperatureResults(){
    UnsetBits(IRQEN, TEMP);   
}

void ADE7753::EnableIRQActiveEnergyOverflow(){
    SetBits(IRQEN, AEOF);   
}

void ADE7753::DisableIRQActiveEnergyOverflow(){
    UnsetBits(IRQEN, AEOF);   
}

void ADE7753::EnableIRQCH2VlvlPeek(){
    SetBits(IRQEN, PKV);   
}

void ADE7753::DisableIRQCH2VlvlPeek(){
    UnsetBits(IRQEN, PKV);   
}

void ADE7753::EnableIRQCH1IlvlPeek(){
    SetBits(IRQEN, PKI);   
}

void ADE7753::DisableIRQCH1IlvlPeek(){
    UnsetBits(IRQEN, PKI);   
}

void ADE7753::EnableIRQAparentEnergyHalfFull(){
    SetBits(IRQEN, VAEHF);   
}

void ADE7753::DisableIRQAparentEnergyHalfFull(){
    UnsetBits(IRQEN, VAEHF);   
}

void ADE7753::EnableIRQAparentEnergyOverflow(){
    SetBits(IRQEN, VAEOF);   
}

void ADE7753::DisableIRQAparentEnergyOverflow(){
    UnsetBits(IRQEN, VAEOF);   
}

void ADE7753::EnableIRQZeroCrossingTimeout(){
    SetBits(IRQEN, ZXTO);   
}

void ADE7753::DisableIRQZeroCrossingTimeout(){
    UnsetBits(IRQEN, ZXTO);   
}

void ADE7753::EnablesIRQPowerChangeToPos(){
    SetBits(IRQEN, PPOS);   
}

void ADE7753::DisablesIRQPowerChangeToPos(){
    UnsetBits(IRQEN, PPOS);   
}

void ADE7753::EnablesIRQPowerChangeToNeg(){
    SetBits(IRQEN, PNEG);   
}

void ADE7753::DisablesIRQPowerChangeToNeg(){
    UnsetBits(IRQEN, PNEG);   
}

bool ADE7753::CheckActiveEnergyHalfFull(){
    return(Read16(STATUS) & AEHF);
}

bool ADE7753::CheckSAG(){
    return(Read16(STATUS) & SAG);
}

bool ADE7753::CheckCycleEnergyAcumulationEnd(){
    return(Read16(STATUS) & CYCEND);
}

bool ADE7753::CheckNewWaveformData(){
    return(Read16(STATUS) & WSMP);
}

bool ADE7753::CheckZeroCrossing(){
    return(Read16(STATUS) & ZX);
}

bool ADE7753::CheckTemperatureResults(){
    return(Read16(STATUS) & TEMP);
}

bool ADE7753::CheckActiveEnergyOverflow(){
    return(Read16(STATUS) & AEOF);
}

bool ADE7753::CheckCH2VlvlPeek(){
    return(Read16(STATUS) & PKV);
}

bool ADE7753::CheckCH1IlvlPeek(){
    return(Read16(STATUS) & PKI);
}

bool ADE7753::CheckAparentEnergyHalfFull(){
    return(Read16(STATUS) & VAEHF);
}

bool ADE7753::CheckAparentEnergyOverflow(){
    return(Read16(STATUS) & VAEOF);
}

bool ADE7753::CheckZeroCrossingTimeout(){
    return(Read16(STATUS) & ZXTO);
}

bool ADE7753::CheckPowerChangeToPos(){
    return(Read16(STATUS) & PPOS);
}

bool ADE7753::CheckPowerChangeToNeg(){
    return(Read16(STATUS) & PNEG);
}

char ADE7753::ResetaStatusReg(){
    return Read16(RSTSTATUS);
}

float ADE7753::ReadVRMS(){  //returns a % of full range [0.5Vin]
    unsigned long reg_value;
    float percent;
    WaitZeroCross();
    reg_value = Read24(VRMS);
    Serial.print("VRMS BIN Value: ");
    Serial.println(reg_value,BIN);
    percent = (reg_value/1561400.00000)*100;
    Serial.print(percent);
    return percent;
}
  
float ADE7753::ReadIRMS(){
    unsigned long reg_value;
    float percent;
    WaitZeroCross();
    reg_value = Read24(IRMS);
    percent = (reg_value /1868467)*100;   //returns a % of full range [0.5Vin]
    return percent;
}

float ADE7753::ReadPERIOD(int CLKIN){  //returns period in seconds
    unsigned long reg_value;
    float period;
    reg_value = Read16(PERIOD);
    period = (8*reg_value)/CLKIN;
    return period;
}

void ADE7753::DisplayBufferCreator(int view, Measurement* data)  
{
    switch (view)
    {
    case 1:
    Serial.println(data->voltage);
        sprintf(data->display_buffer, "Voltage=%f", data->voltage);
        break;
    case 2:
        sprintf(data->display_buffer, "Current=%f", data->current);
        break;
    case 3:
        sprintf(data->display_buffer, "FP=%f", data->FP);
        break;
    case 4:
        sprintf(data->display_buffer, "Frequency=%f", data->frequency);
        break;
    case 5:
        sprintf(data->display_buffer, "Apparent Potency=%f", data->aparent_power);
        break;
    default:
        break;
    }
}

//------------------  
//private
//------------------

void ADE7753::Enable()
{
    digitalWrite(_CSpin,LOW);  
}

void ADE7753::Disable()
{
    digitalWrite(_CSpin,HIGH);  
}

void ADE7753::SetBits(char reg, unsigned long value){
    Write16(reg, Read16(reg) | value);
}

void ADE7753::UnsetBits(char reg, unsigned long value){
    Write16(reg, Read16(reg) & value);
}

unsigned long ADE7753::Read8(char reg){
    Enable();
    char b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(150);
    Disable();
    return (unsigned long)b0;
}
    
unsigned long ADE7753::Read16(char reg){
    Enable();
    char b1,b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b1=SPI.transfer(0x81); //DUMMY BITS
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(50);
    Disable();
    return ((unsigned long)b1<<8 | (unsigned long)b0);            
}

unsigned long ADE7753::Read24(char reg){
    Enable();
    char b2,b1,b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b2=SPI.transfer(0x81);
    delayMicroseconds(5);
    b1=SPI.transfer(0x81);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(50);
    Disable();
    return ((unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0);            
}

void ADE7753::Write8(char reg, unsigned long value){
    Enable();
    SPI.transfer( (reg | 0b10000000) );  // utilizado para colocar 1 no MSB indicando gravacao no registrador
    delayMicroseconds(5);
    SPI.transfer(value); 
    delayMicroseconds(50);
    Disable();
}

void ADE7753::Write16(char reg, unsigned long value){
    Enable();
    SPI.transfer( (reg | 0b10000000) );  //colocar 1 no MSB indica gravacao no registrador
    delayMicroseconds(5);
    SPI.transfer(value>>8); //envia os 8 bits mais significativos
    delayMicroseconds(5);
    SPI.transfer(value&0xFF); //envia os 8 bits menos significativos
    delayMicroseconds(50);
    Disable();
}

int ADE7753::WaitZeroCross(){  //returns 0 when ZeroCross
    unsigned long value = 1;
    unsigned long conta_millis = millis();
    while (!value) {
        if (millis() > conta_millis+100) 
            break; 
        value = (0b10000 & Read16(STATUS));    
    }
    return value;
}



   
