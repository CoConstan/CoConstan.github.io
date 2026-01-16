---
layout: page_Modelisation
title: Apprentissage supervisé
description: Régression et classification.
img: assets/img/12.jpg
importance: 3
category: ADD
related_publications: False
---

# 1 Introduction

L’apprentissage supervisé est l’un des principaux paradigmes du machine learning. Il consiste à apprendre une fonction à partir d’exemples labélisé, c’est-à-dire d’un ensemble de données pour lesquelles on connaît à la fois les entrées (ou variables explicatives, appelées features) et les sorties attendues (appelées labels ou cibles). L’objectif est de construire un modèle capable de généraliser, c’est-à-dire de produire des prédictions correctes sur de nouvelles données jamais vues auparavant.

On peut utiliser l'apprentissage supervisé pour résoudre un très large éventail de problème. Voici quelques exemples non exaustif d'application : 

- Prédiction des prix d'actions au cours du temps
- Ciblage publicitaire à partir des données utilisateur
- Estimer le redshift d’une galaxie
- Prédire si un paiement par carte est frauduleux

Cependant, on peut classer ces problèmes en deux grandes catégories : la régression et la classification.

- En régression, la variable cible est **continue**. Le but est de prédire une valeur numérique, par exemple le prix d’un logement, la consommation énergétique d’un bâtiment ou la température future. Les modèles cherchent alors à approximer une relation fonctionnelle entre les variables d’entrée et une sortie réelle.

- En classification, la variable cible est **discrète** et correspond à une ou plusieurs catégories. Il s’agit par exemple de déterminer si un email est un spam ou non, de reconnaître un chiffre manuscrit, ou d’identifier la classe d’un objet dans une image. Le modèle apprend à séparer l’espace des données en régions correspondant aux différentes classes.

[Version slide](https://docs.google.com/presentation/d/1QcpqFq5FKgZ2xpsRaTzryQRyVLcwQmzH/edit?usp=sharing&ouid=112709948187376646473&rtpof=true&sd=true) du cours de 2024-2025 (plein de fautes et à moitié en anglais)

# 2 Formalisme

Le formalisme de l’apprentissage supervisé consiste à estimer une fonction inconnue reliant les variables d’entrée mesurables <b>X ∈ ℝ<sup>d</sup></b> à une sortie cible <b>y</b>, que l’on note <b>y = f(X)</b>. On dispose d’un ensemble d’apprentissage composé de <b>N</b> exemples <b>(x<sub>i</sub>, y<sub>i</sub>)</b>, et l’objectif est d’estimer une fonction <b>f̂</b> qui minimise une erreur moyenne du type <b>∑<sub>i=1</sub><sup>N</sup> ℓ( f(x<sub>i</sub>), y<sub>i</sub> )</b>. 
Dans de nombreuses situations, les variables <b>X</b> sont facilement mesurables, alors que la variable <b>y</b> est soit impossible à observer, soit trop coûteuse ou complexe à mesurer expérimentalement ; le modèle sert alors d’approximation de la relation physique, biologique ou économique sous-jacente.

- Lorsque la variable cible est continue, <b>y ∈ ℝ</b>, on parle de <b>régression</b>, par exemple pour prédire un prix, un redshift ou un taux métabolique, et on minimise typiquement une erreur quadratique. 
- Lorsque la variable cible est discrète, <b>y ∈ {1,…,K}</b>, on parle de <b>classification</b>, par exemple pour détecter une cellule cancereuse à partir d'une image biomedical ou distinguer des images de chien et de chat ; le modèle apprend alors une frontière de décision qui partitionne l’espace des caractéristiques en régions associées aux différentes classes.

# 3 Optimisation 

## 3.1 Descente de gradient
En apprentissage supervisé, on dispose de données sous forme de paires <b>(x<sub>i</sub>, y<sub>i</sub>)</b>, où <b>x<sub>i</sub> ∈ ℝ<sup>d</sup></b> représente les entrées et <b>y<sub>i</sub></b> la sortie cible. On choisit un <b>modèle paramétrique</b> noté <b>f(x, w)</b>, par exemple un modèle linéaire 
<b>y = f(x, w) = w<sub>0</sub> + x · w<sub>1</sub></b>, où <b>w = (w<sub>0</sub>, w<sub>1</sub>)</b> sont les paramètres à apprendre. 
On définit ensuite une <b>fonction de perte</b> (*Loss function*) <b>L(w)</b> qui mesure l’erreur de prédiction sur l’ensemble des données.. 

L’objectif de l’apprentissage est alors de résoudre le problème d’optimisation <b>argmin<sub>w</sub> L(w)</b>, c’est-à-dire de trouver les valeurs de <b>w</b> qui minimisent la *Loss function*.

Dans la majorité des modèles réalistes, la fonction <b>L(w)</b> n’admet pas de solution analytique avec une forme close, et l’on utilise donc des <b>méthodes de descente de gradient</b>, qui mettent à jour les paramètres selon la règle <b>w ← w − η ∇<sub>w</sub> L(w)</b>, où <b>η</b> est le taux d’apprentissage. 

On peut interpréter la *Loss* comme une surface de hauteur <b>L</b> définie sur l’espace des paramètres, par exemple avec <b>w<sub>0</sub></b> en latitude, <b>w<sub>1</sub></b> en longitude, et <b>L(w)</b> en altitude : l’algorithme cherche à descendre vers les points les plus bas de cette surface. Cependant, cette surface peut contenir plusieurs <b>minima locaux</b>, dans lesquels l’algorithme peut se bloquer sans atteindre le minimum global, ce qui rend l’initialisation des paramètres et le choix de l’algorithme d’optimisation particulièrement importants.

<figure style="text-align: center;">
  <img src="{{ site.baseurl }}/assets/img/grad.png" alt="tidy" width="80%">
  <figcaption><em> Source : https://kraj3.com.np/blog/2019/06/introduction-to-gradient-descent-algorithm-and-its-variants/ </em></figcaption>
</figure>

## 3.2 Quelques exemples de Loss function


En <b>régression</b>, où la variable cible est continue, plusieurs fonctions de perte sont couramment utilisées. 

- La plus classique est la <b>Mean Squared Error (MSE)</b>, définie par <b>L = (1/N) ∑<sub>i</sub> ( y<sub>i</sub> − f(x<sub>i</sub>) )²</b>, qui pénalise fortement les grandes erreurs mais est sensible aux valeurs aberrantes. 
- Une alternative plus robuste est la <b>Mean Absolute Error (MAE)</b>, donnée par <b>L = (1/N) ∑<sub>i</sub> | y<sub>i</sub> − f(x<sub>i</sub>) |</b>, qui réduit l’influence des outliers mais conduit à une fonction de coût moins lisse. 
- Un compromis entre les deux est la <b>log-cosh loss</b>, définie par <b>L = (1/N) ∑<sub>i</sub> log( cosh( y<sub>i</sub> − f(x<sub>i</sub>) ) )</b>, qui se comporte comme la MAE lorsque l’erreur est grande (croissance quasi linéaire) et comme la MSE lorsque l’erreur est faible (comportement quadratique).

En <b>classification binaire</b>, la variable cible prend des valeurs <b>y ∈ {0, 1}</b>, et le modèle produit une probabilité de prédiction <b>p = P(y = 1 | x)</b>. 
La fonction de perte standard est l’<b>entropie croisée binaire</b>, définie par <b>L = − (1/N) ∑<sub>i</sub> [ y<sub>i</sub> log(p<sub>i</sub>) + (1 − y<sub>i</sub>) log(1 − p<sub>i</sub>) ]</b>, qui pénalise fortement les prédictions très confiantes mais incorrectes.

En <b>classification multiclasse</b>, on considère <b>K</b> classes et une variable cible codée en "*one-hot*", avec <b>y<sub>i,c</sub> = 1</b> si l’échantillon <b>i</b> appartient à la classe <b>c</b>, et <b>0</b> sinon. Le modèle prédit une distribution de probabilités <b>p<sub>i,c</sub> = P(y = c | x<sub>i</sub>)</b>, vérifiant la contrainte <b>∑<sub>c=1</sub><sup>K</sup> p<sub>i,c</sub> = 1</b> pour chaque échantillon. La perte utilisée est l’<b>entropie croisée catégorielle</b> : <b>L = − (1/N) ∑<sub>i</sub> ∑<sub>c=1</sub><sup>K</sup> y<sub>i,c</sub> log(p<sub>i,c</sub>)</b>, qui mesure la divergence entre la distribution prédite par le modèle et la distribution vraie des classes.

## 3.3 Overfitting/underfitting

On distingue deux problèmes classiques : le <b>sur-apprentissage (overfitting)</b> et le <b>sous-apprentissage (underfitting)</b>. 
On peut les comprendre avec une analogie scolaire : le <b>jeu d’entraînement (train dataset)</b> correspond aux <b>devoirs</b>, tandis que le <b>jeu de test (test dataset)</b> correspond à l’<b>examen</b>. 

Un modèle en <b>overfitting</b> obtient une très faible erreur sur les devoirs mais échoue à l’examen : il a essentiellement <b>appris par cœur</b> les exercices du cours sans comprendre les concepts généraux, ce qui se traduit par une mauvaise généralisation. À l’inverse, un modèle en <b>underfitting</b> n’arrive pas non plus à résoudre correctement les devoirs, car il est trop simple pour capturer la structure des données ; il échoue donc à la fois sur l’entraînement et sur le test.

L’objectif est de trouver un compromis entre ces deux extrêmes en apprenant un modèle qui capture les régularités utiles sans mémoriser le bruit, ce qui revient à minimiser l’erreur de généralisation.

<figure style="text-align: center;">
  <img src="{{ site.baseurl }}/assets/img/over_under.png" alt="tidy" width="80%">
</figure>

# 4 Evaluation 

Pour être sur de ne pas tombé dans le sur-apprentissage ou le sous-apprentissage, la démarche générale en machine learning est la suivante :

<figure style="text-align: center;">
  <img src="{{ site.baseurl }}/assets/img/train_test.png" alt="tidy" width="80%">
  <figcaption><em> Source : https://builtin.com/data-science/train-test-split </em></figcaption>
</figure>

On découpe l’ensemble des données disponibles en deux parties, un échantillons d’apprentissage et un de test. Il existe d'autre moyen de partitionner et valider un dataset, notamment la partition train/val/test et la cross-validation que vous aborderer durant le cours de réseaux de neuronnes au prochain semestre.

En apprentissage automatique, on entraîne les modèles en minimisant une <b>fonction de perte (loss function)</b> <b>L</b>, qui est choisie pour être optimisable (différentiable, stable numériquement), mais qui n’a pas toujours un sens direct pour le problème réel. 
Par exemple, on minimise une entropie croisée ou une erreur quadratique, alors que l’objectif final peut être médical, économique ou sociétal. 
C’est pourquoi on utilise en plus une ou plusieurs <b>métriques d’évaluation</b> pour juger la qualité du modèle, qui peuvent parfois être identiques à la loss, mais le plus souvent sont différentes. 
Une bonne métrique doit être <b>informative</b>, <b>justifiée par le contexte applicatif</b>, <b>facilement compréhensible</b> si possible, et surtout vérifier que <b>meilleur modèle ⇒ meilleur score</b>.

Considérons par exemple la base <b>MNIST</b> (chiffres de 0 à 9). 
Si l’on construit un modèle binaire qui prédit si une image est un <b>0</b> ou non, une métrique naturelle est l’<b>accuracy</b>, définie par 
<b>Acc = (TP + TN) / (TP + TN + FP + FN)</b>. 
Un score de <b>90%</b> peut sembler bon, mais cela dépend fortement de la distribution des classes et du niveau de difficulté du problème : si seulement 10% des images sont des zéros, un classifieur trivial qui prédit toujours “non-0” obtient déjà 90% d’accuracy sans rien apprendre.

Cette limite est encore plus critique dans des applications sensibles comme le <b>pré-dépistage du cancer</b>, où l’on prédit la présence de la maladie à partir d’un test sanguin. 
Un modèle avec <b>99% d’accuracy</b> peut être trompeur si la maladie est rare : il peut prédire presque toujours “pas de maladie" et rester très précis tout en ratant la majorité des cas positifs. 
Dans ce contexte, des métriques comme :

- la <b>précision</b> <b>Precision = TP / (TP + FP)</b> 
- le <b>rappel (sensibilité)</b> <b>Recall = TP / (TP + FN)</b> sont souvent plus pertinentes.

Par exemple, une précision de <b>50%</b> signifie qu’un patient sur deux déclaré positif est en réalité sain, ce qui peut être inacceptable selon le contexte clinique, même si l’accuracy globale reste élevée. 

Ainsi, le choix des métriques est indissociable des enjeux du problème, et l’évaluation doit toujours être interprétée à la lumière de l’application finale.

# 4.1 Métriques pour la classification

Classification Binaire (0-1, negative-positive)
- TP: true positive    
- FP: false positive   
- TN: true negative 
- FN: false negative

<figure style="text-align: center;">
  <img src="{{ site.baseurl }}/assets/img/metric.png" alt="tidy" width="60%">
  <figcaption><em> Source : https://towardsdatascience.com/demystifying-confusion-matrix-29f3037b0cfa </em></figcaption>
</figure>

Voici quelques métrique à utile dans ce cas : 

- Accuracy = (TP + TN) / (TP + TN + FP + FN)
- true positive rate (ou recall/sentivity), TPR = (TP) / (TP + FN)
- true negative rate (ou specificity),  TNR = (TP) / (TP + FN)
- false positive rate: 1 - TNR
- F1 score, précision …

La fonction `classification_report` de `sk-learn` vous fournie directement l'ensemble de ces métriques.

# 4.2 Métriques pour la régression

En régression, plusieurs métriques permettent d’évaluer la qualité d’un modèle en comparant les valeurs réelles <b>y<sub>i</sub></b> et les prédictions <b>ŷ<sub>i</sub></b>, elles peuvent aussi être utiliser comme loss function (si différentiable) :

- <b>MSE (Mean Squared Error)</b> = <b>(1/N) ∑<sub>i=1</sub><sup>N</sup> ( y<sub>i</sub> − ŷ<sub>i</sub> )²</b>. Elle mesure l’erreur quadratique moyenne et pénalise fortement les grandes erreurs.
- <b>MAE (Mean Absolute Error)</b> = <b>(1/N) ∑<sub>i=1</sub><sup>N</sup> | y<sub>i</sub> − ŷ<sub>i</sub> |</b>. Elle correspond à l’erreur absolue moyenne et est plus robuste aux valeurs aberrantes que la MSE.

- <b>RMSE (Root Mean Squared Error)</b> = <b>√( (1/N) ∑<sub>i=1</sub><sup>N</sup> ( y<sub>i</sub> − ŷ<sub>i</sub> )² )</b>. C’est la racine carrée du MSE.

- <b>Coefficient de détermination R²</b> = <b>1 − [ ∑<sub>i</sub> ( y<sub>i</sub> − ŷ<sub>i</sub> )² / ∑<sub>i</sub> ( y<sub>i</sub> − ȳ )² ]</b>, 
où <b>ȳ</b> est la moyenne des valeurs réelles. Il mesure la proportion de la variance expliquée par le modèle : <b>R² = 1</b> correspond à une prédiction parfaite, <b>R² = 0</b> à un modèle équivalent à la moyenne, et des valeurs négatives indiquent un modèle pire que cette baseline. 


# 5 Exercices

<div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 20px;">

  <a href="https://drive.google.com/file/d/1bEqzLsN1Cg6n0uYu451c4E3X0gqzCg_s/view?usp=sharing" style="text-decoration: none;">
    <div style="border: 1px solid #ddd; border-radius: 12px; padding: 20px; text-align: center; transition: transform 0.2s;">
      <h3> TP04 - Supervised Learning : Classification sur MNIST</h3>
    </div>
  </a>
</div>


Dans le cas où vous ne souhaitez pas utiliser colab, vous pouvez télécharger les notebooks en cliquant sur le lien suivant :
**[Correction_manip.zip]({{ site.baseurl }}/assets/files/TP04_ML.zip)**

