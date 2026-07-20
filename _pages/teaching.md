---
layout: page
permalink: /teaching/
title: Teaching
description: Materials for courses I taught
nav: true
nav_order: 6
display_categories: [Polytech, Deep Learning for Medical Imaging Spring school - 2025]
display_departments: [MAM - Applied Maths and Modeling, GBM - Biomedical Engineering]
---

<!-- pages/teaching.md -->
<div class="teaching">
{% if site.enable_teaching_categories and page.display_categories %}
  <!-- Display categorized teaching materials -->
  {% for category in page.display_categories %}
  <a id="{{ category | slugify }}" href="#{{ category | slugify }}">
    <h2 class="category">{{ category }}</h2>
  </a>
  {% assign categorized_teaching = site.teaching | where: "category", category %}
  {% assign sorted_teaching = categorized_teaching | sort: "importance" %}
  <!-- Generate cards for each teaching page -->
  {% if category == "Polytech" %}
    {% for department in page.display_departments %}
      {% assign department_teaching = sorted_teaching | where: "department", department %}
      <h3 class="department">{{ department }}</h3>
      <div class="row row-cols-1 row-cols-md-3">
        {% for teaching in department_teaching %}
          {% include teaching.liquid %}
        {% endfor %}
      </div>
    {% endfor %}
  {% elsif page.horizontal %}
  <div class="container">
    <div class="row row-cols-1 row-cols-md-2">
    {% for teaching in sorted_teaching %}
      {% include teaching_horizontal.liquid %}
    {% endfor %}
    </div>
  </div>
  {% else %}
  <div class="row row-cols-1 row-cols-md-3">
    {% for teaching in sorted_teaching %}
      {% include teaching.liquid %}
    {% endfor %}
  </div>
  {% endif %}
  {% endfor %}

{% else %}

<!-- Display teaching materials without categories -->

{% assign sorted_teaching = site.teaching | sort: "importance" %}

  <!-- Generate cards for each teaching page -->

{% if page.horizontal %}

  <div class="container">
    <div class="row row-cols-1 row-cols-md-2">
    {% for teaching in sorted_teaching %}
      {% include teaching_horizontal.liquid %}
    {% endfor %}
    </div>
  </div>
  {% else %}
  <div class="row row-cols-1 row-cols-md-3">
    {% for teaching in sorted_teaching %}
      {% include teaching.liquid %}
    {% endfor %}
  </div>
  {% endif %}
{% endif %}
</div>
