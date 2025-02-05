import network
import time
import sys
from umqtt.simple import MQTTClient

# Configuration Wi-Fi et MQTT
ssid = "Wokwi-GUEST"  # SSID du Wi-Fi
password = ""         # Mot de passe du Wi-Fi (vide pour Wokwi-GUEST)
mqtt_server = "broker.hivemq.com"  # Broker MQTT public
mqtt_port = 1883      # Port MQTT non sécurisé
topic = "esp32/chat"  # Sujet partagé pour les ESP32
client_id = "ESP32-#2 : "  # Identifiant unique du client MQTT

# Configuration Wi-Fi
def connect_to_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)

    print("Connexion au WiFi...")
    while not wlan.isconnected():
        print(".", end="")
        time.sleep(1)
    print("\nConnecté au WiFi")
    print("Adresse IP:", wlan.ifconfig()[0])

# Callback pour la réception des messages MQTT
def mqtt_callback(topic, msg):
    message = msg.decode('utf-8')
    if message.startswith(client_id):
        return  # Ignorer les messages publiés par ce client
    print("Reçu:", message)
    print("---")

# Configuration MQTT
def connect_to_mqtt():
    client = MQTTClient(client_id, mqtt_server, mqtt_port)
    client.set_callback(mqtt_callback)

    while True:
        try:
            print("Connexion au broker MQTT...")
            client.connect()
            print("Connecté au broker MQTT")
            client.subscribe(topic)
            print("Abonné au sujet:", topic)
            client.publish(topic, (client_id + "connected!").encode('utf-8'))
            print("---")
            return client
        except Exception as e:
            print("Échec de connexion:", str(e))
            time.sleep(2)

# Vérifie si une entrée est disponible depuis la console
def input_available():
    import select
    return select.select([sys.stdin], [], [], 0)[0]

# Fonction principale
def main():
    connect_to_wifi()
    mqtt_client = connect_to_mqtt()

    while True:
        try:
            mqtt_client.check_msg()  # Vérifier les nouveaux messages MQTT
            
            if input_available():  # Si un message est prêt à être lu depuis la console
                message = input().strip()  # Lire le message utilisateur
                full_message = f"{client_id}: {message}"
                mqtt_client.publish(topic, full_message.encode('utf-8'))
                print("Publié:", full_message)
                print("---")
        
        except OSError:
            print("Erreur de connexion, tentative de reconnexion...")
            mqtt_client = connect_to_mqtt()

# Lancement du programme
try:
    main()
except KeyboardInterrupt:
    print("Programme arrêté.")
