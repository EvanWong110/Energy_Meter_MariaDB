import configparser
import os.path

ROOT_DIR = os.path.dirname(os.path.abspath(__file__)) # This is your Project Root
CONFIG_PATH = os.path.join(ROOT_DIR, 'config.ini')  

def carrega_config():
    parser = configparser.ConfigParser()

    try:
        parser.read(CONFIG_PATH)
    except Exception as error:
        print ('Erro: ', error)

    if (parser.sections() == []):
        raise NameError("Arquivo config.ini corrompido ou nao encontrado.")
  
    items = {'MQTT':{}, 'DATABASE':{}}

    try:
        items['MQTT']['HOST_ADDRESS'] = parser['MQTT']['MQTT_HOST']
        items['MQTT']['USER'] = parser['MQTT']['MQTT_USER']
        items['MQTT']['PASSWORD'] = parser['MQTT']['MQTT_PASSWORD']
        items['MQTT']['TOPICS'] = dict()
        for idx, key in enumerate(parser['MQTT_TOPICS']):
            items['MQTT']['TOPICS'][idx] = parser['MQTT_TOPICS'][key]

        items['DATABASE']['HOST_ADDRESS'] = parser['DATABASE']['DATABASE_HOST']
        items['DATABASE']['USER'] = parser['DATABASE']['DATABASE_USER']
        items['DATABASE']['PASSWORD'] = parser['DATABASE']['DATABASE_PASSWORD']
        items['DATABASE']['DATABASES'] = dict()
        for idx, key in enumerate(parser['MARIADB_DATABASES']):
            items['DATABASE']['DATABASES'][idx] = parser['MARIADB_DATABASES'][key]
      
    except Exception as error:
        print ('Erro no arquivo config.ini: ', error)
    return items

items = carrega_config()

def main():
    print (items)

if __name__ == '__main__':
    main()
    pass
