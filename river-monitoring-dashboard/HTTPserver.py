import requests
import json
import random
import time
from http.server import BaseHTTPRequestHandler, HTTPServer
import threading

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        data = json.loads(post_data)

        print("Received data: ", data)

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b'Success')

# Inizializza il server HTTP
httpd = HTTPServer(('localhost', 8051), SimpleHTTPRequestHandler)

# Avvia il server HTTP in un thread separato
thread = threading.Thread(target=httpd.serve_forever)
thread.start()

# URL del server a cui inviare i dati
url = 'http://127.0.0.1:8050/api/systemdata'

while True:
    # Genera valori casuali per wl e valveValue
    wl = random.randint(1, 100)
    valveValue = random.randint(1, 100)

    # Imposta lo status a "SAMPLE_STATUS"
    status = "SAMPLE_STATUS"

    # Crea il payload JSON
    payload = {
    "wl": wl,
    "status": status,
    "valveValue": valveValue
}

    print("Sending payload: ", payload)
    # Invia la richiesta POST
    response = requests.post(url, data=json.dumps(payload), headers={'Content-Type': 'application/json'})

    # Stampa la risposta del server
    print(response.text)

    # Aspetta un secondo prima di inviare i dati successivi
    time.sleep(1)
