import paho.mqtt.client as mqtt
import mysql.connector
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
    j_data = json.loads(mensagem_b)
    print(j_data)

    cnx = mysql.connector.connect(user='admin', password='password',
                              host='localhost',
                              database='energymeter')
    cursor=cnx.cursor()

    add_data = "INSERT INTO data (id, timestamp, tensao, corrente, FP, pot_at, pot_re, pot_ap, freq) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s)"
    data = (j_data['id'], j_data['timestamp'], j_data['tensao'], j_data['corrente'], j_data['FP'], j_data['pot_at'], j_data['pot_re'], j_data['pot_ap'], j_data['frequencia'] )
    print(data)

    cursor.execute(add_data, data)
    cnx.commit()
    cursor.close()
    cnx.close()

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

