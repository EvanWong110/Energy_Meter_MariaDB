#ifndef SERIALCR_H
#define SERIALCR_H

#include "Arduino.h"
#include "ADE7753CR.h"

class Serials {
    public:
    void ExecutaComandoSerial();
    private:
    void ReceiveSerial(char* received);
    
};

#endif
