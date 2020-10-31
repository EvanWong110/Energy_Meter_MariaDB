import parse_config as parse

configuration = parse.ConfPacket()
configs = configuration.load_config('MARIADB_DATABASE, MARIADB_DATABASES')

import mysql.connector

class database_pusher:
    def __init__(self):
        pass
    
    def connect(self):
        pass

for database in configs['MARIADB_DATABASES']:
    database = mysql.connector.connect(user=configs['MARIADB_DATABASE']['user'], password=configs['MARIADB_DATABASE']['password'],
                                        host=configs['MARIADB_DATABASE']['host'],
                                        database=configs['MARIADB_DATABASES'][database])
    cursor=database.cursor()
    add_data = "INSERT INTO data (id, timestamp, tensao, corrente, FP, pot_at, pot_re, pot_ap, freq, active_energy, apparent_energy) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"
    data = (j_data['id'], j_data['timestamp'], j_data['tensao'], j_data['corrente'], j_data['FP'], j_data['pot_at'], j_data['pot_re'], j_data['pot_ap'], j_data['frequencia'], j_data['active_energy'], j_data['apparent_energy'] )
    #print(data)
    cursor.execute(add_data, data)
    database.commit()
    cursor.close()
    database.close()
