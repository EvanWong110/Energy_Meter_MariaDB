
#include "PUBLISHERCR.h"

void Publisher::CreateMessage(char* dev_id, char* dev_abstract, ADE7753::Measurement data) {
    char buff[1000] = "";
    int ponteiro;
    int soma_ponteiros = 0;
    ponteiro = snprintf(buff, 50, "{\n");
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"id\" : \"%s\",\n", dev_id);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"abstract\" : \"%s\",\n", dev_abstract);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"timestamp\" : \"%d\",\n", data.timestamp);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"temp\" : \"%d\",\n", data.temp);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"eventos\" : \"%d\",\n", data.events);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"tensao\" : \"%.1f\",\n", data.voltage);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"corrente\" : \"%.1f\",\n", data.current);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"frequencia\" : \"%.2f\",\n", data.frequency);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_at\" : \"%d\",\n", data.active_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_re\" : \"%d\",\n", data.reactive_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_ap\" : \"%d\",\n", data.aparent_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"FP\" : \"%.2f\",\n", data.FP);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"active_energy\" : \"%d\",\n", data.active_energy);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"apparent_energy\" : \"%d\"\n", data.apparent_energy);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "}");
    strcpy(msg_to_publish, buff);
    Serial.println(msg_to_publish);
}

void Publisher::PublishMessage(char* dev_id, char* dev_abstract, ADE7753::Measurement atual, PubSubClient* pubsubclient, const char* mqtt_topic){   
    CreateMessage(dev_id, dev_abstract, atual);
    Serial.print("Publishing message...");
    pubsubclient->beginPublish(mqtt_topic, String(msg_to_publish).length(), false);
    pubsubclient->print(msg_to_publish);
    pubsubclient->endPublish();
    Serial.println(" OK.");
}
