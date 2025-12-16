---
layout: page_intro
title: Scraping
description:
img: assets/img/12.jpg
importance: 4
category: ADD
related_publications: False
---

# 1 **Introdution**

Ce cours facultatif propose :

- Une introduction au web scraping et aux principales notions liées.
- Une mise en pratique à travers un tutoriel de la librairie `Python` `BeautifulSoup`.
- Des liens vers des ressources supplémentaires.

Il suppose que vous avez une connaissance préalable de la syntaxe `HTML`.

# 2 **Présentation du web scraping**

## 2.1 **Qu'est ce que le web scraping ?**

Internet est composé de sites web, eux même découpés en pages web contenant des informations. Le web scraping est l'ensemble des méthodes et pratiques visant à récupérer ces informations **_sans que cela ne soit prévu par leur publieur_**.
On peut classer la majorité de ces pratiques en deux parties :

1.  la récupération d'un contenu brut (voir 2.1.1)
2.  l'extraction de l'information cible de ce contenu brut (voir 2.1.2)

### 2.1.1 **Requêtes `HTTP`**

Lors de la navigation web, des _clients_ (navigateur + humain, scripts, …) envoient des requêtes `HTTP` à des _serveurs_, lesquels fournissent des réponses.
Il existe de nombreux types de requêtes. En voici deux :

- Requête `GET`
  - _Fonction :_ Demande de récupération de données
  - _Structure :_ Les informations décrivant les données demandées sont stockées dans l'URL
- Requête `POST`
  - _Fonction :_ Envoi de données
  - _Structure :_ Des données sont envoyées dans le corps de la requête. Le serveur les traite et fourni une réponse adaptée

Lors d'une requête `HTTP`, on peut aussi spécifier un _header_, c'est à dire un ensemble de métadonnées (données relatives à des données) qui décrit la requête.
Comprendre la structure d'un header est important lors qu'on fait du scraping. Certains serveurs refuseront de répondre si le header n'est pas conforme.
Ci-dessous quelques exemples de header.

- `User-Agent` : identification du client (navigateur, bot, script, …)
  - Ex. : `headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}`
- `Accept` : types de contenu acceptés
  - Ex. : `headers = {'Accept': 'text/html'}`
- `Referer`: URL de la page précédente
  - Ex. : `headers = {'Referer': 'example.org'}`

Finalement, il est possible de spécifier des `cookies` dans une requête `HTTP`. Les cookies sont des données persistantes décrivant le client. Encore une fois, certains serveurs refusent de répondre à moins que certains cookies ne soient spécifiés.

Une requête `HTTP` produira toujours une réponse, sous la forme d'un `status-code` accompagné d'un éventuel contenu. Le `status-code` décrit l'état de la requête : succès (`200`), page non trouvée (`404`), serveur inexistant/ne répondant pas (`500`), …

### 2.1.2 **Structure d'une page web**

Une fois requêté, un serveur web répond le plus souvent par une page web. Les pages web contiennent :

- une structure et un contenu, stockés en `HTML`
- un style `CSS`
- un ensemble d'actions réalisables, par exemple en `JavaScript`, `PHP` ou `Python`.
  C'est généralement la partie `HTML` qui contient l'information cible : le `CSS` est propre à la page et la logique des actions est souvent inaccessible (elle est stockée sur le serveur et n'est "qu'appellée" par la page web).
  Il existe de nombreuses ressources servant à parcourir, filtrer et trier du contenu `HTML` de façon efficiente. La librairie `Python` `BeautifulSoup` est présentée en partie 3.

## 2.2 **Pourquoi et quand faire du web scraping ?**

Certaines pages web contiennent des informations précieuses et utiles sans que leur publieur n'ait prévu de manière rapide et automatisable de les récupérer.
C'est dans un tel contexte que le web scraping est pertinent.
Comme évoqué plus haut, faire du scraping consiste à récupérer des données en utilisant des méthodes **_non prévues par les publieurs_**.
Il s'oppose donc à l'utilisation d'API, le téléchargement de données publiques structurées (CSV, …) ou la communication directe avec les publieurs ("Pouvez-vous me fournir des données pour un projet étudiant ?").  
Ces méthodes sont plus officielles, plus simples et souvent plus fructueuses. Il convient donc de les privilégier (ou au moins de les considérer) avant de passer au scraping.
En outre, le scraping soulève parfois des considérations éthiques voire juridiques.

## 2.3 **Implications juridiques**

Les sites internet interdisent souvent le scraping de leur contenu. Plusieurs raisons à cela :

- Les données sont parfois sensibles (personnelles, financièrement ou politiquement chargées, …)
- Les données sont parfois le fond de commerce du site. Si elles sont recupérables publiquement, il perd une source de revenus
- Faire du scraping nécessite parfois de lancer un grand nombre de requêtes `HTTP` en peu de temps. Le serveur doit donc être robuste pour y répondre, ce qui implique des coûts
- Ils le peuvent légalement :
  - [art. L335-2 du CPI](https://www.legifrance.gouv.fr/codes/article_lc/LEGIARTI000032655082) : les textes, images et vidéos stockées sur internet sont protégés. Leur scraping sans autorisation peut mener à 3 ans d'emprisonnement et 300 000€ d'amende. Les données brutes et les informations factuelles ne sont pas concernées.
  - [art. L342-1 du CPI](https://www.legifrance.gouv.fr/codes/article_lc/LEGIARTI000006279247) : les bases de données nécessitant un investissement substantiel sont protégées.
  - [RGPD](https://www.cnil.fr/fr/comprendre-le-rgpd/les-six-grands-principes-du-rgpd) : les données personnelles ont une législation spécifique, plus stricte.
  - Le scraping peut être explicitement interdit dans les CGU du site.
  - Les sites fournissent le plus souvent un fichier `robots.txt` à leur racine (ex. : https://fr.wikipedia.org/robots.txt). Ce fichier indique aux scripts automatisés (ex. : algorithmes de référencement de Google) à quelles portions du sites ils ont le droit d'accéder. Le contourner peut être interpété comme une volonté de nuire.
  - [art. 323-1 et suivants du code pénal](https://www.legifrance.gouv.fr/codes/article_lc/LEGIARTI000047052655/2023-12-21) : À toutes ces interdictions s'ajoute la juridiction relative à l'utilisation de méthodes frauduleuses (piratage informatique).

Il convient de respecter les différents cadres juridiques lorsque vous faites du web scraping. En outre, vous pouvez appliquer les bonnes pratiques suivantes :

- Vérifier si des données publiques/API existent
- Consulter le `robots.txt` et les CGU
- Demander l'autorisation
- En cas de récupération de données personnelles, anonymiser (supprimer noms, identifiants, adresses mails, …)
- Limiter le volume au nécessaire (quelques centaines de pages au maximum)
- Respecter un délai entre les requêtes (quelques secondes au minimum)
- Utiliser un `User-Agent` identifiable
- Documenter la démarche

# 3 **Comment faire du web scraping ?**

Cette partie présente deux librairies `Python` incontournables pour le web scraping : `requests` pour automatiser les requêtes `HTTP` et `BeautifulSoup` pour parser le contenu `HTML` ainsi récupéré.

## 3.1 **Préliminaires**

Vous aurez besoin d'un environnement sur lequel sont installées au moins deux librairies : `requests` et `beautifulsoup4`.

```python
pip install requests
pip install beautifulsoup4
```

En outre, une première analyse manuelle des pages à scraper pourra être réalisée avec l'inspecteur d'élément de votre navigateur.
Pour y accéder, vous pouvez faire `clic-droit > Inspecter` ou `F12 > Inspecteur` sur la page concernée.
Vous pouvez ensuite naviguer dans les conteneurs et les balises `HTML` de la page jusqu'à isoler ceux qui vous intéressent.

## 3.2 **Récupérer une page web avec `requests`**

### 3.2.1 **Requête `GET` naïve**

Comme la majorité des outils `Python`, la librairie `requests` est haut-niveau.
Vous pouvez lancer une requête `HTTP` et lire la réponse du serveur en vous basant sur la méthode `get()`.

```python
import requests

url = "https://fr.wikipedia.org/"
response = requests.get(url)

print(response.status_code)
```

Suite à la requête précédente, vous devriez obtenir un `status-code 403 (Forbidden)`. Cela signifie que le serveur de Wikipédia a refusé de répondre à votre requête.
Vous pouvez consulter la ou les raison·s dans `response.text` ou `response.content`

### 3.2.2 **Utilisation de headers**

Ajoutons un header constitué d'un simple `User-Agent` à notre requête pour respecter les exigences de Wikipédia.

```python
import requests

url = 'https://fr.wikipedia.org/'
headers = {
    "User-Agent": "user-agent-example/1.0 (https://example.com; contact@example.com)"
}

response = requests.get(url, headers = headers)

print(response.status_code)
print(response.text[:1000])
```

Cette fois, vous devez obtenir un `status-code 200 (OK)` accompagné du contenu `HTML` de la page d'accueil de Wikipédia français.
Notez bien que le `User-Agent` fourni au serveur ne vous décrit pas vraiment. Wikipédia accepte de répondre parce qu'il se base sur la bonne foi des utilisateurs et que le rapport coût/bénéfice d'un filtrage rigoureux n'est pas intéressant. Si vous utilisez un `User-Agent` honnête, vous évitez :

- D'être malhonnête
- D'être incontactable, et donc d'être banni sans sommation si vos requêtes ne respectent pas les CGU
- Des `status-code 403` sur des sites plus rigoureux

Les mêmes remarques s'appliquent à l'utilisation de cookies.

### 3.2.3 **Paramètres d'URL**

De nombreux sites web passent des informations dans l’URL sous forme de paramètres de requête (ou query string), par exemple :

> https://fr.wikipedia.org/w/index.php?title=Mathématiques_appliquées&printable=yes

Ici, l'URL est composée de :

- une base : https://fr.wikipedia.org/w/index.php
- une query string (après le `?`) composée de deux éléments séparé par `&`
  - title=Mathématiques_appliquées
  - printable=yes

Une bonne pratique est de ne pas construire cette chaîne "à la main" : on laisse `requests` encoder les paramètres grâce à l'argument `params`. Cela évite notamment les erreurs dues aux caractères spéciaux, accents (surtout en français), espaces, …

```python
import requests

url = "https://fr.wikipedia.org/w/index.php"
headers = {
    "User-Agent": "user-agent-example/1.0 (https://example.com; contact@example.com)"
}

params = {
    "title": "Mathématiques_appliquées"
}

response = requests.get(url, headers=headers, params=params)

print(response.status_code)
print(response.text[:1000])
```

En exécutant le code précédent, vous devriez obtenir un `status-code 200` pour la page Mathématiques appliquées de Wikipédia français. Vous pouvez constater avec `response.url` que l'URL transmis par `requests` a bien été adapté.
En consultant `response.text`, vous devez constater que le contenu `HTML` de la réponse est difficilement lisible et exploitable. Nous allons utiliser `BeautifulSoup` pour dépasser ce problème.

## 3.3 **Analyser le contenu `HTML` avec `BeautifulSoup`**

### 3.3.1 **Introduction de l'objet `BeautifulSoup`**

La librairie `BeautifulSoup` permet de manipuler de façon efficiente le contenu HTML récupéré avec `requests`. Pour cela, elle introduit l'objet éponyme `BeautifulSoup`.
Il prend en entrée un `string` contenant du `HTML` (ou du `XML`) et un parser (`"html.parser"` couvre la plupart des besoins simples).

```python
import requests
from bs4 import BeautifulSoup

url = "https://fr.wikipedia.org/w/index.php"
headers = {
    "User-Agent": "user-agent-example/1.0 (https://example.com; contact@example.com)"
}

params = {
    "title": "Mathématiques_appliquées"
}

response = requests.get(url, headers=headers, params=params)

soup = BeautifulSoup(response.content, "html.parser")
```

L'objet ainsi obtenu représente l'arbre `HTML` complet. On peut déjà accéder à quelques éléments de base :

```python
print(soup.title)        # Balise <title>…</title>
print(soup.title.string) # Contenu textuel du <title>
print(soup.find("h1"))   # Première balise <h1> de la page
```

`BeautifulSoup` génère un arbre `HTML`, ce qui signifie qu'on peut le parcourir de parents à enfants :

- `element.parent` : renvoie la balise parente immédiate.

- `element.parents` : itérateur sur tous les ancêtres (parent, grand-parent, etc.).

- `element.children` : itérateur sur les enfants directs (balises et parfois textes).

- `element.descendants` : itérateur sur tous les descendants (enfants, petits-enfants, …).

- `element.find_next_sibling()` / `element.find_previous_sibling()` : les nœuds « frères » juste après / avant (souvent il faut ignorer des retours à la ligne ou espaces).

```python
paragraphe = soup.find("p")
print("Paragraphe :", paragraphe.get_text())

print("Parent :", paragraphe.parent.name)

for child in paragraphe.children:
    print("Enfant :", repr(child))

paragraphe_suivant = paragraphe.find_next_sibling("p")
print("Paragraphe suivant :", paragraphe_suivant.get_text(strip = True))
```

Ces méthodes sont particulièrement utiles lorsqu’on a identifié un point d’entrée (par exemple un titre de section, un tableau, une liste) et que la structure locale est plus fiable que l’ensemble de la page.

### 3.3.2 **Recherche d'éléments et extraction d''informations utiles**

Les méthodes `find()` et `find_all()` permettent respectivement de trouver le premier élément et l'ensemble des éléments qui correspondent à un ensemble de conditions.
Ces conditions peuvent être exprimées sous la forme d'attributs `id`, `class`, … :

```python
# Recherche par id
voir_aussi = soup.find(id = "Voir_aussi").parent.find_next_sibling("ul")
for child in voir_aussi.children:
    print(child.get_text())

# Recherche par classe CSS
files = soup.find_all(class_ = "mw-file-element")
for file in files:
    print("URL de l'image : ", file['src'])
    print("Dimensions : ", file['width'], "*", file['height'], "px", sep = "")
```

Dans l'exemple précédent, la méthode `get_text()` a servi à extraire le texte contenu dans chaque élément `child`. Elle supporte plusieurs paramètres (cf. ci dessus `strip = True`).
Nous avons également extrait des valeurs d'attribut en utilisant l'opérateur `[]` : `BeautifulSoup` procède automatiquement à une traduction `HTML > dictionnaire Python` (dans les grandes lignes).
Il est aussi possible d'utiliser `get()`, ce qui peut éviter des erreurs d'exécution en définissant une valeur par défaut si l'attribut n'existe pas :

```python
soup.find("a").get("attribut-inexistant", None)
```

Comme vous l'aurez compris, `BeautifulSoup` reproduit la structure `HTML` originelle. Plus vous aurez une connaissance fine et profonde du site que vous analysez, plus votre scraping sera efficace.

### 3.3.4 **Conversion en données exploitables**

Le but du scraping est de transformer le `HTML` brut en données structurées et exploitables (`list`, `dict`, fichiers, …).
Dans cette dernière partie, nous allons construire un fichier CSV répertoriant tous les liens internes (vers `wikipedia.org`) de la page Mathématiques appliquées de Wikipédia.

D'abord, on récupère tous les liens de la pages (balises `<a>`).

```python
content = soup.find("div", id="mw-content-text")
raw_links = content.find_all("a")
```

Et on les stocke dans un tableau de dictionnaires.
Ici, la balise `href` fournit les URL relatifs. Pour obtenir les URL absolus, il faudrait concatener l'URL de base (https://fr.wikipedia.org) avec chacun des href.

```python
links = []

for raw_link in raw_links:
    href = raw_link.get("href", "")
    name = raw_link.get_text(strip = True)

    # On ne garde que les liens internes vers d'autres pages Wikipédia
    if href.startswith("/wiki/") and not href.startswith("/wiki/Fichier:"):
        links.append({
            "name": name,
            "url": href
        })
```

Cette structure `Python` est facile à exploiter puisque tout l'écosystème `Python` la supporte. On peut :

- L'exporter vers un fichier CSV, JSON ou autre
- L'analyser avec `Pandas`
- La stocker dans une base de données
- …

```python
import csv

with open("liens_math_appliquees.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(f, fieldnames=["name", "url"])
    writer.writeheader()
    writer.writerows(links)
```

# 4 **Ressource supplémentaires**

- [Documentation d'HTML](https://developer.mozilla.org/fr/docs/Web/HTML)
- [Documention de requests](https://docs.python-requests.org/en/latest/index.html)
- [Documentation de BeautifulSoup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/#)
- La [REGEX](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_expressions/Cheatsheet) permet de naviguer de façon très efficiente dans des ressources `HTML`.
- Le livre Web Scraping with Python de Ryan Mitchell est disponible dans la plupart des librairies. Il est également possible de trouver la version PDF sur internet.
