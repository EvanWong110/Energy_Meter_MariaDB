
void CreateMessage(ADE7753::Measurement atual) {
    char buff[1000] = "";
    int ponteiro;
    int soma_ponteiros = 0;
    ponteiro = snprintf(buff, 50, "{\n");
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"id\" : \"%s\",\n", atual.id);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"timestamp\" : \"%d\",\n", atual.timestamp);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"tensao\" : \"%f\",\n", atual.voltage);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"corrente\" : \"%f\",\n", atual.current);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"frequencia\" : \"%f\",\n", atual.frequency);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_at\" : \"%f\",\n", atual.active_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_re\" : \"%f\",\n", atual.reactive_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_ap\" : \"%f\",\n", atual.aparent_power);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "\"FP\" : \"%f\"\n", atual.FP);
    soma_ponteiros += ponteiro;
    ponteiro = snprintf(buff+soma_ponteiros, 50, "}");
    strcpy(msg_to_publish, buff);
}

void PublishMessage(PubSubClient client){   
    Serial.print("Publishing message: ");
    Serial.println(msg_to_publish);
    client.beginPublish("home/energymeter", String(msg_to_publish).length(), false);
    client.print(msg_to_publish);
    client.endPublish();
    Serial.println("");
}
