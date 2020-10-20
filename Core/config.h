/* * Nome do arquivo: config.h
 *  Este arquivo armazena os principais defines
 *  
 */

#define time_between_uploads 7000 //ms                        // Tempo entre uploads
#define debaunce_time 250                                      // Debaunce da chave do display
#define $id "0"

#define serial_speed 115200        // Serial port speed

const char* ssid = "Home";         // WiFi network name
const char* wifi_password = "07111993"; // WiFi network password

char* mqtt_server = "192.168.000.251";  // IP of the MQTT broker
const char* mqtt_username = "energymeter"; // MQTT username
const char* mqtt_password = "energymeter"; // MQTT password
const char* clientID = "client_livingroom"; // MQTT client ID

void verificar_comando_serial();

WiFiClient wifiClient;

void connect_WIFI(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  display_msg("Inicializando...");

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     verificar_comando_serial();
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

PubSubClient client(mqtt_server, 1883, wifiClient); 

void connect_MQTT(){
  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  while (!client.connect(clientID, mqtt_username, mqtt_password)) {
     Serial.println("Connecting to MQTT Broker!");
     verificar_comando_serial();
  }
}

boolean threadTo(unsigned long* last_time, unsigned long default_time) {  //cria rotinas que rodam a cada ciclo de tempo especifico
    long now = millis();
    if (now - *last_time > default_time) {
        *last_time = now;
        return true;
    }  
    else 
        return false;  
}

long setClock() {        // Set time via NTP, as required for x.509 validation  
  configTime(0 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
  }
  Serial.println("Done.");
  return now;  
}

// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";     // Servidores de fuso horário
const char* ntp_secondary = "time.nist.gov";

const int columns_number=9;

void createMessage(char * msg_to_publish, mensagem atual) {
Serial.println("Creating message: ");
char buff[1000] = "";
int ponteiro;
int soma_ponteiros = 0;
ponteiro = snprintf(buff, 50, "{\n");
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"id\" : \"%s\",\n", atual.id);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"timestamp\" : \"%d\",\n", atual.timestamp);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"tensao\" : \"%f\",\n", atual.tensao);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"corrente\" : \"%f\",\n", atual.corrente);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"frequencia\" : \"%f\",\n", atual.frequencia);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_at\" : \"%f\",\n", atual.pot_at);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_re\" : \"%f\",\n", atual.pot_re);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"pot_ap\" : \"%f\",\n", atual.pot_ap);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "\"FP\" : \"%f\"\n", atual.FP);
soma_ponteiros += ponteiro;
ponteiro = snprintf(buff+soma_ponteiros, 50, "}");
strcpy(msg_to_publish, buff);
}

void publish_message(char* msg_to_publish){   //Publica a string no serviço da AWS
    Serial.print("Publishing message: ");
    Serial.println(msg_to_publish);
    client.beginPublish("home/energymeter", String(msg_to_publish).length(), false);
    client.print(msg_to_publish);
    client.endPublish();
    Serial.println("");
}

void configADE(){
   write16(MODE, MODE_VALUE_16BITS);
   write16(IRQEN, IRQEN_VALUE_16BITS);              
   write16(LINECYC, LINECYC_VALUE_16BITS);
// write16(IRMSOS, IRMSOS_VALUE_12BITS);            //offset canal 1 tensao
// write16(VRMSOS, VRMSOS_VALUE_12BITS);            //offset canal 2 tensao
   }

void ler_serial(char * mensagem){
   char message[100];
   int charsRead = 0;
   if (Serial.available() > 0) {      // Is the Serial object sending something?
      charsRead = Serial.readBytesUntil('\n', message, sizeof(message) - 1);   // Yep, so read it...
      message[charsRead] = '\0';                        // Now make it a C string...
      strcpy(mensagem, message);
      Serial.print("Comando recebido: ");
      Serial.println(mensagem);
      }
   }

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
