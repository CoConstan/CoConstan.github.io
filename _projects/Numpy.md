---
layout: page_Manipulation
title: Numpy
description: 
img: assets/img/12.jpg
importance: 4
category: ADD
toc : False
related_publications: False
---

## 1 Introduction

`NumPy` est une bibliothèque Python optimisée pour le calcul numérique. Elle offre :  

- **Tableaux multidimensionnels (`ndarray`)** plus performants que les listes Python  
- **Fonctions mathématiques optimisées** pour l’algèbre linéaire, les statistiques et les transformations  
- **Gestion efficace de grandes quantités de données** grâce à ses opérations vectorisées  
- **Interopérabilité** avec d'autres bibliothèques comme SciPy et Pandas.  

C’est un outil clé pour la data science et l’intelligence artificielle. Vous trouverez la documentation complète ici : [Documentation Numpy](https://numpy.org/doc/stable/)

<details open style="border: 2px solid #2196F3; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E3F2FD; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    💡Remarque
  </summary>
  <div style="padding: 12px;">
   Pytorch (l'une des librairies de références pour le deep learning) possède une syntaxe quasiment identique à Numpy. La parrelisation d'un code NumPy est donc presque "automatiques".
  </div>
</details>

Dans ce chapitre, nous utiliseront la convention qui s'est imposé pour l'importation de `NumPy`, à savoir : 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
import numpy as np
</code>
</pre>
</div>

## 2 Les Arrays

Dans le domaine de la science des données — comme nous le verrons plus en détail dans les prochains chapitres — l’élément central est le tableau de données à deux dimensions. La première dimension correspond aux lignes et la seconde aux colonnes. Lorsqu’on ne s’intéresse qu’à une seule dimension, on considère alors une variable, c’est-à-dire une colonne du tableau. Il est donc naturel d’établir un lien entre ces tableaux de données et les objets mathématiques que sont les matrices et les vecteurs.

`Numpy` constitue la brique de base pour manipuler efficacement des données numériques, organisées sous forme de tableaux ou de matrices. Il fournit des structures de données adaptées ainsi qu’un large ensemble d’opérations mathématiques et algébriques, absentes du langage Python standard.

L’objet central de `NumPy` est l’`array`, un tableau de données multidimensionnel. Il peut être unidimensionnel et s’apparenter à un vecteur, bidimensionnel et se rapprocher d’une matrice, ou plus généralement prendre la forme d’un objet à n dimensions, appelé `ndarray`, que l’on peut voir comme un ensemble de tableaux emboîtés.

### 2.1 Création d'array

Il existe plusieurs moyens de créer un *array*. La plus simple est à partir d'une liste. Pour se faire on utilise la méthodes <code>np.array</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.array([1, 2, 3, 4, 5])
</code>
</pre>
</div>

<code>
array([1, 2, 3, 4, 5])
</code>

On peut aussi utiliser des séquences logiques avec <code>np.arange</code> (suite) ou  <code>np.linespace</code> (interpolation linéaire, *equivalant au linspace de matlab*)

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.arange(0,5)
</code>
</pre>
</div>

<code>
array([0, 1, 2, 3, 4])
</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.arange(0, 50, 10)
</code>
</pre>
</div>

<code>
array([0, 10, 20, 30, 40])
</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.linspace(0, 1, 4)
</code>
</pre>
</div>

<code>
array([0., 0.33333333, 0.66666667, 1.])
</code>

Si on veut initialiser un array à 0, 1 ou un nombre quelconque on utiliseras les fonctions <code>np.zeros</code>, <code>np.ones</code> ou <code>np.full</code>.

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.zeros(10, dtype=float)
</code>
</pre>
</div>

<code>
array([0., 0., 0., 0., 0., 0., 0., 0., 0., 0.])
</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.ones((2,2), dtype=int)
</code>
</pre>
</div>

<code>
array([[1, 1],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[1, 1]])
</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.full((2, 2), 3.14)
</code>
</pre>
</div>

<code>
array([[3.14, 3.14],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.14, 3.14]])
</code>

Pour créer une matrice identité, on utilise <code>np.eyes</code>: 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.eyes(3)
</code>
</pre>
</div>

<code>
array([[1., 0., 0.],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[0., 1., 0.],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[0., 0., 1.]])
</code>

### 2.2 Création d'array aléatoire

Le module `numpy.random` fournit toute une liste de fonctions pour la génération de matrices aléatoires.

Pour faire un tirage uniforme : 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.random.rand(3,3)
</code>
</pre>
</div>

<code>
array([[0.17455977,0.40903843, 0.97271591],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[0.77478127, 0.97271591, 0.77172352],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[0.62838879, 0.4985154 , 0.54871591]])
</code>

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 1
  </summary>
  <div style="padding: 12px;">
    Créer une fonction « gazparfait » permattant de modéliser PV = nRT avec les unités suivantes (généralement utilisées):
    - P = pression du gaz en Pa
    - V = volume en m3
    - n = quantité de matière en mol
    - T = température absolue en K (Kelvins)
    - R = 8.314 SI (si les unités utilisées sont celles ci-dessus)

    Calculer l'array des valeurs de quantité de matière (n) Y associées aux valeurs de pression X = 15, 89, 56, 78, 152, 66, 48, 77, 2, 96.
  </div>
</details>

Pour faire un tirage suivant une loi normal N(0,1) : 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
np.random.randn(3,3)
</code>
</pre>
</div>

<code>
array([[0.99447383,-1.06050264, -0.42279998],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[-0.15762056, 0.12981994, -0.6188213],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[-0.31845562, 0.4485154 , 0.54871591]])
</code>

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 2
  </summary>
  <div style="padding: 12px;">
    - Générer $X$ une variable aléatoire, correspondant à 1000 réalisations d’une loi $U(0,1)$ <br>
    - Générer $Y$ une variable aléatoire, correspondant à 1000 réalisations d’une loi $N(0,2)$ <br>
    - Verifié les moyennes et variances à l'aide de `np.var` et `np.mean`<br>    
    - Créer une fonction `statdesc` permettant de calculer la moyenne, médiane, écart-type, minimum et maximum.
  </div>
</details>


## 3 Indexation et slicing

Comme vous avez pu le remarquer, l'indexation de Numpy suit l'indexation classique d'une liste, elle commence à 0 et finit à n-1.

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
a = np.arange(5)
print(a)
</code>
</pre>
</div>

<code>
[0, 1, 2, 3, 4]
</code>

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
a[2]
</code>
</pre>
</div>

<code>
np.int64(2)
</code>

Cette idée est generalisable en dimension supérieur. 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
a = np.array([[1, 2, 3], [4, 5, 6]])
a[1,2]
</code>
</pre>
</div>

<code>
np.int64(6)
</code>


Le slicing en NumPy permet d'extraire des parties d'un tableau (`ndarray`) en utilisant la notation `array[start:stop:step]`. Cela permet notamment de réaliser des coupes 2D (slices) dans une image 3D stocker dans un array. Ou une colone/ligne dans un tableau 2D.

Par exemple si on veut selectionné la 1ère colone du tableau précédent :

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
a[:,1]
</code>
</pre>
</div>

<code>
array([2, 5], dtype=int64)
</code>

Voici quelques exemples en vrac de slicing : 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
# Création d'un tableau NumPy  
arr = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])  

# Slicing de base  
print(arr[2:6])   # [2 3 4 5]  (de l'index 2 à 5)  
print(arr[:5])    # [0 1 2 3 4] (du début à l'index 4)  
print(arr[5:])    # [5 6 7 8 9] (de l'index 5 à la fin)  
print(arr[::2])   # [0 2 4 6 8] (tous les 2 éléments)  
print(arr[::-1])  # [9 8 7 6 5 4 3 2 1 0] (tableau inversé)  

# Slicing en 2D  
mat = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])  
print(mat[:2, 1:])  # [[2 3]  
                    #  [5 6]] (extraction d’un sous-tableau)  

# Slicing avec un tableau de booléens
arr = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
print(arr[arr > 5])  # [6 7 8 9] (éléments plus grands que 5)
</code>
</pre>
</div>

### 3.1 Filtre logiques
On peut également sélectionner des données à partir de conditions logiques, grâce à ce qu’on appelle un boolean mask. Cette approche est souvent plus pratique et sert principalement à filtrer les données de manière flexible.

Pour des comparaisons simples, l’utilisation des opérateurs logiques est généralement suffisante. Ces comparaisons s’appliquent aussi aux tableaux multidimensionnels, car NumPy exploite le mécanisme du broadcasting, sur lequel nous reviendrons plus en détail par la suite.

Un petit exemple : 

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
x = np.arange(10)
mask = x>4
print(mask)
print(x[mask])
</code>
</pre>
</div>

<code>
[False False False False False  True  True  True  True  True]<br>
[5 6 7 8 9]
</code>

### 3.2 Une petite subtilité
Un aspect fondamental de la performance de NumPy par rapport aux listes Python réside dans la gestion du slicing. Lorsqu’un découpage est effectué sur une liste, Python crée systématiquement une copie de la portion sélectionnée. Cette duplication engendre un surcoût en mémoire et en temps d’exécution, particulièrement lorsque les structures de données sont volumineuses.

En revanche, dans le cas d’un array NumPy, le slicing ne produit pas de copie : il génère une vue (view) qui fait simplement référence aux données sous-jacentes. Ainsi, toute modification appliquée à cette vue impacte directement l’array d’origine.

Lorsque la création d’une copie indépendante est nécessaire — par exemple pour préserver l’intégrité du tableau initial — il est possible d’utiliser explicitement la méthode `copy`.
<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
x_slice_copy = x[:2].copy()
</code>
</pre>
</div>


## 4 Manipuler un Array

NumPy propose de nombreuse méthodes et fonctions pour modifier un array :

| Opération     | Type | Implementation |
|---------|----:| |
| Aplatir un array      |  méthodes | `x.flatten()` |
| Transposer un array   |  méthodes | `x.T` |
| Transposer un array   |  fonction | `np.transpose(x)` |
| Ajouter des éléments à la fin d'un array   |  fonction | `np.append(x, element)` |
| Ajouter des éléments à une position d'un array   |  fonction | `np.insert(x, position, element)` |
| Supprimer des éléments     |  fonction | `np.delete(x, position)` |
| Trier un array | fonction | `np.sort(x)` |
| Concatenation | fonction | `np.concatenate((x1,x2), axis)` |

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 3
  </summary>
  <div style="padding: 12px;">
    - Créer l'array à partir de la liste suivante : [17, 38, 10, 25, 72] <br>
    - trier et afficher l'array <br>
    - ajouter l’élément 12 à l'array et afficher l'array <br>
    - afficher l'array inverse <br>
    - afficher l’indice de l’élément 17 <br> 
    - afficher la slice du 2e au 3e élément <br>
    - afficher la slice du début au 2e élément <br>
    - afficher la slice du 3e élément à la fin de l'array <br>
    - afficher le dernier élément en utilisant un indiçage négatif.
  </div>
</details>

## 5 Braodcasting
Le broadcasting désigne l’ensemble des règles qui permettent d’effectuer des opérations entre des tableaux de dimensions différentes. Concrètement, il s’agit d’étendre automatiquement les dimensions d’un tableau afin de rendre l’opération compatible, sans avoir à dupliquer explicitement les données.

Par exemple, le broadcasting permet d’appliquer une opération impliquant un scalaire à l’ensemble des éléments d’un tableau NumPy. Ainsi, le scalaire 3 peut être traité comme un tableau de dimension trois pour être ajouté élément par élément à un array de taille 3.

<div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
<pre>
<code>
a = np.array([0, 1, 2])
b = np.array([3, 3, 3])

print(a + b)
print(a + 3)
</code>
</pre>
</div>

<code>
[3, 4, 5]<br>
[3, 4, 5]
</code>

<details open style="border: 2px solid #4CAF50; border-radius: 8px; margin: 16px 0;">
  <summary style="background: #E8F5E9; padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    📝 Exercice 4
  </summary>
  <div style="padding: 12px;">
    1. Créer <code>X</code> un tableau à deux dimensions (i.e. une matrice) comportant 10 lignes et 2 colonnes. Les nombres dans le tableau sont aléatoires. <br>
    2. Importer <code>matplotlib.pyplot</code> sous le nom <code>plt</code>. Utiliser <code>plt.scatter</code> pour représenter les données sous forme de nuage de points.<br>
    3.Constuire une matrice 10x10 stockant, à l’élément $(i,j)$ la distance euclidiennee entre les points $X[i,]$ et $X[j,]$. Pour cela, on utilisera la fonction <code>np.newaxis</code> :<br>
    &nbsp;&nbsp;&nbsp;&nbsp;    - Utiliser <code>X1 = X[:, np.newaxis, :]</code> pour transformer la matrice en tableau emboîté. Vérifier les dimensions.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;    - Créer <code>X2</code> de dimension <code>(1, 10, 2)</code> de la même façon.
    &nbsp;&nbsp;&nbsp;&nbsp;    - En déduire, pour chaque point, la distance avec les autres points pour chaque coordonnées. Elever celle-ci au carré.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;    - Vous devriez avoir un tableau de dimension <code>(1, 10, 2)</code>. La réduction à une matrice 10x10 s’obtient en sommant sur le dernier axe.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;    - Appliquer la racine carrée pour obtenir une distance euclidienne. <br>
    &nbsp;&nbsp;&nbsp;&nbsp;    - Vérifier que les termes diagonaux sont bien nuls.<br>
    4. Il faut maintenant classer pour chaque point les points dont les valeurs sont les plus similaires. Utiliser <code>np.argsort</code> pour obtenir, pour chaque ligne, le classement des points les plus proches.<br>
    5. On cherche les k-plus proches voisins. Pour le moment, fixons k=2. Utiliser <code>argpartition</code> pour réordonner chaque ligne de manière à avoir les 2 plus proches voisins de chaque point d’abord et le reste de la ligne ensuite.<br>
    6. Représenter graphiquement les plus proches voisins. (Utiliser l'indice ci-dessous si vous bloquez)<br>
    7. Quelle est la complexité de cet algorithmes ? 
  </div>
</details>

<details style="border-radius: 8px; margin: 16px 0;">
  <summary style="padding: 8px 12px; font-weight: bold; color: #0D47A1; cursor: pointer;">
    Indice pour la question 6.
  </summary>
  <div style="margin: 20px 0; font-family: 'Courier New', monospace; font-size: 0.9em;">
  <pre>
  <code>
    plt.scatter(X[:, 0], X[:, 1], s=100)

    # draw lines from each point to its two nearest neighbors
    K = 2

    for i in range(X.shape[0]):
        for j in nearest_partition[i, :K+1]:
            # plot a line from X[i] to X[j]
            # use some zip magic to make it happen:
            plt.plot(*zip(X[j], X[i]), color='black')
  </code>
  </pre>
  </div>
</details>