import configparser

def carrega_config():
    parser = configparser.ConfigParser()

    try:
        parser.read('config.ini')
    except Exception as error:
        print ('Erro: ', error)

    items = {'MQTT':{}, 'MARIADB':{}}

    try:
        topics = (parser['DEFAULT']['MQTT_ARRAY'].split(', '))
        for item in topics:
            items['MQTT'][item] = dict()
            items['MQTT'][item]['HOST_ADDRESS'] = parser[item]['HOST_ADDRESS']
            items['MQTT'][item]['USER'] = parser[item]['USER']
            items['MQTT'][item]['PASSWORD'] = parser[item]['PASSWORD']
            items['MQTT'][item]['TOPIC'] = parser[item]['TOPIC']
            
        topics = (parser['DEFAULT']['MARIADB_ARRAY'].split(', '))
        for item in topics:
            items['MARIADB'][item] = dict()
            items['MARIADB'][item]['HOST_ADDRESS'] = parser[item]['HOST_ADDRESS']
            items['MARIADB'][item]['USER'] = parser[item]['USER']
            items['MARIADB'][item]['PASSWORD'] = parser[item]['PASSWORD']
            items['MARIADB'][item]['DATABASE'] = parser[item]['DATABASE']
    except Exception as error:
        print ('Erro no arquivo config.ini: ', error)
    return items

items = carrega_config()

def main():
    print (items)

if __name__ == '__main__':
    main()
