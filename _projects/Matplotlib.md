---
layout: page_Visualisation
title: Visualisations figées, Matplotlib - Seaborn
description:
img: assets/img/12.jpg
importance: 3
category: ADD
related_publications: False
---

# Matplotlib
## Introduction
`Matplotlib` est un package open source polyvalent de visualisation pour Python développée par John D. Hunter en 2003 pour proposer une alternative à la création de graphique `Matlab`. Cette origine assez ancienne se reflète dans la logique de construction de Matplotlib, qui peut sembler peu intuitive pour qui est habitué à l’écosystème moderne de la data science. Heureusement, de nombreuses bibliothèques s’appuient sur Matplotlib tout en proposant une syntaxe plus proche des usages et des attentes des data scientists.

`Matplotlib` s’organise autour de deux niveaux d'abstraction principaux : la **figure** et les **axes**. La figure agit comme une « toile » générale pouvant contenir un ou plusieurs axes, chacun servant à tracer des graphiques. Selon ce que l’on souhaite modifier, il est possible d’ajuster les paramètres de la figure ou ceux des axes. Cela rend `matplotlib` très flexible, mais aussi un peu déroutant, car il n’est pas toujours évident de savoir quel niveau manipuler pour obtenir le résultat souhaité. La Figure ci-dessous illustre tous les éléments d'une figure.

<figure style="text-align: center;">
  <img src="/assets/img/anatomy.webp" alt="pandas dataframe" width="80%">
  <figcaption><em> Anatomie d’une figure `matplotlib`, source : [matplolib.org](https://matplotlib.org/stable/users/explain/quick_start.html) </em></figcaption>
</figure>

## Matplotlib en pratique
En pratique, il existe deux manière d'utiliser `matplotlib` : 

- une approche explicite, orientée objet en utilisant `pylab`. On crée des objets `Figure` et `Axes` et on les met à jour. Son utilisation est très semblable à l'API Matlab. 
- une approche implicite, basée sur l’interface `pyplot`, qui utilise une succession de fonctions pour mettre à jour les objets créés implicitement. 

Voici un exemple d'utilisation de matplotlib, implicite. Nous allons travailler sur les données de la variation de température terrestre. Il s'agit d'une reproduction simplifiée de [ce tutoriel](https://python-graph-gallery.com/web-lollipop-with-colormap-and-arrow/)

```python
import pandas as pd
import matplotlib.colors as mcolors
import matplotlib.pyplot as plt

url = "https://raw.githubusercontent.com/holtzy/The-Python-Graph-Gallery/master/static/data/temperature-variation.csv"
df = pd.read_csv(url)
df.head()
```

Nous allons créer ce que l'on appele une 'lollipop chart'. Bien que la fonction `stem()` de `Matplotlib` soit conçue pour créer des graphiques de type lollipop, nous allons utiliser `plot()` et `scatter()` à la place pour ajouter manuellement les lignes et les points. Cette approche facilite la personnalisation des couleurs de chaque lollipop à l’étape suivante.

```python
fig, ax = plt.subplots(figsize=(15, 8), dpi=300)

for i, row in df.iterrows():
    year = row["Year"]
    change = row["Change"]
    ax.scatter(x=year, y=change)
    ax.plot([year, year], [0, change])

plt.show()
```

<figure style="text-align: center; cursor: pointer;" id="image-container">
    <img id="toggle-image" src="/assets/img/chap_visu/world_temp1.png" alt="worldtemp" width="70%">
</figure>


Nous allons maintenant créer un palette de couleur liée à la valeur de température à l'aide de `LinearSegmentedColormap`. 

```python
colors = ["blue", "#ffe6cc", "red"]
cmap = mcolors.LinearSegmentedColormap.from_list("BluetoRed", colors)
# On normalise pour que la couleur ffe6cc soit la valeur à 0° de différence
norm = mcolors.TwoSlopeNorm(vmin=df["Change"].min(), vcenter=0, vmax=df["Change"].max())

fig, ax = plt.subplots(figsize=(15, 8), dpi=300)

for i, row in df.iterrows():
    year = row["Year"]
    change = row["Change"]
    color = cmap(norm(change))  # normaliser avant de passer à la colormap
    ax.scatter(x=year, y=change, color=color, s=100)  # ajout d'une taille pour la visibilité
    ax.plot([year, year], [0, change], color=color, alpha=0.8)

plt.show()
```
<figure style="text-align: center; cursor: pointer;" id="image-container">
    <img id="toggle-image" src="/assets/img/chap_visu/world_temp2.png" alt="worldtemp" width="70%">
</figure>

Nous allons maintenant personnaliser les axes en affichant uniquement les années divisible par 20 (axe X). Nous allons aussi tracer une ligne pour certaine valeurs de température (axe Y) tout en ajoutant la valeurs correspondante.

```python
fig, ax = plt.subplots(figsize=(15, 8), dpi=300)
ax.set_axis_off()

for i, row in df.iterrows():
    year = row["Year"]
    change = row["Change"]
    color = cmap(norm(change))
    ax.scatter(x=year, y=change, color=color)
    ax.plot([year, year], [0, change], color=color, alpha=0.8)

    if year % 20 == 0:
        ax.text(x=year, y=-0.6, s=f"{year:.0f}",  size=15, ha="left")
ax.text(x=1881, y=-0.6, s=f"{1880}",  size=15, ha="left")

h_lines = [-0.4, 0, 0.4, 0.8]
ax.hlines(
    y=h_lines,
    xmin=1881,
    xmax=2023,
    colors=[norm(cmap(val)) for val in h_lines],
    linewidth=1.2,
    zorder=-1,
    alpha=0.5,
)
for value in h_lines:
    ax.text(
        x=1877, y=value, s=f"{value}", color=cmap(value), size=9, va="center"
    )

plt.show()
```
<figure style="text-align: center; cursor: pointer;" id="image-container">
    <img id="toggle-image" src="/assets/img/chap_visu/world_temp3.png" alt="worldtemp" width="70%">
    <figcaption>Cliquez sur l'image pour la masquer/afficher</figcaption>
</figure>

Enfin nous rajoutons un titre, un sous-titre et la sources de nos données.

```python
fig, ax = plt.subplots(figsize=(15, 8), dpi=300)
ax.set_axis_off()

for i, row in df.iterrows():
    year = row["Year"]
    change = row["Change"]
    color = cmap(norm(change))
    ax.scatter(x=year, y=change, color=color)
    ax.plot([year, year], [0, change], color=color, alpha=0.8)

    if year % 20 == 0:
        ax.text(x=year, y=-0.6, s=f"{year:.0f}",  size=15, ha="left")
ax.text(x=1881, y=-0.6, s=f"{1880}",  size=15, ha="left")

h_lines = [-0.4, 0, 0.4, 0.8]
ax.hlines(
    y=h_lines,
    xmin=1881,
    xmax=2023,
    colors=[cmap(norm(val)) for val in h_lines],
    linewidth=1.2,
    zorder=-1,
    alpha=0.5,
)
for value in h_lines:
    ax.text(
        x=1877, y=value, s=f"{value}", color=cmap(value), size=9, va="center"
    )

ax.text(
    x=1881,
    y=1.1,
    s="Global Land-Ocean Temperature Index",
    fontsize=35,
    ha="left",
    va="top"
)

ax.text(
    x=1881,
    y=0.94,
    s="Change in global surface temperature compared to the long-term average from 1880 to 2020",
    fontsize=12,
    ha="left",
    va="top"
)

ax.text(
    x=1881,
    y=-0.7,
    s="Source : NASA",
    fontsize=12,
    ha="left",
    va="top"
)

plt.show()
```
<figure style="text-align: center; cursor: pointer;" id="image-container">
    <img id="toggle-image" src="/assets/img/chap_visu/world_temp4.png" alt="worldtemp" width="70%">
    <figcaption>Cliquez sur l'image pour la masquer/afficher</figcaption>
</figure>



Vous trouverez dans ce notebook tiré du cours d'ADD de 2023-2024 des exemples plus simples détaillant le fonctionnement de matplotlib à la fois en implicite et en explicite.
<div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 20px;">
<a href="https://drive.google.com/file/d/1rAqr-GWCB0rJYDdFoFH0i48OjLylLd4C/view?usp=sharing" style="text-decoration: none;">
    <div style="border: 1px solid #ddd; border-radius: 12px; padding: 20px; text-align: center; transition: transform 0.2s;">
        <h3>Matplotlib & Dataviz</h3>
    </div>
</a>
</div>
<br>

# Seaborn

[Seaborn](https://seaborn.pydata.org/) constitue une interface de plus haut niveau construite au-dessus de `Matplotlib`. Ce package propose un ensemble de fonctions permettant de générer directement des figures ou des axes Matplotlib à partir d’appels simples, enrichis de nombreux paramètres. Lorsque des ajustements plus fins sont nécessaires, il reste possible de s’appuyer sur les mécanismes de personnalisation de Matplotlib, en utilisant aussi bien l’approche implicite que l’approche explicite évoquées précédemment.

À l’instar de `Matplotlib`, une même visualisation peut être produite de différentes manières avec `Seaborn`. La bibliothèque reprend en effet la distinction figure/axes, et il est fréquent de devoir intervenir à l’un ou l’autre de ces niveaux. L’un des principaux atouts de Seaborn réside toutefois dans la standardisation de certains points d’entrée, comme seaborn.relplot ou seaborn.catplot, ainsi que dans une logique d’utilisation centrée sur les DataFrames, contrairement à Matplotlib qui repose principalement sur des tableaux NumPy. Il convient néanmoins de garder à l’esprit que Seaborn hérite également de certaines limites de Matplotlib, en particulier la complexité de la personnalisation avancée, qui peut rapidement devenir délicate lorsque les options recherchées ne sont pas directement accessibles via les arguments des fonctions.

Voici un exemple d'une visualisation qui serait longue et fastidieuse en `Matplotlib` qui est très simple à faire en utilisant `Seaborn` sur le dataset *Iris* :

```python
# library & dataset
import matplotlib.pyplot as plt
import seaborn as sns
df = sns.load_dataset('iris')
 
sns.pairplot(df, kind="scatter", hue="species", markers=["o", "s", "D"], palette="Set2")
plt.show()
```

<figure style="text-align: center; cursor: pointer;" id="image-container">
    <img id="toggle-image" src="/assets/img/chap_visu/iris.png" alt="iris visual" width="70%">
    <figcaption>Cliquez sur l'image pour la masquer/afficher</figcaption>
</figure>

<script>
  const image = document.getElementById('toggle-image');
  const container = document.getElementById('image-container');

  container.addEventListener('click', () => {
    if (image.style.display === 'none') {
      image.style.display = 'block';
    } else {
      image.style.display = 'none';
    }
  });
</script>

# Pour aller plus loin

Ces tutoriels constituent le minimum pour faire une visualisation de données. Pour être plus à l’aise avec ces concepts, la pratique répétée est indispensable. Voici quelques sources qui vous serons toujours utiles : 

Docs et exemple :
* [Matplotlib](http://www.matplotlib.org).
* [Seaborn](https://seaborn.pydata.org/index.html).
* [The Python Graph Gallery](https://python-graph-gallery.com/) - **un must-have**, plein d'exemple très reussis et parfois très techniques.

Tuto :
* [Tutoriel sur Matplotlib](http://www.loria.fr/~rougier/teaching/matplotlib).
* [Autre tutoriel Matplotlib](http://scipy-lectures.org/intro/matplotlib/index.html).

Autre package très interessant : 

* [Plotnine](https://plotnine.org/) - Cette librairie vise à importer la logique de ggplot en Python. Remplacera peut être matplotlib/seaborns d'ici quelques années, à surveiller.


