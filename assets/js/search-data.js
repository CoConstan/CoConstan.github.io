// get the ninja-keys element
const ninja = document.querySelector('ninja-keys');

// add the home and posts menu items
ninja.data = [{
    id: "nav-about",
    title: "about",
    section: "Navigation",
    handler: () => {
      window.location.href = "/";
    },
  },{id: "nav-cv",
          title: "cv",
          description: "",
          section: "Navigation",
          handler: () => {
            window.location.href = "/cv/";
          },
        },{id: "nav-teaching",
          title: "Teaching",
          description: "Materials for courses I taught",
          section: "Navigation",
          handler: () => {
            window.location.href = "/teaching/";
          },
        },{id: "books-the-godfather",
          title: 'The Godfather',
          description: "",
          section: "Books",handler: () => {
              window.location.href = "/books/the_godfather/";
            },},{id: "projects-nettoyer-des-données",
          title: 'Nettoyer des données',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Clean/";
            },},{id: "projects-dlmi-2025-classification",
          title: 'DLMI 2025 - Classification',
          description: "Hands-on",
          section: "Projects",handler: () => {
              window.location.href = "/projects/DLMI2025/";
            },},{id: "projects-deep-learning-project-4a",
          title: 'Deep Learning Project - 4A',
          description: "Resources for the 4th Year&#39;s Deep Learning Project at Polytech Lyon",
          section: "Projects",handler: () => {
              window.location.href = "/projects/DL_4A/";
            },},{id: "projects-analyse-de-données",
          title: 'Analyse de données',
          description: "Python et data science",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Intro_ADD/";
            },},{id: "projects-intro-python",
          title: 'Intro Python',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Intro_python_ADD/";
            },},{id: "projects-partie-1-manipulation-de-données",
          title: 'Partie 1 - Manipulation de données',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Manipulation_ADD/";
            },},{id: "projects-manipuler-des-données-avec-pandas",
          title: 'Manipuler des données avec Pandas',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Manipuler_des_donn%C3%A9es/";
            },},{id: "projects-modélisation",
          title: 'Modélisation',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Modelisation_ADD/";
            },},{id: "projects-évaluation",
          title: 'Évaluation',
          description: "Attendus et critères de notation",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Notation/";
            },},{id: "projects-numpy",
          title: 'Numpy',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Numpy/";
            },},{id: "projects-introduction-à-pandas",
          title: 'Introduction à Pandas',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Pandas/";
            },},{id: "projects-les-questions-à-se-poser-face-à-un-jeu-de-données",
          title: 'Les questions à se poser face à un jeu de données',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Question/";
            },},{id: "projects-operational-research",
          title: 'Operational Research',
          description: "Linear programming and graph theory",
          section: "Projects",handler: () => {
              window.location.href = "/projects/RO/";
            },},{id: "projects-récuperer-des-données",
          title: 'Récuperer des données',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Recup/";
            },},{id: "projects-visualisation",
          title: 'Visualisation',
          description: "",
          section: "Projects",handler: () => {
              window.location.href = "/projects/Visualisation_ADD/";
            },},{
        id: 'social-email',
        title: 'email',
        section: 'Socials',
        handler: () => {
          window.open("mailto:%63%6F%72%65%6E%74%69%6E.%63%6F%6E%73%74%61%6E%7A%61@%63%72%65%61%74%69%73.%69%6E%73%61-%6C%79%6F%6E.%66%72", "_blank");
        },
      },{
        id: 'social-linkedin',
        title: 'LinkedIn',
        section: 'Socials',
        handler: () => {
          window.open("https://www.linkedin.com/in/corentin-constanza", "_blank");
        },
      },{
      id: 'light-theme',
      title: 'Change theme to light',
      description: 'Change the theme of the site to Light',
      section: 'Theme',
      handler: () => {
        setThemeSetting("light");
      },
    },
    {
      id: 'dark-theme',
      title: 'Change theme to dark',
      description: 'Change the theme of the site to Dark',
      section: 'Theme',
      handler: () => {
        setThemeSetting("dark");
      },
    },
    {
      id: 'system-theme',
      title: 'Use system default theme',
      description: 'Change the theme of the site to System Default',
      section: 'Theme',
      handler: () => {
        setThemeSetting("system");
      },
    },];
