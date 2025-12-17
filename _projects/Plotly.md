---
layout: page_Visualisation
title: Visualisations réactives, Matplotlib - Seaborn
description:
img: assets/img/12.jpg
importance: 3
category: ADD
related_publications: False
---

# Plotly

## Introduction 
`Plotly` est une librairie Python permettant de créer des graphiques interactifs. Avec un graphique Plotly, il est possible d’afficher des infobulles sur des points d’intérêt, de zoomer sur des zones spécifiques, etc... Vous trouverez la doc [ici](https://docs.plotly.com/).

Plotly repose sur la célèbre librairie JavaScript `d3.js` et fournit un wrapper `Python`, ce qui permet de construire directement depuis Python des graphiques interactifs et esthétiquement remarquables.

Il existe deux principales manières d’utiliser la librairie Python Plotly : 
- `plotly.express` : une API user-friendly et haut niveau, qui exploite les capacités graphiques de Plotly pour faciliter la création rapide de graphiques. Son approche simplifiée permet aux utilisateurs de générer facilement une grande variété de types de graphiques avec un minimum de code.

- `plotly.graph_objects` : une API qui offre un niveau de contrôle et de personnalisation plus fins. Il faut cependant un peu plus de code pour créer le même graphique par rapport à `plotly.express`, mais cette API reste très accessible.

## Exemple d'utilisation

Dans cet exemple nous allons construire un graphique en *chandelier japonais* pour représenter des données financières. On commence à importer les différents package, notamment `yfinance` (yahoo finance). 


```python
import plotly.graph_objects as go
import yfinance as yf

# Define the stock symbol and date range
stock_symbol = "GOOGL"  # Example: Google
start_date = "2021-01-01"
end_date = "2025-03-30"

# Load data
stock_data = yf.download(stock_symbol,
                         start=start_date, end=end_date)
stock_data.columns = ['_'.join(col) for col in stock_data.columns]
```

```python
fig = go.Figure(data=[go.Candlestick(
    x=stock_data.index,
    open=stock_data['Open_GOOGL'],
    high=stock_data['High_GOOGL'],
    low=stock_data['Low_GOOGL'],
    close=stock_data['Close_GOOGL'],
    increasing_line_color='purple',
    decreasing_line_color='orange'
)])

# Mask a default range slider
fig.update_layout(xaxis_rangeslider_visible=True)

# Set layout size
fig.update_layout(
    autosize=False,
    width=700,
    height=500)

fig.show()
```

<iframe
    src="/notebooks/random/candlestick-plotly-basic.html" 
    width="700" 
    height="500" 
    title="candlestick with plotly 2" 
    style="border:none">
</iframe>

# Folium 
## Introduction

`Folium` est une bibliothèque `Python` dédiée à la création de cartes interactives basées sur `Leaflet.js`. Elle permet de visualiser facilement des données géographiques (points, polygones, couches, marqueurs, heatmaps, etc.) directement dans un navigateur web ou un notebook Jupyter. `Folium` est particulièrement appréciée en data science et en géospatial car elle combine la simplicité de Python avec la puissance des cartes web interactives, sans nécessiter de connaissances approfondies en JavaScript. La doc est disponible [ici](https://python-visualization.github.io/folium/latest/). 

## Exemple pratique : disponibilité des vélo'v à Lyon

Nous allons représenter la localisation des stations Vélo'v dans la métropole de Lyon. Celles-ci sont disponibles en open data sur le [site du Grand Lyon](https://data.grandlyon.com/portail/fr/jeux-de-donnees/stations-velo-v-metropole-lyon-disponibilites-temps-reel/info) et sur [data.gouv](https://www.data.gouv.fr/datasets/stations-velov-de-la-metropole-de-lyon-disponibilites-temps-reel/).

Commencons par importer les données et les packages dont nous aurons besoins à savoir `folium` et `pandas`. Notez qu'il existe aussi [geopandas](https://geopandas.org/en/stable/), une version de `pandas` adaptée aux données géographiques. Par souci de simplicité nous ne l'aborderons pas ici. 

```python
import folium
import pandas as pd
from folium.plugins import MarkerCluster

velov_data = "https://www.data.gouv.fr/api/1/datasets/r/839491c5-35a0-4520-b4e5-1552fe5d9d68"
stations = pd.read_csv(velov_data)
```

```python
# Coordonnées de Lyon
lyon_coords = [45.7640, 4.8357]

# Création de la carte
carte_lyon = folium.Map(
    location=lyon_coords,
    zoom_start=13,
    tiles="OpenStreetMap"
)
```

Nous allons maintenant ajouter une par une les differentes stations. Notez que nous utilisons un objet appelé `MarkerCluster()`. C'est ce qui permettra lorsque l'on dezoom/zoom de degrouper/grouper les différentes stations afin d'obtenir un affichage moins chargé. Notez que les `marker` possède deux attributs assez important pour une figure interactive : 

- le *tooltip* qui est ce qui s'affiche lorsque l'on passe la souris sur l'objet.
- le *popup* qui est ce qui s'affiche lorsque l'on clique sur l'objet.

```python
# Cluster
marker_cluster = MarkerCluster().add_to(carte_lyon)

#ajout de chaque station
for _, row in stations.iterrows():
    popup_text = f"""
    <b>{row['name']}</b><br>
    Vélos disponibles : {row['available_bikes']}<br>
    Capacité totale : {row['bike_stands']}
    """

    folium.Marker(
        location=[row['lat'], row['lng']],
        popup=popup_text,
        tooltip=row['name']
    ).add_to(marker_cluster)

#affichage
carte_lyon
```
<iframe
    src="/notebooks/random/carte_velov_lyon.html" 
    width="700" 
    height="500" 
    title="candlestick with plotly 2" 
    style="border:none">
</iframe>