---
layout: page_Visualisation
title: Partie 2 - Visualisation
description:
img: assets/img/12.jpg
importance: 3
category: ADD
related_publications: False
---

# Introduction 
Une dimension centrale du métier de data scientist consiste à résumer l’information contenue dans les jeux de données afin de distinguer ce qui relève du signal, sur lequel l’analyse pourra se focaliser ; de ce qui correspond au bruit, inévitable dans toute collecte de données. Lors de la phase exploratoire, le travail du data scientist repose ainsi sur un va-et-vient permanent entre des représentations synthétiques des données et leur forme détaillée. Il est donc primordial de savoir condenser l’information d’un jeu de données pour en comprendre la structure globale, laquelle pourra ensuite orienter les analyses futures, qu’il s’agisse de modélisation ou de correction des données (comme la détection d’anomalies ou d’erreurs de collecte).

Nous avons déjà abordé une composante clé de cette démarche : la construction de statistiques descriptives pertinentes et robustes. Toutefois, se limiter à une restitution brute des résultats issus de combinaisons `groupby` et `agg` dans un DataFrame `Pandas` offrirait une vision très partielle des données et restreindrait notre capacité à en tirer des enseignements approfondis. En pratique, notre cerveau comprend et interprète l’information beaucoup plus facilement lorsqu’elle est présentée sous forme de graphiques simples plutôt que dans un tableau.

## La visualisation des données, un outil de communication mais pas que
Les capacités cognitives humaines étant limitées, le data scientist doit s’appuyer sur des outils informatiques et statistiques pour produire des représentations synthétiques de grands volumes de données. La visualisation de données s’inscrit dans cette démarche : elle consiste à représenter visuellement des informations complexes afin d’en faciliter la compréhension, l’exploration et l’analyse. En mettant en évidence tendances, corrélations ou anomalies, elle permet de donner du sens aux données brutes et joue un rôle clé tant dans l’analyse que dans la communication des résultats auprès des experts, des décideurs et du grand public.

La visualisation des données intervient à toutes les étapes d’un projet de data science, et pas uniquement lors de la phase finale de communication des résultats. Elle joue un rôle clé dès l’exploration des données, en permettant de transformer de simples enregistrements en informations porteuses de valeur, seules ou combinées entre elles.

Au quotidien, le data scientist utilise la visualisation comme un outil d’exploration et de réflexion personnelle pour identifier rapidement les axes d’analyse prioritaires, dans une démarche itérative et parfois volontairement approximative, afin de ne pas passer à côté de sources potentielles de valeur.

En revanche, la communication des résultats à des publics non experts (disposant d’un accès limité aux données, d’un temps d’attention restreint ou de compétences quantitatives réduites) exige un travail bien plus abouti. Elle nécessite des visualisations soignées, adaptées aux attentes et aux usages des utilisateurs, ce qui explique l’essor des plateformes et sites web dédiés à la data visualisation. 

# Les packages de visualisation en `Python`

L’écosystème Python dédié à la visualisation de données est à la fois très riche et particulièrement fragmenté. Il est à lui seul un sujet suffisamment vaste pour faire l’objet d'un cours. Python met en effet à disposition de nombreuses bibliothèques permettant de produire rapidement, et avec une relative simplicité, des visualisations de données.

Ces librairies de visualisation se répartissent principalement en deux grandes familles :

 - Les librairies **figées**, principalement destinées à une intégration dans des supports statiques, tels que des documents PDF ou des rapports textuels. Nous nous concentrerons essentiellement sur `Matplotlib` et `Seaborn`. Cependant nous vous conseillons de suivre l'évolution de [Plotnine](https://plotnine.org/), l’adaptation de [ggplot2](https://juba.github.io/tidyverse/08-ggplot2.html) à l’écosystème `Python`.
 - Les librairies **réactives**, adaptées aux visualisations web et permettent aux utilisateurs d’interagir directement avec les représentations graphiques. Elles s’appuient généralement sur JavaScript, pilier de l’écosystème du développement web, tout en proposant une interface d’utilisation via Python. Dans cette catégorie, nous aborderons principalement Plotly et Folium.