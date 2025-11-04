---
layout: page_Manipulation
title: Partie 1 - Manipulation de données
description: 
img: assets/img/12.jpg
importance: 2
category: ADD
related_publications: true
---

# Introduction 


On associe souvent les *data scientists* à la conception et à la mise en œuvre de modèles d’intelligence artificielle et/ou d'apprentissage machine/profond. Pourtant, il ne faut pas oublier que l’entraînement et l’exploitation de ces modèles ne constituent pas nécessairement le cœur de leur activité quotidienne.

En réalité, une grande partie de leur travail consiste à collecter des sources de données variées, à les structurer et à les harmoniser afin de permettre une analyse exploratoire préalable à toute modélisation ou visualisation. Dans de nombreux contextes, c’est même cette phase de préparation et de compréhension des données qui définit véritablement le rôle du *data scientist*. L’élaboration de modèles pertinents repose en effet sur une réflexion approfondie autour des données — une étape essentielle qu’il serait risqué de négliger.

Les logiciels de programmation conçus autour du concept de base de données sont aujourd’hui les outils de référence des *data scientists*. La possibilité d’appliquer un ensemble d’opérations standardisées sur des bases de données, quelle qu’en soit la nature, permet aux programmeurs d’être bien plus efficaces que s’ils devaient répéter manuellement ces manipulations, comme dans `Excel`.

La plupart des langages dominants dans l’écosystème de la data science reposent sur la notion de **dataframe**, un objet central dans certains environnements, notamment `R`. Cette approche s’inscrit dans la continuité de la logique SQL, un langage déclaratif vieux de plus de cinquante ans, qui offre un cadre robuste pour réaliser des opérations structurées sur les données (création de nouvelles colonnes, filtrage de lignes, agrégations, etc.).

En Python, toutefois, le concept de **dataframe** ne s’est véritablement imposé que récemment, grâce à la création du package `Pandas` par {% cite mckinney2012python %}. L’essor spectaculaire de cette bibliothèque a largement contribué à la popularité de `Python` dans le domaine de la data science. En quelques années, `Pandas` a profondément transformé la manière de coder en `Python`, en orientant ce langage particulièrement flexible vers l’analyse de données.

Cette partie du cours propose une introduction générale à l’écosystème riche et diversifié de la manipulation de données avec `Python`. Vous y découvrirez les principales bibliothèques Python dédiées à ces tâches, ainsi que les concepts fondamentaux qui sous-tendent leur utilisation. L’objectif est de vous fournir une base solide pour aborder la data science avec `Python`, en mettant l’accent sur les techniques et outils essentiels pour manipuler efficacement les données. 
