from merger import ROI
import plotly.graph_objects as go
from plotly.subplots import make_subplots

# Figure with 2 Y axes
fig = make_subplots(specs=[[{"secondary_y": True}]])

# Add Profit bar
fig.add_trace(
    go.Bar(x=ROI.index, y=ROI['profit'], name='Profit ($)'),
    secondary_y=False
)

# Add ROI line
fig.add_trace(
    go.Scatter(x=ROI.index, y=ROI['roi'], name='ROI (%)', mode='lines+markers'),
    secondary_y=True
)

# Layout
fig.update_layout(
    title_text="Efficienty analysis categorically",
    xaxis_title="Product category",
    template="plotly_white",
)

# Update titles for Y axes
fig.update_yaxes(title_text="<b>Profit</b> in $", secondary_y=False)
fig.update_yaxes(title_text="<b>ROI</b> in %", secondary_y=True)

fig.show()