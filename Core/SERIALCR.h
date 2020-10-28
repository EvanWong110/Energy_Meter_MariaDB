#ifndef SERIALCR_H
#define SERIALCR_H

#include "Arduino.h"
#include "ADE7753CR.h"

class Serials {
    public:
    void ExecutaComandoSerial(ADE7753* ADE7753);
    private:
    void ReceiveSerial(char* received);
    
};

#endif
