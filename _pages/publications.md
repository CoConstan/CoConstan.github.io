---
layout: page
permalink: /publications/
title: Publications
description: Publications grouped by type.
nav: true
nav_order: 2
---

<!-- Each BibTeX entry must define one of the following fields:
     category = {journal-article}
     category = {international-conference}
     category = {national-conference} -->

{% include bib_search.liquid %}

<div class="publications">

  <h2>Journal Articles</h2>

  {% bibliography --query @*[category=journal-article]* %}

  <h2>International Conferences</h2>

  {% bibliography --query @*[category=international-conference]* %}

  <h2>National Conferences</h2>

  {% bibliography --query @*[category=national-conference]* %}

</div>
