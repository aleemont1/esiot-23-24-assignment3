import requests
import json
import random
import time

# URL del server a cui inviare i dati
url = 'http://127.0.0.1:8050/postdata'

while True:
    # Genera valori casuali per wl e valveValue
    wl = random.randint(1, 100)
    valveValue = random.randint(1, 100)

    # Imposta lo status a "SAMPLE_STATUS"
    status = "SAMPLE_STATUS"

    # Crea il payload JSON
    payload = {
        'wl': wl,
        'status': status,
        'valveValue': valveValue
    }

    # Invia la richiesta POST
    response = requests.post(url, data=json.dumps(payload), headers={'Content-Type': 'application/json'})

    # Stampa la risposta del server
    print(response.text)

    # Aspetta un secondo prima di inviare i dati successivi
    time.sleep(1)
