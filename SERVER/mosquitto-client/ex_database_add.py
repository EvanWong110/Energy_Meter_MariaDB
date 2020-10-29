import mysql.connector

cnx = mysql.connector.connect(user='admin', password='password',
                              host='localhost',
                              database='energymeter')

cursor=cnx.cursor()
add_data = "INSERT INTO data (id, timecode, tensao, corrente, pot_at, pot_ap, pot_re) VALUES(%s, %s, %s, %s, %s, %s, %s)"
data = (0, 3333333, 220, 20, 0, 1, 2)

cursor.execute(add_data, data)
cnx.commit()
cursor.close()
cnx.close()
