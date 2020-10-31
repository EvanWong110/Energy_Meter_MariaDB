import paho.mqtt.client as mqtt
import parse_config as parse
import json

configuration = parse.ConfPacket()
configs = configuration.load_config('MQTT, MQTT_TOPICS')

on_msg = None

class MQTTReceiver:
    def __init__(self):
        pass
        
    @staticmethod
    def on_connect(client, userdata, flags, rc):
        """ The callback for when the client receives a CONNACK response from the server."""
        print('Connected with result code ' + str(rc))
        for topic in configs['MQTT_TOPICS']:
            client.subscribe(configs['MQTT_TOPICS'][topic])

    @staticmethod
    def on_message(client, userdata, msg):
        """The callback for when a PUBLISH message is received from the server."""
        #print(msg.topic + ' ' + str(msg.payload))
        msg_decoded = str(msg.payload.decode("utf-8","ignore"))
        #print("Msg decoded: ", msg_decoded)
        try:
            msg_dict = json.loads(msg_decoded)
            msg_dict['topic'] = msg.topic
            #print("Dict: ", msg_dict)
            on_msg(msg_dict)
        except Exception as error:
            print("Ocorreu um erro na decodificação da mensagem JSON: ", error)

    def create_connections(self):
        client = mqtt.Client()
        host = configs['MQTT']['host_address']
        user = configs['MQTT']['user']
        passwd = configs['MQTT']['password']
        port = int (configs['MQTT']['port'])
        client.username_pw_set(user, passwd)
        client.on_connect = self.on_connect
        client.on_message = self.on_message
        client.connect(host, port)
        client.loop_forever()
        #loops at here

    
def main():
    print(configs)    
    Received = MQTTReceiver()
    Received.create_connections()

def on_msg(msg):
    pass

if __name__ == '__main__':
    main()
