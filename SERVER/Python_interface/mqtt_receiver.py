import paho.mqtt.client as mqtt
import parse_config as parse

configuration = parse.ConfPacket()
configs = configuration.load_config()    

def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    for topic_address in configs['MQTT']['TOPICS']:
        topic = configs['MQTT']['TOPICS'][topic_address]
        client.subscribe(topic)

class MQTTConn:
    def __init__(self, on_message):
        #self.variable = value
        self.on_message = on_message
        pass

    def create_connections(self):
        #print(configs)
        client = mqtt.Client()
        host = configs['MQTT']['HOST_ADDRESS']
        user = configs['MQTT']['USER']
        passwd = configs['MQTT']['PASSWORD']
        client.username_pw_set(user, passwd)
        client.on_connect = on_connect
        client.on_message = self.on_message
        client.connect(host, 1883)
        client.loop_forever()
    
def on_message_f(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    mensagem_b = str(msg.payload.decode("utf-8","ignore"))
    print(mensagem_b)


def main():
    Received = MQTTConn(on_message_f)
    Received.create_connections()

if __name__ == '__main__':
    main()
