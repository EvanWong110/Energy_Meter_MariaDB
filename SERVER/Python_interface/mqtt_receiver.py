import paho.mqtt.client as mqtt
import config

def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    client.subscribe(topic)

def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    mensagem_b = str(msg.payload.decode("utf-8","ignore"))
    print(mensagem_b)

def new_client(client, host, user, passwd):
    client = mqtt.Client()
    client.username_pw_set(user, passwd)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(host, 1883)
    client.loop_forever()

def create_conections():
    for mqtt_config in config.items['MQTT']:
        user = config.items['MQTT'][mqtt_config]['USER']
        passwd = config.items['MQTT'][mqtt_config]['PASSWORD']
        host = config.items['MQTT'][mqtt_config]['HOST_ADDRESS']
        global topic
        topic = config.items['MQTT'][mqtt_config]['TOPIC']
        new_client(mqtt_config, host, user, passwd)

def main():
    create_conections()

if __name__ == '__main__':
    main()
