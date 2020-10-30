import mqtt_receiver

def do_this(msg):
    print(msg)

def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload))
    mensagem_recebida = str(msg.payload.decode("utf-8","ignore"))
    do_this(mensagem_recebida)

Received = mqtt_receiver.MQTTConn(on_message)
Received.create_connections()







