from flask import Flask, request
import dash
from dash import html, dcc
from dash.dependencies import Input, Output, State
import plotly.graph_objs as go
from collections import deque
import datetime
import requests
import json

# Inizializza l"app Flask
server = Flask(__name__)

# Inizializza l"app Dash
app = dash.Dash(__name__, server=server)

# Definisci la struttura della dashboard
app.layout = html.Div([
    html.H1("River Monitoring Dashboard"),
    html.Div([
        html.Div([
            dcc.Graph(id="water-level-graph"),
        ], style={"width": "50%", "display": "inline-block"}),
        html.Div([
            dcc.Graph(id="valve-level-graph"),
        ], style={"width": "50%", "display": "inline-block"})
    ]),
    dcc.Interval(
        id="interval-component",
        interval=1*1000,  # in milliseconds
        n_intervals=0
    ),
    html.Div(id="status-display"),
    html.Div([
        dcc.Slider(
        id='valveValue',
        min=0,
        max=180,
        value=0,
        marks={i: '{}'.format(i) for i in range(0, 181, 20)},  # Etichette ogni 20 unità
        )], style={"width": "50%", "display": "inline-block"}),
        html.Button("Set Valve Value", id="send-valveValue", n_clicks=0)
])

# Inizializza una coda per memorizzare i dati
data_queue = deque(maxlen=60)

# Gestisci le richieste POST al server
@server.route("/api/systemdata", methods=["POST"])
def get_post_data():
    global data_queue
    data = request.get_json()
    #Ottieni i valori numerici da wl e valveValue
    data["wl"] = float(data["wl"])
    data["valveValue"] = int(data["valveValue"])
    # Add the current timestamp to the data
    # Aggiungi il timestamp corrente ai dati
    data["timestamp"] = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    # Aggiungi i dati alla coda
    data_queue.append(data)
    return "Success", 200

@app.callback(Output("send-valveValue", "value"),
              [Input("send-valveValue", "n_clicks")],
              [State("valveValue", "value")])
def send_valveValue(n_clicks, valveValue):
    url = "http://localhost:8051/api/postdata"
    if n_clicks > 0:
        data = {
            "valveValue": valveValue
        }
        response = requests.post(url, data=json.dumps(data), headers={"Content-Type": "application/json"})
        print(response.text)

# Aggiorna il grafico del livello dell'acqua in tempo reale
@app.callback(Output("water-level-graph", "figure"),
              [Input("interval-component", "n_intervals")])
def update_water_level_graph(n):
    global data_queue

    # Crea il grafico utilizzando tutti i dati nella coda
    fig = go.Figure(
        data=[
            go.Scatter(
                x=[data["timestamp"] for data in data_queue],
                y=[data["wl"] for data in data_queue],
                mode="lines+markers"
            )
        ],
        layout=go.Layout(
            title="Livello dell\'acqua",
            xaxis=dict(title="Timestamp"),
            yaxis=dict(title="Livello dell\'acqua")
        )
    )

    return fig

# Aggiorna il grafico del livello della valvola in tempo reale
@app.callback(Output("valve-level-graph", "figure"),
              [Input("interval-component", "n_intervals")])
def update_valve_level_graph(n):
    global data_queue

    # Crea il grafico utilizzando tutti i dati nella coda
    fig = go.Figure(
        data=[
            go.Scatter(
                x=[data["timestamp"] for data in data_queue],
                y=[data["valveValue"] for data in data_queue],
                mode="lines+markers"
            )
        ],
        layout=go.Layout(
            title="Livello della valvola",
            xaxis=dict(title="Timestamp"),
            yaxis=dict(title="Livello della valvola")
        )
    )

    return fig

# Aggiorna lo stato del sistema
@app.callback(Output("status-display", "children"),
              [Input("interval-component", "n_intervals")])
def update_status_display(n):
    global data_queue
    if data_queue:
        return f'Stato del sistema: {data_queue[-1]["status"]}'

if __name__ == "__main__":
    app.run_server(debug=True, port=8050)
