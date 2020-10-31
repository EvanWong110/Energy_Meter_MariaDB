import mqtt_receiver
import json

class JsonMessage:
    def __init__(self):
        pass

    def strtojson(self, msg_decoded, topic):    
        try:
            msg_dict = json.loads(msg_decoded)
            msg_dict['topic'] = topic
            print("Dict: ", msg_dict)
        except Exception as error:
            print("Ocorreu um erro na decodificação da mensagem JSON: ", error)

jsonmessage = JsonMessage()

def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    msg_decoded = str(msg.payload.decode("utf-8","ignore"))
    print ("Received: ", msg_decoded)
    jsonmessage.strtojson(msg_decoded, msg.topic)

Received = mqtt_receiver.MQTTConn(on_message)
Received.create_connections()


def main():
    pass

if __name__ == '__main__':
    main()





