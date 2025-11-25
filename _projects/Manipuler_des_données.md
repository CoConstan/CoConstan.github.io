---
layout: page_Manipulation
title: Manipuler des données avec Pandas
description:
img: assets/img/12.jpg
importance: 4
category: ADD
related_publications: False
---

# 1 **Introdution**

Le chapitre d’introduction à `Pandas` a permis de présenter le principe des données organisées sous la forme d’un `DataFrame`, ainsi que la praticité de l’écosystème `Pandas` pour réaliser des opérations simples sur un jeu de données.

Dans la pratique, il est rare de travailler sur une source de données isolée. Un jeu de données prend toute sa valeur lorsqu’il est mis en relation avec d’autres sources.
Pour les chercheurs, cette mise en perspective permet de contextualiser l’information contenue dans une source en la comparant ou en la combinant avec d’autres.
Dans le secteur privé, les data scientists cherchent souvent à associer des informations relatives à une même entité (par exemple, un client) issues de plusieurs bases, ou à comparer les individus entre eux.

L’un des grands atouts des outils modernes de data science — et de `Pandas` en particulier — réside dans la facilité avec laquelle ils permettent de restructurer et de combiner des sources de données pour mener une analyse intégrée.
Ce chapitre vient consolider les notions introduites précédemment en affinant les traitements appliqués aux données. Il se concentrera principalement sur deux types d’opérations :

- les statistiques descriptives par groupe ;

- l’association de données à partir de caractéristiques communes.

Réaliser ce travail de manière simple, fiable et efficace est une compétence essentielle pour tout data scientist, tant cette tâche est fréquente dans la pratique.
Heureusement, Pandas offre des outils puissants et intuitifs pour accomplir ce type de traitement sur des données structurées.

Ce travail constitue une étape clé : il nous permettra de mieux comprendre un phénomène réel grâce à des statistiques descriptives détaillées, avant de passer à la statistique inférentielle, qui vise à formaliser et généraliser les liens de corrélation ou de causalité entre des caractéristiques observées et un phénomène étudié.

## 1.1 Environment

Le chapitre précédent utilisait quasi exclusivement la librairie `Pandas`. Nous allons dans ce chapitre utiliser d’autres packages en complément de celui-ci.

```python
!pip install xlrd --quiet
!pip install pynsee --quiet
```

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import pynsee
import pynsee.download
```

Pour obtenir des résultats reproductibles, on fixe la racine du générateur pseudo-aléatoire.

```python
np.random.seed(42)
```

## 1.2 Données

Dans ce chapitre, nous allons travailler sur des données issues de l’Insee et de l'ADEME :

- Les émissions de gaz à effet de serre estimées au niveau communal par l’ADEME. Le jeu de données est disponible sur [data.gouv](https://www.data.gouv.fr/fr/datasets/inventaire-de-gaz-a-effet-de-serre-territorialise/#_) et requêtable directement dans `Python`.

- Le [code officiel géographique](https://www.insee.fr/fr/statistiques/fichier/6800675/v_commune_2023.csv) de l'Insee. Il permet d'identifier les communes françaises à partir d'un code univoque (code INSEE).

- Les données [Filosofi](https://www.insee.fr/fr/metadonnees/source/serie/s1172) constituant une source d’information sur les revenus des Français à une échelle spatiale fine, élaborée par l’Insee à partir des déclarations fiscales et des données relatives aux prestations sociales. Dans notre cas, nous utiliserons les niveaux de revenu et les données de population au niveau communal, afin de les mettre en relation avec nos données d’émissions.

Pour faciliter l’import de données Insee, il est recommandé d’utiliser le package `pynsee` qui simplifie l’accès aux principaux jeux de données de l’Insee disponibles sur le site web insee.fr ou via des API. La liste des jeux de données disponibles est consultable [ici](https://inseefrlab.github.io/DoReMIFaSol/articles/donnees_dispo.html).

# 2 **Recupération des données**

## 2.1 Données ADEME

```python
url = "https://koumoul.com/s/data-fair/api/v1/datasets/igt-pouvoir-de-rechauffement-global/convert"
emissions = pd.read_csv(url)
emissions.head(2)
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>INSEE commune</th>
<th>Commune</th>
<th>Agriculture</th>
<th>Autres transports</th>
<th>Autres transports international</th>
<th>CO2 biomasse hors-total</th>
<th>Déchets</th>
<th>Energie</th>
<th>Industrie hors-énergie</th>
<th>Résidentiel</th>
<th>Routier</th>
<th>Tertiaire</th>
</tr>
</thead>
<tbody>
<tr>
<th>0</th>
<td>01001</td>
<td>L'ABERGEMENT-CLEMENCIAT</td>
<td>3711.425991</td>
<td>NaN</td>
<td>NaN</td>
<td>432.751835</td>
<td>101.430476</td>
<td>2.354558</td>
<td>6.911213</td>
<td>309.358195</td>
<td>793.156501</td>
<td>367.036172</td>
</tr>
<tr>
<th>1</th>
<td>01002</td>
<td>L'ABERGEMENT-DE-VAREY</td>
<td>475.330205</td>
<td>NaN</td>
<td>NaN</td>
<td>140.741660</td>
<td>140.675439</td>
<td>2.354558</td>
<td>6.911213</td>
<td>104.866444</td>
<td>348.997893</td>
<td>112.934207</td>
</tr>
</tbody>
</table>
</div>
</div>
<br>

Nous allons maintenant ajouter une colonne pour le code département extrait du code INSEE de la commune et identifier les colonnes correspondant aux secteurs d’activité.

```python
secteurs = emissions.select_dtypes(include='number').columns
emissions["dep"] = emissions["INSEE commune"].str[:2]
```

## 2.2 Données Filosofi

```python
from pynsee.download import download_file
filosofi = download_file("FILOSOFI_COM_2016")
filosofi.head(2)
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>CODGEO</th>
<th>LIBGEO</th>
<th>NBMENFISC16</th>
<th>NBPERSMENFISC16</th>
<th>MED16</th>
<th>PIMP16</th>
<th>TP6016</th>
<th>TP60AGE116</th>
<th>TP60AGE216</th>
<th>TP60AGE316</th>
<th>...</th>
<th>PPEN16</th>
<th>PPAT16</th>
<th>PPSOC16</th>
<th>PPFAM16</th>
<th>PPMINI16</th>
<th>PPLOGT16</th>
<th>PIMPOT16</th>
<th>D116</th>
<th>D916</th>
<th>RD16</th>
</tr>
</thead>
<tbody>
<tr>
<th>0</th>
<td>01001</td>
<td>L'Abergement-Clémenciat</td>
<td>313</td>
<td>795.5</td>
<td>22679</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>...</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
</tr>
<tr>
<th>1</th>
<td>01002</td>
<td>L'Abergement-de-Varey</td>
<td>101</td>
<td>248</td>
<td>24382.083333333336</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>...</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
</tr>
</tbody>
</table>
<p>2 rows × 29 columns</p>
</div>
</div>

Pandas a géré automatiquement les types de variables. Il le fait relativement bien, mais une vérification est toujours utile pour les variables qui ont un statut spécifique. Pour les variables qui ne sont pas en type float alors qu’elles devraient l’être, on modifie leur type.

```python
filosofi = (filosofi.astype({c: "float" for c in filosofi.columns[2:]}))
```

Un simple examen des données permet de se faire une idée assez précise de leur structure. On observe que certaines variables de Filosofi présentent de nombreuses valeurs manquantes — en raison du secret statistique —, tandis que d’autres sont plus complètes. Il est donc essentiel de choisir avec soin les variables à exploiter pour garantir la qualité de l’analyse.

Notre objectif, à terme, est de relier les informations contenues dans ces deux jeux de données.Sans cette mise en correspondance, l’analyse risquerait de rester incomplète : nous pourrions vouloir approfondir la compréhension des émissions de gaz carbonique, mais serions limités dans nos possibilités d’interprétation sans l’apport d’informations complémentaires issues de Filosofi.

# 3 **Statistiques descriptives par groupe**

Dans le chapitre précédent, nous avons vu comment obtenir facilement des statistiques agrégées à l’aide de Pandas.
Cependant, il est fréquent de disposer de données comportant des strates d’analyse intermédiaires pertinentes — par exemple, des variables géographiques, des groupes socio-démographiques liés à certaines caractéristiques observées, ou encore des indicateurs temporels.

Nous allons rapidement calculer les statistique au niveau national en utilisant ce que nous avons appris précédemment.

```python
emissions_totales = pd.DataFrame(df.sum(numeric_only = True), columns = ["emissions"]).reset_index(names = "secteur")
emissions_totales['emissions (%)'] = 100*emissions_totales['emissions']/emissions_totales['emissions'].sum()
emissions_totales.sort_values("emissions", ascending = False).round()
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>secteur</th>
<th>emissions</th>
<th>emissions (%)</th>
</tr>
</thead>
<tbody>
<tr>
<th>8</th>
<td>Routier</td>
<td>126493164.0</td>
<td>24.0</td>
</tr>
<tr>
<th>0</th>
<td>Agriculture</td>
<td>87909694.0</td>
<td>17.0</td>
</tr>
<tr>
<th>6</th>
<td>Industrie hors-énergie</td>
<td>83573677.0</td>
<td>16.0</td>
</tr>
<tr>
<th>7</th>
<td>Résidentiel</td>
<td>63841398.0</td>
<td>12.0</td>
</tr>
<tr>
<th>3</th>
<td>CO2 biomasse hors-total</td>
<td>63519311.0</td>
<td>12.0</td>
</tr>
<tr>
<th>9</th>
<td>Tertiaire</td>
<td>39562729.0</td>
<td>7.0</td>
</tr>
<tr>
<th>5</th>
<td>Energie</td>
<td>22852034.0</td>
<td>4.0</td>
</tr>
<tr>
<th>2</th>
<td>Autres transports international</td>
<td>22238569.0</td>
<td>4.0</td>
</tr>
<tr>
<th>4</th>
<td>Déchets</td>
<td>14703580.0</td>
<td>3.0</td>
</tr>
<tr>
<th>1</th>
<td>Autres transports</td>
<td>6535446.0</td>
<td>1.0</td>
</tr>
</tbody>
</table>
</div>
</div>
<br>

Nous pouvons voir que les secteurs les plus émetteurs, à savoir le transport, l’agriculture et l’industrie hors énergie. Le fait que l’énergie soit relativement peu émettrice s’explique bien du fait du mix énergétique français où le nucléaire représente une majorité de la production électrique.

Mais qu’en est-il du profil d’émission des différents départements ?
Pour répondre à cette question, il sera nécessaire d’agréger les données au niveau départemental.
Cette approche nous fournira une perspective complémentaire, différente à la fois de celle du niveau communal et du niveau national.

En `SQL`, il est très simple de découper les données pour effectuer des opérations sur des blocs cohérents, puis de rassembler les résultats dans la dimension appropriée.
Cette logique, connue sous le nom de `split–apply–combine`, est également au cœur des langages de manipulation de données modernes — et `Pandas` [n’y fait pas exception](https://pandas.pydata.org/pandas-docs/stable/user_guide/groupby.html). Pour faire cela, en `Pandas`, on utilise la méthode `groupby()`.

## 3.1 Exemple 1: dénombrement par groupe

Pour illustrer le fonctionnement de `groupby()`, nous allons commencer par un exemple simple : compter le nombre de communes par département.

```python
import requests
from io import StringIO
import pandas as pd
cog_2023 = pd.read_csv(StringIO(response.text))
communes = cog_2023.loc[cog_2023['TYPECOM']=="COM"] # on sélectionne uniquement les communes (pour eviter les arrondissements de Paris, Lyon, Marseille)
communes.loc[:, ['COM', 'DEP', 'REG']].nunique()
```

<div class="jp-RenderedText jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/plain" tabindex="0">
<pre>COM    34945
DEP      101
REG       18
dtype: int64</pre>
</div>

On obtient le nombre de communes, départements et régions en France. On peut maintenant compter le nombre de communes par département.

```python
communes.groupby('DEP').agg({'COM': 'nunique'})
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>COM</th>
</tr>
<tr>
<th>DEP</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>01</th>
<td>392</td>
</tr>
<tr>
<th>02</th>
<td>798</td>
</tr>
<tr>
<th>03</th>
<td>317</td>
</tr>
<tr>
<th>04</th>
<td>198</td>
</tr>
<tr>
<th>05</th>
<td>162</td>
</tr>
<tr>
<th>...</th>
<td>...</td>
</tr>
<tr>
<th>971</th>
<td>32</td>
</tr>
<tr>
<th>972</th>
<td>34</td>
</tr>
<tr>
<th>973</th>
<td>22</td>
</tr>
<tr>
<th>974</th>
<td>24</td>
</tr>
<tr>
<th>976</th>
<td>17</td>
</tr>
</tbody>
</table>
<p>101 rows × 1 columns</p>
</div>
</div>

On obtient une serie indexée. Ce n'est pas pratique, on prefère un DataFrame. On utilise donc la méthode `reset_index()`. Pour finir, on trie les départements par nombre de communes décroissant avec la méthode `sort_values()`.

```python
communes.groupby('DEP').agg({'COM': 'nunique'}).reset_index().sort_values('COM', ascending = False)
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>DEP</th>
<th>COM</th>
</tr>
</thead>
<tbody>
<tr>
<th>62</th>
<td>62</td>
<td>890</td>
</tr>
<tr>
<th>1</th>
<td>02</td>
<td>798</td>
</tr>
<tr>
<th>80</th>
<td>80</td>
<td>772</td>
</tr>
<tr>
<th>57</th>
<td>57</td>
<td>725</td>
</tr>
<tr>
<th>76</th>
<td>76</td>
<td>708</td>
</tr>
<tr>
<th>...</th>
<td>...</td>
<td>...</td>
</tr>
<tr>
<th>96</th>
<td>971</td>
<td>32</td>
</tr>
<tr>
<th>99</th>
<td>974</td>
<td>24</td>
</tr>
<tr>
<th>98</th>
<td>973</td>
<td>22</td>
</tr>
<tr>
<th>100</th>
<td>976</td>
<td>17</td>
</tr>
<tr>
<th>75</th>
<td>75</td>
<td>1</td>
</tr>
</tbody>
</table>
<p>101 rows × 2 columns</p>
</div>
</div>

## 3.2 Exemple 2: agrégation par groupe

Pour illustrer l'utilisation d'agréggats, nous allons utilisé le jeu de données `filosofi` pour compter la population totale par département.

Il y a deux manières de faire cela : une implicite et une explicite.

```python
# On commence par créer la variable "dep"
filosofi["dep"] = filosofi["CODGEO"].str[:2]
# Implicite => il faut faire attention à l'ordre des opérations (renvoie une série)
filosofi.groupby('dep')['NBPERSMENFISC16'].sum()
```

<div class="jp-RenderedText jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/plain" tabindex="0">
<pre>dep
01     613088.0
02     514249.0
03     329435.0
04     156537.5
05     133992.5
        ...    
92    1583682.0
93    1586664.5
94    1345977.0
95    1226059.0
97    1191947.0
Name: NBPERSMENFISC16, Length: 97, dtype: float64</pre>
</div>

```python
# Explicite => plus verbeux mais plus clair (renvoie un DataFrame)
filosofi.groupby('dep').agg({'NBPERSMENFISC16': 'sum'})
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>NBPERSMENFISC16</th>
</tr>
<tr>
<th>dep</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>01</th>
<td>613088.0</td>
</tr>
<tr>
<th>02</th>
<td>514249.0</td>
</tr>
<tr>
<th>03</th>
<td>329435.0</td>
</tr>
<tr>
<th>04</th>
<td>156537.5</td>
</tr>
<tr>
<th>05</th>
<td>133992.5</td>
</tr>
<tr>
<th>...</th>
<td>...</td>
</tr>
<tr>
<th>92</th>
<td>1583682.0</td>
</tr>
<tr>
<th>93</th>
<td>1586664.5</td>
</tr>
<tr>
<th>94</th>
<td>1345977.0</td>
</tr>
<tr>
<th>95</th>
<td>1226059.0</td>
</tr>
<tr>
<th>97</th>
<td>1191947.0</td>
</tr>
</tbody>
</table>
<p>97 rows × 1 columns</p>
</div>
</div>

La seconde approche s’avère plus pratique, car elle renvoie directement un DataFrame Pandas, et non une série indexée.
À partir de ce DataFrame, quelques manipulations simples suffisent pour obtenir un tableau exploitable décrivant la démographie départementale.

Cependant, ce tableau reste encore assez brut, puisqu’il ne contient pour l’instant que les numéros de département.
Pour y ajouter le nom des départements, il sera nécessaire d’utiliser une seconde base de données et de croiser les informations communes entre les deux sources (en l’occurrence, le code du département). C’est l’objet de la section suivante.

# 3.3 Exercice d'application

Ce exercice utilise le jeu de données `emissions` pour calculer les émissions totales de gaz à effet de serre par département.

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 1
  </summary>
  <div style="padding: 12px;">
    1. Calculer les émissions totales du secteur “Résidentiel” par département, puis rapporter ces valeurs à celle du département le plus émetteur dans ce domaine. Que pouvez-vous en conclure ?<br>
    2. Calculer, pour chaque département, les émissions totales de chaque secteur en pourcentage des émissions totales du département. Que pouvez-vous en conclure ?<br>
  </div>
</details>

# 4 **Joindre des données**

Nous allons ici nous focaliser sur le cas le plus favorable qui est la situation où une information permet d’apparier de manière exacte deux bases de données. Associer des données issues de sources différentes est une tâche courante en data science. Par exemple, pour une entreprise, elle peut posseder une base de données clients et une base de données de transactions, et souhaiter les combiner pour analyser le comportement d'achat de ses clients.

Cette structuration en étoile, est historiquement liée aux bases de données relationnelles, aujourd'hui il existe des alternatives plus flexibles sans structure _a priori_ où l'information est empilée dans un datalake. Cependant, la structuration en étoile reste très utilisée dans la pratique, notamment de compartimentation de l'information. On ne donne accès qu'aux données nécessaires à une tâche précise, ce qui permet de limiter les risques de fuites de données sensibles.

On parle souvent de jointure de données, un héritage du terme JOIN en SQL. En `Pandas`, et la manière de définir les jointures (left join, right join…) est directement inspirée de SQL. Cette opération est réalisée à l’aide de la méthode `merge()`.

## 4.1 Mise en oeuvre

En Pandas, la méthode la plus pratique pour associer plusieurs jeux de données à partir de caractéristiques communes est la fonction merge().
Ses principaux arguments permettent de contrôler précisément le type et le comportement de la jointure, offrant ainsi une grande flexibilité dans la manière de combiner les sources d’information.
Nous allons les explorer de façon visuelle afin d’en comprendre le fonctionnement.

Dans notre cas d’étude — la construction de statistiques sur les émissions de gaz carbonique —, la base de gauche correspondra au DataFrame `emission`, et la base de droite au DataFrame `filosofi`.

On utilise le term clé(s) pour spécifier la ou les colonnes communes aux deux DataFrames utilisées pour la jointure. Il n'est pas nécessaire que les noms des colonnes soient identiques dans les deux DataFrames, on peut utiliser les arguments `left_on` et `right_on` pour spécifier les noms des colonnes dans chaque DataFrame. Cependant, elles doivent contenir des valeurs identiques pour que la jointure fonctionne correctement (sinon on obtient l'ensemble vide).

De manière général, les jointures sont effectuer sur des colonnes contenant des identifiants uniques (comme un code INSEE, un numéro de sécurité sociale, un identifiant client…).

Il existe quatre types de jointures principales :

- **Inner join** : ne conserve que les lignes ayant des valeurs correspondantes dans les deux DataFrames. C'est le type de jointure par défaut.

- **Left join** : conserve toutes les lignes du DataFrame de gauche, et ajoute les colonnes du DataFrame de droite lorsque des correspondances sont trouvées. Les lignes sans correspondance dans le DataFrame de droite auront des valeurs NaN pour les colonnes ajoutées.

- **Right join** : conserve toutes les lignes du DataFrame de droite, et ajoute les colonnes du DataFrame de gauche lorsque des correspondances sont trouvées. Les lignes sans correspondance dans le DataFrame de gauche auront des valeurs NaN pour les colonnes ajoutées.

- **Full (Outer) join** : conserve toutes les lignes des deux DataFrames, en ajoutant des valeurs NaN pour les colonnes où il n'y a pas de correspondance.

Pour illustrer ces différents types de jointures, nous allons utiliser les dataframes d'exemple suivant :

```python
left = pd.DataFrame({
    'id': ['a', 'b', 'c'],
    'x': ['x1', 'x2', 'x3'],
    'y': ['y1', 'y2', 'y3'],
    'z': ['z1', 'z2', 'z3']
}).set_index('id')
left
```

<div class="jp-OutputPrompt jp-OutputArea-prompt">Out[24]:</div>
<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>x</th>
<th>y</th>
<th>z</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>x1</td>
<td>y1</td>
<td>z1</td>
</tr>
<tr>
<th>b</th>
<td>x2</td>
<td>y2</td>
<td>z2</td>
</tr>
<tr>
<th>c</th>
<td>x3</td>
<td>y3</td>
<td>z3</td>
</tr>
</tbody>
</table>
</div>
</div>

<br>

```python
right = pd.DataFrame({
    'id': ['a', 'd', 'c'],
    'm': ['m1', 'm2', 'm3'],
    'n': ['n1', 'n2', 'n3']
}).set_index('id')
right
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>m</th>
<th>n</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>m1</td>
<td>n1</td>
</tr>
<tr>
<th>d</th>
<td>m2</td>
<td>n2</td>
</tr>
<tr>
<th>c</th>
<td>m3</td>
<td>n3</td>
</tr>
</tbody>
</table>
</div>
</div>
<br>

### 4.1.1 Inner join

Commenceons par une jointure interne (inner join). Il s’agit du jeu de données où les clés sont retrouvées à l’intersection des deux tables.

```python
inner_merged = left.merge(
  right,
  left_on = ["id"],
  right_on = ["id"],
  how = "inner"
)
inner_merged
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>x</th>
<th>y</th>
<th>z</th>
<th>m</th>
<th>n</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
<th></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>x1</td>
<td>y1</td>
<td>z1</td>
<td>m1</td>
<td>n1</td>
</tr>
<tr>
<th>c</th>
<td>x3</td>
<td>y3</td>
<td>z3</td>
<td>m3</td>
<td>n3</td>
</tr>
</tbody>
</table>
</div>
</div>
<br>

### 4.1.2 Left join

Passons maintenant à une jointure à gauche (left join). On conserve toutes les lignes du DataFrame de gauche (`emissions`), et on ajoute les colonnes du DataFrame de droite (`filosofi`) lorsque des correspondances sont trouvées.

```python
left_merged = left.merge(
  right,
  left_on = ["id"],
  right_on = ["id"],
  how = "left"
)
left_merged
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>x</th>
<th>y</th>
<th>z</th>
<th>m</th>
<th>n</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
<th></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>x1</td>
<td>y1</td>
<td>z1</td>
<td>m1</td>
<td>n1</td>
</tr>
<tr>
<th>b</th>
<td>x2</td>
<td>y2</td>
<td>z2</td>
<td>NaN</td>
<td>NaN</td>
</tr>
<tr>
<th>c</th>
<td>x3</td>
<td>y3</td>
<td>z3</td>
<td>m3</td>
<td>n3</td>
</tr>
</tbody>
</table>
</div>
</div>

<br>

### 4.1.3 Right join

```python
right_merged = left.merge(
  right,
  left_on = ["id"],
  right_on = ["id"],
  how = "right"
)
right_merged
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>x</th>
<th>y</th>
<th>z</th>
<th>m</th>
<th>n</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
<th></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>x1</td>
<td>y1</td>
<td>z1</td>
<td>m1</td>
<td>n1</td>
</tr>
<tr>
<th>d</th>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>m2</td>
<td>n2</td>
</tr>
<tr>
<th>c</th>
<td>x3</td>
<td>y3</td>
<td>z3</td>
<td>m3</td>
<td>n3</td>
</tr>
</tbody>
</table>
</div>
</div>

<br>

### 4.1.4 Full join

```python
full_merged = left.merge(
  right,
  left_on = ["id"],
  right_on = ["id"],
  how = "outer"
)
full_merged
```

<div class="jp-RenderedHTMLCommon jp-RenderedHTML jp-OutputArea-output jp-OutputArea-executeResult" data-mime-type="text/html" tabindex="0">
<div>
<style scoped="">
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }

</style>
<table border="1" class="dataframe">
<thead>
<tr style="text-align: right;">
<th></th>
<th>x</th>
<th>y</th>
<th>z</th>
<th>m</th>
<th>n</th>
</tr>
<tr>
<th>id</th>
<th></th>
<th></th>
<th></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<th>a</th>
<td>x1</td>
<td>y1</td>
<td>z1</td>
<td>m1</td>
<td>n1</td>
</tr>
<tr>
<th>b</th>
<td>x2</td>
<td>y2</td>
<td>z2</td>
<td>NaN</td>
<td>NaN</td>
</tr>
<tr>
<th>c</th>
<td>x3</td>
<td>y3</td>
<td>z3</td>
<td>m3</td>
<td>n3</td>
</tr>
<tr>
<th>d</th>
<td>NaN</td>
<td>NaN</td>
<td>NaN</td>
<td>m2</td>
<td>n2</td>
</tr>
</tbody>
</table>
</div>
</div>
<br>

## 4.2 Exercice d'application

Cet exercice va revenir un peu en arrière afin de saisir pourquoi nous préferons prendre le code INSEE de commune au lieu du nom de la commune pour faire des jointures.

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 2
  </summary>
  <div style="padding: 12px;">
    1. Vérifier les dimensions des DataFrames.<br>
    2. Identifier dans <code>filosofi</code> les noms de communes qui correspondent à plusieurs codes communes et sélectionner leurs codes. En d’autres termes, identifier les <code>LIBGEO</code> tels qu’il existe des doublons de <code>CODGEO</code> et les stocker dans un vecteur <code>x</code> (conseil: faire attention à l’index de <code>x</code>).<br>
    3. Regarder dans <code>filosofi</code> les observations où le libellé comporte plus de deux codes communes différents.<br>
    4. Réordonner la base obtenue par order alphabétique.<br>
    5. Déterminer la taille moyenne des communes (variable nombre de personnes: NBPERSMENFISC16) et quelques statistiques descriptives de ces données. Comparer aux mêmes statistiques sur les données où libellés et codes communes coïncident.<br>
    6. Vérifier les grandes villes (> 100 000 habitants) et regarder la proportion pour lequelles un même nom est associé à différents codes commune.<br>
    7. Vérifier dans <code>filosofi</code> combien de villes sont nommées "Montreuil". De même avec celle qui contiennent "Saint-Denis".<br>
    8. Quelles conclusions peut-on tirer de cet exercice ?<br>
  </div>
</details>

Nous allons maintenant calculer l'empreinte carbone par habitant.

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 3
  </summary>
  <div style="padding: 12px;">
    1. Créer une variable <code>emissions</code> qui correspond aux émissions totales d’une commune.<br>
    2. Faire une jointure à gauche entre les données d’émissions et les données de cadrage.<br>
    3. Calculer l’empreinte carbone (émissions totales / population). <br>
    4. Faire un histogramme de l’empreinte carbone et un autre du log de l'empreinte carbone.<br>
    5. Regarder la corrélation entre les variables et l’empreinte carbone. Certaines variables semblent-elles pouvoir potentiellement influer sur l’empreinte carbone ?
  </div>
</details>
