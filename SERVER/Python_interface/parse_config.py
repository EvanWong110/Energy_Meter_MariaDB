import configparser
import os.path

ROOT_DIR = os.path.dirname(os.path.abspath(__file__)) # This is your Project Root
CONFIG_PATH = os.path.join(ROOT_DIR, 'config.ini')  

class ConfPacket:
    def __init__(self):
        pass

    def load_config(self):
        parser = configparser.ConfigParser()

        try:
            parser.read(CONFIG_PATH)
        except Exception as error:
            print ('Erro: ', error)

        if (parser.sections() == []):
            raise NameError("Arquivo config.ini corrompido ou nao encontrado.")
    
        configs = {'MQTT':{}, 'DATABASE':{}}

        try:
            configs['MQTT']['HOST_ADDRESS'] = parser['MQTT']['MQTT_HOST']
            configs['MQTT']['USER'] = parser['MQTT']['MQTT_USER']
            configs['MQTT']['PASSWORD'] = parser['MQTT']['MQTT_PASSWORD']
            configs['MQTT']['TOPICS'] = dict()
            for idx, key in enumerate(parser['MQTT_TOPICS']):
                configs['MQTT']['TOPICS'][idx] = parser['MQTT_TOPICS'][key]

            configs['DATABASE']['HOST_ADDRESS'] = parser['DATABASE']['DATABASE_HOST']
            configs['DATABASE']['USER'] = parser['DATABASE']['DATABASE_USER']
            configs['DATABASE']['PASSWORD'] = parser['DATABASE']['DATABASE_PASSWORD']
            configs['DATABASE']['DATABASES'] = dict()
            for idx, key in enumerate(parser['MARIADB_DATABASES']):
                configs['DATABASE']['DATABASES'][idx] = parser['MARIADB_DATABASES'][key]
        
        except Exception as error:
            print ('Erro no arquivo config.ini: ', error)
        return configs


def main():
    configs = ConfPacket()
    items = configs.load_config()
    print (items)

if __name__ == '__main__':
    main()
