from flask import Flask, request
import dash
from dash import html, dcc
from dash.dependencies import Input, Output, State
import plotly.graph_objs as go
from collections import deque
import datetime
import requests
import json

# Inizializza una coda per memorizzare i dati
data_queue = deque(maxlen=60)

# Inizializza l"app Flask
server = Flask(__name__)

# Inizializza l'app Dash con il foglio di stile esterno
app = dash.Dash(__name__, server=server)
app.css.append_css({"external_url": "https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100;0,300;0,400;0,500;0,700;0,900;1,100;1,300;1,400;1,500;1,700;1,900&display=swap"})
# Definisci la struttura della dashboard
app.layout = html.Div([
    html.H1("River Monitoring Dashboard", style={"text-align": "center", "font-size": "48px"}),
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
    html.Div(id="status-display",style={"text-align": "center", "font-size": "24px"}),
    html.Div([
        html.H3("Set Valve Value"),
        html.Div([
            dcc.Slider(
            id='valveValue',
            min=0,
            max=100,
            value=0,
            marks={i: '{}%'.format(i) for i in range(0, 101, 10)},
            )], style={"width": "33%", "display": "inline-block"}),
            html.Button("Set Valve Value", id="send-valveValue", n_clicks=0, className="button-17", style={"margin-right": "1%"}),
            html.Button("Set Auto-mode", id="send-autoMode", n_clicks=0, className="button-17 button-17-red")
    ], style={"display": "flex", "justify-content": "center", "align-items": "center"}),
    html.Div(id="dummy-output", style={"display": "none"})
])

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

@app.callback([
        Output("dummy-output", "children"),
        Input("send-autoMode", "n_clicks")
        ])
def send_manualMode(n_clicks):
    url = "http://localhost:8051/api/postdata"
    if n_clicks is None:
        return [""]
    else:
        data = {
            "isManual": False
        }
        response = requests.post(url, data=json.dumps(data), headers={"Content-Type": "application/json"})
        print(response.text)
        return [f"Sent request with response: {response.text}"]

@app.callback(Output("send-valveValue", "value"),
              [Input("send-valveValue", "n_clicks")],
              [State("valveValue", "value")])
def send_valveValue(n_clicks, valveValue):
    url = "http://localhost:8051/api/postdata"
    if n_clicks > 0:
        data = {
            "valveValue": valveValue,
            "isManual": True
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
                mode="lines+markers",
                line=dict(color="blue")
            )
        ],
        layout=go.Layout(
            title=dict(text="Livello dell'acqua", font=dict(size=24, family="Roboto"), x=0.5),
            xaxis=dict(title="Ora"),
            yaxis=dict(title="Livello dell'acqua")
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
                mode="lines+markers",
                line=dict(color="red")
            )
        ],
        layout=go.Layout(
            title=dict(text="Livello della valvola", font=dict(size=24, family="Roboto"), x=0.5),
            xaxis=dict(title="Ora"),
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
