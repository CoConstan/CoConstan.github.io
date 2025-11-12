---
layout: page
title: Évaluation
description: Attendus et critères de notation
img: assets/img/12.jpg
importance: 2
category: ADD
related_publications: False
---

# 1. Résumé 

* La note finale sera composer de 2 notes différentes : 
  * Une note de projets (40% rapport + 40% oral)
  * Une note de QCM (20%)
* Des QCM non annoncés à l’avance seront organisés en début de cours, pour une durée maximale de 10 à 15 minutes.
* Le projets sera à rendre à la fin du semestre, par **groupe de 2 ou 3 personnes**. Un **rapport écrit** (format Jupyter Notebook encouragé) ainsi qu’une présentation **orale** (10min + 5min de questions) seront demandés.
* Le sujet est libre, il doit comporter :
  * Une valorisation d’un ou plusieurs jeux de données *open data* ou collectés par le biais de scraping ou d’API.
  * De la visualisation 
  * De la modélisation
* Les étudiants sont invités à proposer des sujets qui leur plaisent, à faire valider par le chargé de TD. 
* **Les projets issus de compétitions type Kaggle sont interdits.**
* Le projet doit être **reproductible** et **documenté**. Le rapport doit contenir des explications claires sur les choix méthodologiques et techniques effectués.
* Un code source partagé (GitHub, GitLab, etc) sera valorisé.


Deadline pour le projet: 

| Étape | Date | 
|---------|----|
| Validation des sujets |  10 décembre 2025 | 
| Rendu du projets   |  XX | 
| Soutenance   |  XX | 

<br>

# 2. QCM 

Des QCM non annoncés à l’avance seront organisés en début de cours, pour une durée maximale de 10 à 15 minutes. Ils porteront sur des notions de bases abordée dans les TPs. Toutes questions a sa reponse sur ce site. Le but est de s'assurer que les étudiants ont bien assimilé les notions de base. 


# 3. Attendus pour le projet

Le projet, par groupe de 2 ou 3 étudiants, consiste à l'analyse d'une **problématique de votre choix**, en utilisant un ou plusieurs jeux de données *open data* ou collectés par le biais de scraping ou d’API. 

La première étapes est de bien **définir la question** que vous souhaitez aborder. Pour cela il est nécéssaire de contextualiser et de problematiser le sujet. Il est encouragé de choisir un sujet qui vous intéresse personnellement, cela rendra le travail plus agréable et motivant.

Le projet doit articuler les trois étapes suivantes :

1. Collecte et exploration des données
2. Visualisation et comunication des résultats
3. Analyse et/ou Modélisation

Il n'est pas nécessaire de couvrir ces trois étapes de manière exhaustive, mais il est important de montrer une compréhension claire de chacune d'entre elles. Il est attendu qu'au moins une de ces étapes soit approfondie.

Enfin, un effort de synhtèse est attendu, tant dans le rapport écrit que dans la présentation orale. Le but est de rendre votre travail accessible et compréhensible pour un public non spécialiste. L'objectif n'est pas de tout montrer, mais de **sélectionner** et **mettre en valeur** les éléments les plus pertinents de votre analyse.

## 3.1 Récupération des données

Les données utilisées dans votre projet peuvent provenir de diverses sources : fichiers CSV, API, scraping, etc. Plus la collecte de ces données demande d’efforts ou de compétences techniques (par exemple, le croisement de plusieurs sources, l’automatisation via une API ou le scraping multi-pages), plus cette partie pourra être valorisée dans votre évaluation.

À l’inverse, si vous choisissez un jeu de données déjà prêt à l’emploi, il sera important de le compléter ou de l’enrichir (ajout de variables, intégration de données complémentaires, restructuration, etc.) afin que cette étape ait une réelle valeur ajoutée.

Dans la majorité des cas, les données brutes ne seront pas directement exploitables. Vous devrez donc effectuer un nettoyage rigoureux : traitement des valeurs manquantes, harmonisation des formats, renommage des variables, transformation des types, etc. Cette étape est également l’occasion de créer des variables plus pertinentes ou plus faciles à interpréter.

Enfin, pensez à bien documenter et justifier vos choix. Un code clair et bien commenté facilitera la compréhension de votre démarche.

<details open style="border: 2px solid #F44336; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #FFEBEE; padding: 8px 12px; font-weight: bold; color: #B71C1C; cursor: pointer;">
    Quelles sources utiliser ?
  </summary>
  <div style="padding: 12px;">
    <p>Pour trouver des jeux de données, plusieurs plateformes d’<em>open data</em> sont disponibles en ligne. Voici quelques exemples :</p>
    <ul>
      <li><a href="https://www.data.gouv.fr/fr/" target="_blank">data.gouv.fr</a> : La plateforme officielle française d’open data, proposant une grande variété de jeux de données publics.</li>
      <li><a href="https://data.grandlyon.com/" target="_blank">data.grandlyon.com</a> : Données spécifiques à la métropole de Lyon, couvrant divers domaines tels que les transports, l’environnement, etc.</li>
      <li><a href="https://www.insee.fr/fr/statistiques" target="_blank">insee.fr</a> : Données statistiques officielles en France, couvrant des aspects démographiques, économiques, sociaux, etc.</li>
      <li><a href="https://data.ademe.fr/" target="_blank">data.ademe.fr</a> : Données environnementales et énergétiques fournies par l’Agence de la transition écologique (ADEME).</li>
      <li>
        <a href="https://www.openstreetmap.org/" target="_blank">OpenStreetMap</a>, 
        <a href="https://www.wikidata.org/" target="_blank">Wikidata</a>, ou 
        <a href="https://fr.openfoodfacts.org/" target="_blank">OpenFoodFacts</a> : Bases de données collaboratives et ouvertes sur divers sujets.
      </li>
    </ul>
    <p>Les jeux de données provenant de Kaggle ou d’autres compétitions similaires sont <strong>interdits</strong>. Ces jeux de données sont peu propices à des recherches originales. En pratique, les principales analyses possibles se limitent à comparer des algorithmes pour optimiser leurs performances, ce qui n’est pas l’objectif du projet.</p>

  </div>
</details>



## 3.2 Visualisation et Analyses descriptives

Les statistiques descriptives constituent une étape essentielle du projet. Elles doivent permettre de comprendre la structure de la base de données et d’en dégager les premières tendances majeures. L’objectif est d’obtenir une vision d’ensemble : comment les données se relient à la problématique posée, en quoi elles permettent d’y répondre, et quels premiers enseignements elles apportent. Chaque analyse doit être interprétée, il ne suffit pas d’afficher des tableaux ou un simple describe sans en tirer de conclusions.

Pour la partie visuelle, plusieurs niveaux d’analyse sont possibles selon la profondeur du travail. Une bonne visualisation repose avant tout sur un choix pertinent du graphique et une présentation claire : légendes explicites, axes correctement nommés, titres lisibles, etc.

Enfin, un graphique n’a de valeur que s’il est expliqué. Précisez ce qu’il met en évidence et comment il vient appuyer, ou au contraire remettre en question, votre raisonnement.

## 3.3 Modélisation

La phase de modélisation intervient lorsque les statistiques descriptives ne suffisent plus à répondre entièrement à la problématique, ou lorsqu’un modèle peut venir compléter et renforcer l’analyse exploratoire.
Le choix du modèle (régression linéaire, random forest, réseau de neuronnes, etc.) importe moins que sa pertinence : il doit être cohérent avec votre question de recherche et justifié dans sa mise en œuvre.

Il est tout à fait possible (et même recommandé) de confronter plusieurs approches aux objectifs différents : par exemple, utiliser une classification hiérarchique ascendante (CAH) pour créer des groupes ou de nouvelles variables, puis une régression pour analyser les relations entre ces groupes et d’autres variables.

Même si le projet n’est pas celui d’un cours de statistiques, la rigueur scientifique reste essentielle : votre démarche doit être structurée, et vos résultats interprétés de manière critique.

# 4 Format du rendu

Pour le rendu, vous devrez :

* Rédiger un rapport écrit (format Jupyter Notebook encouragé) présentant votre démarche, vos analyses et vos résultats. Le rapport doit être clair, structuré et bien documenté, avec des explications sur les choix méthodologiques et techniques effectués.
* Transmettre le code source de votre projet. L’utilisation de plateformes comme GitHub est recommandée et sera valorisé.
* Préparer une présentation orale de 10 minutes, suivie de 5 minutes de questions. La présentation doit synthétiser les points clés de votre projet et mettre en avant les résultats les plus significatifs.

# 5. Exemples de projet

Quelques exemples de projets possibles (non exhaustifs) :

* Peut-on prédire l'apparition de feu de forêt à partir de données météorologiques et géographiques ?
* Études de l’évolution de la qualité de l’air dans les grandes villes françaises sur les dix dernières années.
* Présidentielle 2022 : Analyse des tendances de vote à partir des données socio-économiques et historiques.
* Étude qualitative des commentaires YouTube visant à mesurer la perception et la réception de la vidéo par les spectateurs.
* L’insertion professionnelle chez les jeunes, analyse des facteurs influençant le taux d’emploi à 6 mois après l’obtention du diplôme.