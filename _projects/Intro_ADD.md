---
layout: page_intro
title: Analyse de données
description: Python et data science
img: assets/img/12.jpg
importance: 1
category: Polytech
related_publications: true
toc: true
---

# Introduction

Ce cours est à destination des élèves de 3A MAM de Polytech Lyon dans le cadre du module Analyse de données. Il a pour principal objectif d'introduire les élèves à la *Data Science*, une discipline scientifique très large à la frontière des **mathématiques, de la statistique et de l'informatique**. Ce cours vise a un apprentissage pratique de la démarche scientifique rigoureuse à adopter face à des données, les problèmes rencontré et les solutions disponible pour essayer de les dépasser. Pour ce faire nous nous concentrerons sur l'apprentissage de l'outils (pratiquement) indispensable pour resoudre ces problèmes, le langage `Python`. 

En soit Python n'est qu'un pretexte et un outil, si demain pour une raison X ou Y, Python n'est plus utilisé (très improbable), ce cours devrait vous permettre d'apprendre à avoir les bons réflexes quand on est confronté à un jeu de données.

Ce cours est une actualisation du cours *Patrice Mazel*, grandement inspiré (notamment la première partie) par le cours [Python pour la data science](https://pythonds.linogaliana.fr/) {% cite galiana2023 %} et du livre {% cite mckinney2012python %}, principal auteur de la library **pandas**.

# Pourquoi utiliser Python ?

Python est un langage de programmation simple, puissant et polyvalent. Sa syntaxe claire et lisible ainsi que sa documentation de qualité en fait un excellent choix aussi bien pour les débutants que pour les développeurs expérimentés. De plus, python est plutot simple à associer à des langages plus performants (C++/CUDA). 

Pour ces raisons, Python a su agrégé une comunauté hétérogène, allant de lycéen à des chercheurs de haut niveau, travaillant sur une grande varieté de sujets aussi bien théoriques que pratiques. 

Ce succès, est difficilement explicable sans parler de l'emergence de la Data Science et des metiers associé, apparue dans les années 2010. Les Data Scientist, responsable de l'exploitation de données pour en tirer de la valeur (prédictions, analyses, recommandations) ont besoin de communiquer facilement avec les differents profils interdependants que sont les *data engineer* et *ML engineer*.

# Plan du cours

La première partie de ce cours se concentre sur ce qu'on appelle aujourd'hui le "*feature engineering*" (aussi parfois nommé "*data munging*"). Cette partie **[Manipulation]({{ site.baseurl }}/projects/Manipulation_ADD)**, servira de fondement pour le reste du cours, elle se concentrera sur la récupération, la structuration, l'exploration et la mise en relation de donnée. Souvent négligé, ces étapes étapes constituent une part importante et indispendable du temps de travail d'un data scientist. Le principal outil utiliser sera la library `Pandas`.

La deuxième partie, **[Visualisation]({{ site.baseurl }}/projects/Visualisation_ADD)**, est consacrée à la création de graphiques et de visuels afin de synthétiser nos données après les avoir nettoyé et mise en forme. Relativement introductive, cette partie se concentrera sur l'apprentissage des librairy `matplotlib` et `seaborn`. 

La troisième partie, **[Modélisation]({{ site.baseurl }}/projects/Modelisation_ADD)**, à pour obectif au travers d'un exemple d'illustrer la dermarche scientifique, les choix methodologique et technique nécessaire pour l'étude d'un jeux de donnée. Ce chapitre sera aussi une introduction à certain concept appartennant au champs du *Machine Learning*.

Vous trouverez aussi dans la partie **[Intro Python]({{ site.baseurl }}/projects/Intro_python_ADD)** un ensemble d'exercices facultatif, permettant de prendre en main (ou reviser) les bases du langague. 

