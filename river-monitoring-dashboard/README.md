# River monitoring dashboard

Install requirements with:
`pip install -r requirements.txt`

Execute with:
`python river-monitoring-dashboard.py`

Open a browser page and type:
`localhost:8050`

Note: The HTTPServer is a test application, it POSTs random values on 8050 port in the correct format to visualize sample data in the dashboard.

The application receives data on port 8050, and sends the Valve Value on port 8051 when the button is clicked.
