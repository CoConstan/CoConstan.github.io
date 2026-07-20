---
layout: page
title: Presentations
permalink: /presentation/
description:
nav: true
nav_order: 3
---

{% assign talks = site.presentations | sort: "date" | reverse %}
{% assign groups = talks | group_by_exp: "t", "t.date | date: '%Y'" %}

{% for g in groups %}

## {{ g.name }}

{% for t in g.items %}

### <a href="{{ t.url | relative_url }}">{{ t.title }}</a> <small>({{ t.date | date: "%b %Y" }})</small>

**{{ t.type }}** · {{ t.venue }}{% if t.location %} — {{ t.location }}{% endif %}

<div class="presentation-links">
  {% if t.slides %}
    <a class="presentation-link" href="{{ t.slides | relative_url }}">
      <i class="fa-solid fa-display" aria-hidden="true"></i><span>Slides</span>
    </a>
  {% endif %}
  {% if t.poster %}
    <a class="presentation-link" href="{{ t.poster | relative_url }}">
      <i class="fa-solid fa-image" aria-hidden="true"></i><span>Poster</span>
    </a>
  {% endif %}
  {% if t.video %}
    <a class="presentation-link" href="{{ t.video }}">
      <i class="fa-solid fa-circle-play" aria-hidden="true"></i><span>Vidéo</span>
    </a>
  {% endif %}
  {% if t.paper %}
    <a class="presentation-link" href="{{ t.paper }}">
      <i class="fa-solid fa-file-lines" aria-hidden="true"></i><span>Article</span>
    </a>
  {% endif %}
  {% for L in t.links %}
    <a class="presentation-link" href="{{ L.url }}">
      <i class="fa-solid fa-arrow-up-right-from-square" aria-hidden="true"></i><span>{{ L.text }}</span>
    </a>
  {% endfor %}
</div>

<hr>
{% endfor %}
{% endfor %}
