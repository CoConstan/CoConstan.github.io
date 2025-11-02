---
layout: page_Manipulation
title: Manipuler des données avec Pandas
description: 
img: assets/img/12.jpg
importance: 4
category: ADD
related_publications: True
---

# 1 **Introdution**

Le chapitre d’introduction à `Pandas` a permis de présenter le principe des données organisées sous la forme d’un `DataFrame`, ainsi que la praticité de l’écosystème `Pandas` pour réaliser des opérations simples sur un jeu de données.

Dans la pratique, il est rare de travailler sur une source de données isolée. Un jeu de données prend toute sa valeur lorsqu’il est mis en relation avec d’autres sources.
Pour les chercheurs, cette mise en perspective permet de contextualiser l’information contenue dans une source en la comparant ou en la combinant avec d’autres.
Dans le secteur privé, les data scientists cherchent souvent à associer des informations relatives à une même entité (par exemple, un client) issues de plusieurs bases, ou à comparer les individus entre eux.

L’un des grands atouts des outils modernes de data science — et de `Pandas` en particulier — réside dans la facilité avec laquelle ils permettent de restructurer et de combiner des sources de données pour mener une analyse intégrée.
Ce chapitre vient consolider les notions introduites précédemment en affinant les traitements appliqués aux données. Il se concentrera principalement sur deux types d’opérations :

* les statistiques descriptives par groupe ;

* l’association de données à partir de caractéristiques communes.

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

* Les émissions de gaz à effet de serre estimées au niveau communal par l’ADEME. Le jeu de données est disponible sur [data.gouv](https://www.data.gouv.fr/fr/datasets/inventaire-de-gaz-a-effet-de-serre-territorialise/#_) et requêtable directement dans `Python`.

* Le [code officiel géographique](https://www.insee.fr/fr/statistiques/fichier/6800675/v_commune_2023.csv) de l'Insee. Il permet d'identifier les communes françaises à partir d'un code univoque (code INSEE). 

* Les données [Filosofi](https://www.insee.fr/fr/metadonnees/source/serie/s1172) constituant une source d’information sur les revenus des Français à une échelle spatiale fine, élaborée par l’Insee à partir des déclarations fiscales et des données relatives aux prestations sociales. Dans notre cas, nous utiliserons les niveaux de revenu et les données de population au niveau communal, afin de les mettre en relation avec nos données d’émissions.

Pour faciliter l’import de données Insee, il est recommandé d’utiliser le package `pynsee` qui simplifie l’accès aux principaux jeux de données de l’Insee disponibles sur le site web insee.fr ou via des API. La liste des jeux de données disponibles est consultable [ici](https://inseefrlab.github.io/DoReMIFaSol/articles/donnees_dispo.html).

# 2 **Recupération des données**

## 2.1 Données ADEME

```python
url = "https://koumoul.com/s/data-fair/api/v1/datasets/igt-pouvoir-de-rechauffement-global/convert"
emissions = pd.read_csv(url)
emissions.head(2)
```

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

Pandas a géré automatiquement les types de variables. Il le fait relativement bien, mais une vérification est toujours utile pour les variables qui ont un statut spécifique.

Pour les variables qui ne sont pas en type float alors qu’elles devraient l’être, on modifie leur type.
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

Nous pouvons voir que les secteurs les plus émetteurs, à savoir le transport, l’agriculture et l’industrie, hors énergie. Le fait que l’énergie soit relativement peu émettrice s’explique bien du fait du mix énergétique français où le nucléaire représente une majorité de la production électrique. 

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
communes = cog_2023.loc[cog_2023['TYPECOM']=="COM"]
communes.loc[:, ['COM', 'DEP', 'REG']].nunique()
```
On obtient une serie indexée. Ce n'est pas pratique, on prefère un DataFrame. On utilise donc la méthode `reset_index()`.

```python
communes.groupby('DEP').agg({'COM': 'nunique'}).reset_index().sort_values('COM', ascending = False)
```

## 3.2 Exemple 2: agrégation par groupe

Pour illustrer l'utilisation d'agréggats, nous allons utilisé le jeu de données `filosofi` pour compter la population totale par département.

Il y a deux manières de faire cela : une implicite et une explicite.

```python
# Implicite => il faut faire attention à l'ordre des opérations
filosofi.groupby('dep')['NBPERSMENFISC16'].sum()
```

```python
# Explicite => plus verbeux mais plus clair
filosofi.groupby('dep').agg({'NBPERSMENFISC16': 'sum'})
```

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


Cette structuration en étoile, est historiquement liée aux bases de données relationnelles, aujourd'hui il existe des alternatives plus flexibles sans structure *a priori* où l'information est empilée dans un datalake. Cependant, la structuration en étoile reste très utilisée dans la pratique, notamment de compartimentation de l'information. On ne donne accès qu'aux données nécessaires à une tâche précise, ce qui permet de limiter les risques de fuites de données sensibles.

On parle souvent de jointure de données, un héritage du terme JOIN en SQL. En `Pandas`, et la manière de définir les jointures (left join, right join…) est directement inspirée de SQL. Cette opération est réalisée à l’aide de la méthode `merge()`.

## 4.1 Mise en oeuvre

En Pandas, la méthode la plus pratique pour associer plusieurs jeux de données à partir de caractéristiques communes est la fonction merge().
Ses principaux arguments permettent de contrôler précisément le type et le comportement de la jointure, offrant ainsi une grande flexibilité dans la manière de combiner les sources d’information.
Nous allons les explorer de façon visuelle afin d’en comprendre le fonctionnement.

Dans notre cas d’étude — la construction de statistiques sur les émissions de gaz carbonique —, la base de gauche correspondra au DataFrame `emission`, et la base de droite au DataFrame `filosofi`.

On utilise le term clé(s) pour spécifier la ou les colonnes communes aux deux DataFrames utilisées pour la jointure. Il n'est pas nécessaire que les noms des colonnes soient identiques dans les deux DataFrames, on peut utiliser les arguments `left_on` et `right_on` pour spécifier les noms des colonnes dans chaque DataFrame. Cependant, elles doivent contenir des valeurs identiques pour que la jointure fonctionne correctement (sinon on obtient l'ensemble vide).

De manière général, les jointures sont effectuer sur des colonnes contenant des identifiants uniques (comme un code INSEE, un numéro de sécurité sociale, un identifiant client…).

Il existe quatre types de jointures principales :

  * **Inner join** : ne conserve que les lignes ayant des valeurs correspondantes dans les deux DataFrames. C'est le type de jointure par défaut.

  * **Left join** : conserve toutes les lignes du DataFrame de gauche, et ajoute les colonnes du DataFrame de droite lorsque des correspondances sont trouvées. Les lignes sans correspondance dans le DataFrame de droite auront des valeurs NaN pour les colonnes ajoutées.

  * **Right join** : conserve toutes les lignes du DataFrame de droite, et ajoute les colonnes du DataFrame de gauche lorsque des correspondances sont trouvées. Les lignes sans correspondance dans le DataFrame de gauche auront des valeurs NaN pour les colonnes ajoutées.

  * **Outer join** : conserve toutes les lignes des deux DataFrames, en ajoutant des valeurs NaN pour les colonnes où il n'y a pas de correspondance.

### 4.1.1 Inner join

## 4.2 Exercice d'application
Cet exercice va revenir un peu en arrière afin de saisir pourquoi nous prenons le code INSEE de commune au lieu du nom de la commune pour faire les jointures.


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
    4. Faire un histogramme de l’empreinte carbone du log de l'empreinte carbone.<br>
    5. Regarder la corrélation entre les variables et l’empreinte carbone. Certaines variables semblent-elles pouvoir potentiellement influer sur l’empreinte carbone ?
  </div>
</details>

