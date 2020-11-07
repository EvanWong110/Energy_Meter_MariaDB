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
    SoftReset();
}

void ADE7753::Closes()
{
    SPI.endTransaction();
}

void ADE7753::EnableHPF(){
    UnsetBits(MODE_U, DISHPF);
}

void ADE7753::DisableHPF(){
    SetBits(MODE_U, DISHPF);
}

void ADE7753::EnableLPF2(){
    UnsetBits(MODE_U, DISLPF2);
}

void ADE7753::DisableLPF2(){
    SetBits(MODE_U, DISLPF2);
}

void ADE7753::EnableCF(){
    UnsetBits(MODE_U, DISCF);
}

void ADE7753::DisableCF(){
    SetBits(MODE_U, DISCF);
}
void ADE7753::EnableSAGDetection(){
    UnsetBits(MODE_U, DISSAG);
} 

void ADE7753::DisableSAGDetection(){
    SetBits(MODE_U, DISSAG);
}

void ADE7753::DisableADConverters(){
    SetBits(MODE_U, ASUSPEND);
}

void ADE7753::EnableADConverters(){
    UnsetBits(MODE_U, ASUSPEND);
}

void ADE7753::StartTemperatureMeasurement(){
    SetBits(MODE_U, TEMPSEL);
}

void ADE7753::SoftReset(){
    SetBits(MODE_U, SWRST);
    delayMicroseconds(18);
}

unsigned long ADE7753::EnableAccumulationMode(){
    SetBits(MODE_U, CYCMODE);
    return Read16(MODE_U); 
}

void ADE7753::DisableAccumulationMode(){
    UnsetBits(MODE_U, CYCMODE); 
}

void ADE7753::DisableCH1(){  
    SetBits(MODE_U, DISCH1);
    Serial.println("CH1 AD Disabled");
    Serial.println(ReadModeReg(),BIN);
}

void ADE7753::DisableCH2(){
    SetBits(MODE_U, DISCH2);
    Serial.println("CH2 AD Disabled");
    Serial.println(ReadModeReg(),BIN);
}

void ADE7753::EnableCH1(){
    UnsetBits(MODE_U, DISCH1);
    Serial.println("CH1 AD Enabled");
    Serial.println(ReadModeReg(),BIN);
}

void ADE7753::EnableCH2(){
    UnsetBits(MODE_U, DISCH2);
    Serial.println("CH2 AD Enabled");
    Serial.println(ReadModeReg(),BIN);
}

void ADE7753::DisableSwap(){
    UnsetBits(MODE_U, SWAP);
}

void ADE7753::EnableSwap(){
    SetBits(MODE_U, SWAP);
}

void ADE7753::SelectWaveformDataRate(int datarate){
    switch (datarate)
    {
    case 1:
        UnsetBits(MODE_U, DTRT10);
        SetBits(MODE_U, DTRT10_01);
        break;
    case 2:
        UnsetBits(MODE_U, DTRT10);
        SetBits(MODE_U, DTRT10_10);
        break;
    case 3:
        SetBits(MODE_U, DTRT10_11);
        break;
    default:
        UnsetBits(MODE_U, DTRT10);
        break;
    }
}

void ADE7753::SelectWaveformDataSource(int datasource){
    switch (datasource)
    {
    case 2:
        UnsetBits(MODE_U, WAVSEL10);
        SetBits(MODE_U, WAVSEL10_10);
        break;
    case 3:
        SetBits(MODE_U, WAVSEL10_11);
        break;
    default:
        UnsetBits(MODE_U, WAVSEL10);
        break;
    }
}    
    
void ADE7753::EnableOnlyPositive(){
    SetBits(MODE_U, POAM);
}

void ADE7753::DisableOnlyPositive(){
    UnsetBits(MODE_U, POAM);
}

void ADE7753::EnableIRQActiveEnergyHalfFull(){
    SetBits(IRQEN_U, AEHF);
}

void ADE7753::DisableIRQActiveEnergyHalfFull(){
    UnsetBits(IRQEN_U, AEHF);
}

void ADE7753::EnableIRQSAG(){
    SetBits(IRQEN_U, SAG);
}

void ADE7753::DisableIRQSAG(){
    UnsetBits(IRQEN_U, SAG);
}

void ADE7753::EnableIRQCycleEnergyAccumulationEnd(){
    SetBits(IRQEN_U, CYCEND);   
}

void ADE7753::DisableIRQCycleEnergyAccumulationEnd(){
    UnsetBits(IRQEN_U, CYCEND);   
}

void ADE7753::EnableIRQNewWaveformData(){
    SetBits(IRQEN_U, WSMP);   
}

void ADE7753::DisableIRQNewWaveformData(){
    UnsetBits(IRQEN_U, WSMP);   
}

void ADE7753::EnableIRQZeroCrossing(){
    SetBits(IRQEN_U, ZX);   
}

void ADE7753::DisableIRQZeroCrossing(){
    UnsetBits(IRQEN_U, ZX);   
}

void ADE7753::EnableIRQTemperatureResults(){
    SetBits(IRQEN_U, TEMP);   
}

void ADE7753::DisableIRQTemperatureResults(){
    UnsetBits(IRQEN_U, TEMP);   
}

void ADE7753::EnableIRQActiveEnergyOverflow(){
    SetBits(IRQEN_U, AEOF);   
}

void ADE7753::DisableIRQActiveEnergyOverflow(){
    UnsetBits(IRQEN_U, AEOF);   
}

void ADE7753::EnableIRQCH2VlvlPeek(){
    SetBits(IRQEN_U, PKV);   
}

void ADE7753::DisableIRQCH2VlvlPeek(){
    UnsetBits(IRQEN_U, PKV);   
}

void ADE7753::EnableIRQCH1IlvlPeek(){
    SetBits(IRQEN_U, PKI);   
}

void ADE7753::DisableIRQCH1IlvlPeek(){
    UnsetBits(IRQEN_U, PKI);   
}

void ADE7753::EnableIRQAparentEnergyHalfFull(){
    SetBits(IRQEN_U, VAEHF);   
}

void ADE7753::DisableIRQAparentEnergyHalfFull(){
    UnsetBits(IRQEN_U, VAEHF);   
}

void ADE7753::EnableIRQAparentEnergyOverflow(){
    SetBits(IRQEN_U, VAEOF);   
}

void ADE7753::DisableIRQAparentEnergyOverflow(){
    UnsetBits(IRQEN_U, VAEOF);   
}

void ADE7753::EnableIRQZeroCrossingTimeout(){
    SetBits(IRQEN_U, ZXTO);   
}

void ADE7753::DisableIRQZeroCrossingTimeout(){
    UnsetBits(IRQEN_U, ZXTO);   
}

void ADE7753::EnablesIRQPowerChangeToPos(){
    SetBits(IRQEN_U, PPOS);   
}

void ADE7753::DisablesIRQPowerChangeToPos(){
    UnsetBits(IRQEN_U, PPOS);   
}

void ADE7753::EnablesIRQPowerChangeToNeg(){
    SetBits(IRQEN_U, PNEG);   
}

void ADE7753::DisablesIRQPowerChangeToNeg(){
    UnsetBits(IRQEN_U, PNEG);   
}

bool ADE7753::CheckandResetActiveEnergyHalfFull(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & AEHF;
    Write16(STATUS_U, value & ~AEHF);
    return check;
}

bool ADE7753::CheckandResetSAG(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & SAG;
    Write16(STATUS_U, value & ~SAG);
    return check;
}

bool ADE7753::CheckandResetCycleEnergyAccumulationEnd(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & CYCEND;
    Write16(STATUS_U, value & ~CYCEND);
    return check;
}

bool ADE7753::CheckandResetNewWaveformData(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & WSMP;
    Write16(STATUS_U, value & ~WSMP);
    return check;
}

bool ADE7753::CheckandResetZeroCrossing(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & ZX;
    Write16(STATUS_U, value & ~ZX);
    return check;
}

bool ADE7753::CheckandResetZeroCrossingTimeout(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & ZXTO;
    Write16(STATUS_U, value & ~ZXTO);
    return check;
}

bool ADE7753::CheckZeroCrossingError(){
    if (WaitZeroCross() != 0)
        return 1;
    return 0;
}

bool ADE7753::CheckandResetTemperatureResults(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & TEMP;
    Write16(STATUS_U, value & ~TEMP);
    return check;
}

bool ADE7753::CheckandResetActiveEnergyOverflow(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & AEOF;
    Write16(STATUS_U, value & ~AEOF);
    return check;
}

bool ADE7753::CheckandResetCH2VlvlPeek(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & PKV;
    Write16(STATUS_U, value & ~PKV);
    return check;
}

bool ADE7753::CheckandResetCH1IlvlPeek(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & PKI;
    Write16(STATUS_U, value & ~PKI);
    return check;
}

bool ADE7753::CheckandResetAparentEnergyHalfFull(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & VAEHF;
    Write16(STATUS_U, value & ~VAEHF);
    return check;
}

bool ADE7753::CheckandResetAparentEnergyOverflow(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & VAEOF;
    Write16(STATUS_U, value & ~VAEOF);
    return check;
}

bool ADE7753::CheckandResetPowerChangeToPos(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & PPOS;
    Write16(STATUS_U, value & ~PPOS);
    if (check){
        Serial.println("Potency changed to Pos");
    }
    return(check);
}

bool ADE7753::CheckandResetPowerChangeToNeg(){
    unsigned long value = Read16(STATUS_U);
    bool check = value & PNEG;
    Write16(STATUS_U, value & ~PNEG);
    if (check){
        Serial.println("Potency changed to Neg");
    }
    return(check);
}

bool ADE7753::CheckResetEnds(){
    bool check = Read16(STATUS_U) & RESET;
    if (check){
        Serial.println("Reseting...");
    }
    return(check);
}

unsigned long ADE7753::ReadModeReg(){
    return Read16(MODE_U);  
}

unsigned long ADE7753::ReadStatusReg(){
    return Read16(STATUS_U);  
}

unsigned long ADE7753::ResetStatusReg(){
    return(Read16(RSTSTATUS_U));
}

long ADE7753::SetSAGLVL(long value){
    Write8(SAGLVL_U, value);
    return Read8(SAGLVL_U);        
}

long ADE7753::SetSAGCYC(long value){
    Write8(SAGCYC_U, value);
    return Read8(SAGCYC_U);        
}

long ADE7753::SetIPKLVL(long value){
    Write8(IPKLVL_U, value);
    return Read8(IPKLVL_U);        
}

long ADE7753::SetVPKLVL(long value){
    Write8(VPKLVL_U, value);
    return Read8(VPKLVL_U);        
}

long ADE7753::SetVRMSOS(long value){
    Write16(VRMSOS_S, value);
    return Read16(VRMSOS_S);        
}

long ADE7753::SetIRMSOS(long value){
    Write16(IRMSOS_S, value);
    return Read16(IRMSOS_S);        
}

unsigned long ADE7753::SetLINECYC(unsigned long value){
    Write16(LINECYC_U, value);
    return Read16(LINECYC_U);
}

float ADE7753::ReadVRMS(){  //returns a Vin CH2
    unsigned long media = 0;
    float value;
    Read24(VRMS_U);
    for (int i=0; i<60; i++){
        if (WaitZeroCross()) return 0;
        media += Read24(VRMS_U);  
    }
    media /= 60; 
    value = (media/1561400.000000*0.5);
    value -=0.015222; //offset when CH2 disabled
    value *= 0.74985;
    return value;
}
  
float ADE7753::ReadIRMS(){ //returns a Vin CH1
    unsigned long media = 0;
    float value;
    Read24(IRMS_U);
    for (int i=0; i<60; i++){
        if (WaitZeroCross()) return 0;
        media += Read24(IRMS_U);  
    }
    media /= 60; 
    value = (media/1868467.00000)*0.5;   
    value *= 0.7013;
    return value;
}

float ADE7753::ReadPERIOD(int CLKIN){  //returns period in seconds
    unsigned long reg_value;
    float period;
    reg_value = Read16(PERIOD_U);
    period = (8.0000000*reg_value)/CLKIN;
    return period;
}

float ADE7753::ReadActiveEnergy(){
    long active_value = Signed24toSigned32( Read24(AENERGY_S) );
    active_value *=(0.827/12.1031); //energy scales // W conversion
    return active_value;
}

float ADE7753::ReadApparentEnergy(){
    long apparent_value = Signed24toSigned32( Read24(VAENERGY_U) );
    apparent_value /= 12.1031; //VA conversion
    return apparent_value;
}

float ADE7753::ReadandResetActiveEnergy(){
    long active_value = Signed24toSigned32( Read24(RAENERGY_S) );
    active_value *= (0.827/12.1031); //VA conversion
    return active_value;
}

float ADE7753::ReadandResetApparentEnergy(){
    long apparent_value = Signed24toSigned32( Read24(RVAENERGY_U) );
    apparent_value /= 12.1031; //VA conversion
    return apparent_value;
}


void ADE7753::ReadFP(int half_line_cycles, float* power_factor, short* reactive_power){ //return active energy in Watt-Hour still needs calibration to work
    long active_value, reactive_value;
    unsigned long apparent_value;
    SetLINECYC(half_line_cycles);
    EnableAccumulationMode();
    delay(1);
    while (!CheckandResetCycleEnergyAccumulationEnd()) {
        delayMicroseconds(5);
    }
    while (!CheckandResetCycleEnergyAccumulationEnd()) {
        delayMicroseconds(5);
    }
    active_value = Signed24toSigned32( Read24(LAENERGY_S) );      
    apparent_value = Read24(LVAENERGY_U);
    reactive_value = Signed24toSigned32( Read24(LVARENERGY_S) );     
    DisableAccumulationMode();
    apparent_value = (apparent_value / 0.827) / 14,634946; //VA conversion
    active_value = ((active_value*active_value) / apparent_value)  / 14,634946; //energy scales // W conversion
    int reactive_signal = reactive_value / abs(reactive_value);
    *reactive_power = (active_value / apparent_value) * reactive_signal;
 
 //old values
 /*   active_value *=(0.827000/12.1031); //energy scales // W conversion
    apparent_value /= 12.103100; //VA conversion
    reactive_value *=(0.204000 / (0.827*12.1031)); //energy scales / VAr conversion
 */
    *power_factor =  ((active_value*1.000000) / apparent_value);
//    if (isnan(*power_factor)) *power_factor = 0;
//    if (*power_factor >= 1) *power_factor = 0.9999999999;
}

void ADE7753::DisplayBufferUpdate(Measurement* data, char dest, int view, boolean next)  
{
    switch (view){
      case 1:
          sprintf(&dest, "Voltage=%.1f", data->voltage);
          display_position+=next;
          break;
      case 2:
          sprintf(&dest, "Current=%.2f", data->current);
          display_position+=next;
          break;
      case 3:
          sprintf(&dest, "FP=%.2f", data->FP);
          display_position+=next;
          break;
      case 4:
          sprintf(&dest, "Frequency=%.2f", data->frequency);
          display_position+=next;
          break;
      case 5:
          sprintf(&dest, "Apparent Potency=%.0f", data->aparent_power);
          display_position+=next;
          break;
      case 6:
          sprintf(&dest, "Active Potency=%.0f", data->active_power);
          display_position+=next;
          break;
      case 7:
          sprintf(&dest, "Reactive Potency=%.0f", data->reactive_power);
          if (next) display_position = 1;
          break;
      default:
          break;
    }
}

int ADE7753::GetDisplayPosition(){
    return display_position;
}

byte ADE7753::GetTemperature(){
    CheckandResetTemperatureResults();
    SetBits(MODE_U, TEMPSEL);
    while (!CheckandResetTemperatureResults()) 1;
    return Read8(TEMP_S)*1.34;    
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
    Write16(reg, Read16(reg) & ~value);
}

unsigned long ADE7753::Read8(char reg){
    Enable();
    char b0;
    SPI.transfer(reg);
    delayMicroseconds(5);
    b0=SPI.transfer(0x81);
    delayMicroseconds(50);
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
    boolean value = 0;
    unsigned long conta_millis = millis();
    CheckandResetZeroCrossing();
    while (!CheckandResetZeroCrossing()) {
        if (millis() > (conta_millis+100)){
            Serial.println("ZX ERROR");
            value = 1;
            delay(100);
            break;
        }    
    }
    return value;
}

long ADE7753::Signed24toSigned32(long value){
    if (value & 1 << 23) {   
      value = -((~value) & 0xffffff);
    }
    return value;
}



   
