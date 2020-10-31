import mqtt_receiver
import mysql.connector

def on_msg(msg):
    print(msg)

mqtt_receiver.on_msg = on_msg
Received = mqtt_receiver.MQTTReceiver()
Received.create_connections()



cnx = mysql.connector.connect(user='admin', password='password',
                              host='192.168.0.251',
                              database='energymeter')
cursor=cnx.cursor()

add_data = "INSERT INTO data (id, timestamp, tensao, corrente, FP, pot_at, pot_re, pot_ap, freq, active_energy, apparent_energy) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"
data = (j_data['id'], j_data['timestamp'], j_data['tensao'], j_data['corrente'], j_data['FP'], j_data['pot_at'], j_data['pot_re'], j_data['pot_ap'], j_data['frequencia'], j_data['active_energy'], j_data['apparent_energy'] )
#print(data)

cursor.execute(add_data, data)
cnx.commit()
cursor.close()
cnx.close()



def main():
    pass

if __name__ == '__main__':
    main()





