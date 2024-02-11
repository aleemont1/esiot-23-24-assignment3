from flask import Flask, request
import dash
from dash import html, dcc
from dash.dependencies import Input, Output
import plotly.graph_objs as go
from collections import deque
import datetime

# Inizializza l'app Flask
server = Flask(__name__)

# Inizializza l'app Dash
app = dash.Dash(__name__, server=server)

# Definisci la struttura della dashboard
app.layout = html.Div([
    html.H1('River Monitoring Dashboard'),
    dcc.Graph(id='water-level-graph'),
    dcc.Graph(id='valve-level-graph'),
    dcc.Interval(
        id='interval-component',
        interval=1*1000,  # in milliseconds
        n_intervals=0
    ),
    html.Div(id='status-display')
])

# Inizializza una coda per memorizzare i dati
data_queue = deque(maxlen=60)

# Gestisci le richieste POST al server
@server.route('/postdata', methods=['POST'])
def get_post_data():
    global data_queue
    data = request.get_json()
    # Aggiungi il timestamp corrente ai dati
    data['timestamp'] = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    # Aggiungi i dati alla coda
    data_queue.append(data)
    return 'Success', 200

# Aggiorna il grafico del livello dell'acqua in tempo reale
@app.callback(Output('water-level-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_water_level_graph(n):
    global data_queue

    # Crea il grafico utilizzando tutti i dati nella coda
    fig = go.Figure(
        data=[
            go.Scatter(
                x=[data['timestamp'] for data in data_queue],
                y=[data['wl'] for data in data_queue],
                mode='lines+markers'
            )
        ],
        layout=go.Layout(
            title='Livello dell\'acqua',
            xaxis=dict(title='Timestamp'),
            yaxis=dict(title='Livello dell\'acqua')
        )
    )

    return fig

# Aggiorna il grafico del livello della valvola in tempo reale
@app.callback(Output('valve-level-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_valve_level_graph(n):
    global data_queue

    # Crea il grafico utilizzando tutti i dati nella coda
    fig = go.Figure(
        data=[
            go.Scatter(
                x=[data['timestamp'] for data in data_queue],
                y=[data['valveValue'] for data in data_queue],
                mode='lines+markers'
            )
        ],
        layout=go.Layout(
            title='Livello della valvola',
            xaxis=dict(title='Timestamp'),
            yaxis=dict(title='Livello della valvola')
        )
    )

    return fig

# Aggiorna lo stato del sistema
@app.callback(Output('status-display', 'children'),
              [Input('interval-component', 'n_intervals')])
def update_status_display(n):
    global data_queue
    if data_queue:
        return f"Stato del sistema: {data_queue[-1]['status']}"

if __name__ == '__main__':
    app.run_server(debug=True, port=8050)
