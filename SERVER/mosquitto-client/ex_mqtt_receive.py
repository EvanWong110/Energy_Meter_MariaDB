import paho.mqtt.client as mqtt
import json

MQTT_ADDRESS = '192.168.0.251'
MQTT_USER = 'energymeter'
MQTT_PASSWORD = 'energymeter'
MQTT_TOPIC = 'home/energymeter'


def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    mensagem_b = str(msg.payload.decode("utf-8","ignore"))
    mensagem_json = json.loads(mensagem_b)
    print(mensagem_json)
    print(mensagem_json['tensao'])

def main():
    mqtt_client = mqtt.Client()
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_ADDRESS, 1883)
    mqtt_client.loop_forever()


if __name__ == '__main__':
    print('MQTT to InfluxDB bridge')
    main()
