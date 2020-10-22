#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <PubSubClient.h>     // Biblioteca para publicacao MQTT na AWS
#include "ADE7753CR.h"

class Publisher
{
    public:
        void CreateMessage(ADE7753::Measurement atual);
        void PublishMessage(PubSubClient client);

    private:
        char msg_to_publish[1000];
};


#endif // PUBLISHER_H
