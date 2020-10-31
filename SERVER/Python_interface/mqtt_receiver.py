import paho.mqtt.client as mqtt
import parse_config as parse
import json

configuration = parse.ConfPacket()
configs = configuration.load_config('MQTT, MQTT_TOPICS')

def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    for topic in configs['MQTT_TOPICS']:
        client.subscribe(configs['MQTT_TOPICS'][topic])

def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    msg_decoded = str(msg.payload.decode("utf-8","ignore"))
    print("Msg decoded: ", msg_decoded)
    try:
        msg_dict = json.loads(msg_decoded)
        msg_dict['topic'] = msg.topic
        print("Dict: ", msg_dict)
    except Exception as error:
        print("Ocorreu um erro na decodificação da mensagem JSON: ", error)

class MQTTReceiver:
    def __init__(self):
        pass     

    def on_received(self, func):
        func()
        
    def create_connections(self):
        client = mqtt.Client()
        print("funcao: ",self.teste)
        self.teste()
        host = configs['MQTT']['host_address']
        user = configs['MQTT']['user']
        passwd = configs['MQTT']['password']
        client.username_pw_set(user, passwd)
        client.on_connect = on_connect
        client.on_message = on_message
        client.connect(host, 1883)
        client.loop_forever()
        #loops at here
   
def testando():
    print("teste")

def main():
    print(configs)    
    Received = MQTTReceiver()
    Received.teste = testando
    Received.create_connections()

if __name__ == '__main__':
    main()
