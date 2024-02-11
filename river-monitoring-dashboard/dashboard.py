from flask import Flask, request
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go
from collections import deque

# Inizializza l'app Flask
server = Flask(__name__)

# Inizializza l'app Dash
app = dash.Dash(__name__, server=server)

# Definisci la struttura della dashboard
app.layout = html.Div([
    html.H1('River Monitoring Dashboard'),
    dcc.Graph(id='live-update-graph'),
    dcc.Interval(
        id='interval-component',
        interval=1*1000,  # in milliseconds
        n_intervals=0
    )
])

# Inizializza una coda per memorizzare i dati
data_queue = deque(maxlen=60)

# Gestisci le richieste POST al server
@server.route('/postdata', methods=['POST'])
def get_post_data():
    global data_queue
    data = request.get_json()
    # Aggiungi i dati alla coda
    data_queue.append(data)
    return 'Success', 200

# Aggiorna il grafico in tempo reale
@app.callback(Output('live-update-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_graph_live(n):
    global data_queue

    # Crea il grafico utilizzando tutti i dati nella coda
    fig = go.Figure(
        data=[
            go.Scatter(
                x=list(range(len(data_queue))),
                y=[data['wl'] for data in data_queue],
                mode='lines+markers'
            )
        ]
    )

    return fig

if __name__ == '__main__':
    app.run_server(debug=True)
