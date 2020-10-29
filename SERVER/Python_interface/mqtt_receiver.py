import paho.mqtt.client as mqtt
#import json_converter
import config

def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    for topic_address in config.items['MQTT']['TOPICS']:
        topic = config.items['MQTT']['TOPICS'][topic_address]
        client.subscribe(topic)

def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    mensagem_b = str(msg.payload.decode("utf-8","ignore"))
    print(mensagem_b)

def create_conections():
    client = mqtt.Client()
    host = config.items['MQTT']['HOST_ADDRESS']
    user = config.items['MQTT']['USER']
    passwd = config.items['MQTT']['PASSWORD']
    client.username_pw_set(user, passwd)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(host, 1883)
    client.loop_forever()

def main():
    create_conections()
if __name__ == '__main__':
    main()
