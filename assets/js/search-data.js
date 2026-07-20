// get the ninja-keys element
const ninja = document.querySelector('ninja-keys');

// add the home and posts menu items
ninja.data = [{
    id: "nav-bio",
    title: "Bio",
    section: "Navigation",
    handler: () => {
      window.location.href = "/";
    },
  },{id: "nav-news",
          title: "News",
          description: "",
          section: "Navigation",
          handler: () => {
            window.location.href = "/news/";
          },
        },{id: "nav-presentations",
          title: "Presentations",
          description: "",
          section: "Navigation",
          handler: () => {
            window.location.href = "/presentation/";
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
            },},{id: "news-began-my-phd-under-the-supervision-of-david-sarrut-and-ane-etxebeste-at-creatis-and-insa-lyon",
          title: 'Began my PhD under the supervision of David SARRUT and Ane ETXEBESTE at...',
          description: "",
          section: "News",},{id: "news-presented-at-ai-wild-west-workshop",
          title: 'Presented at AI WILD West Workshop.',
          description: "",
          section: "News",},{id: "news-presented-at-iabm-2026-conference",
          title: 'Presented at IABM 2026 conference.',
          description: "",
          section: "News",},{id: "news-presented-at-the-2026-ai-for-reconstruction-in-biomedical-imaging-symposium-in-london",
          title: 'Presented at the 2026 AI for Reconstruction in Biomedical Imaging Symposium in London....',
          description: "",
          section: "News",},{id: "news-the-work-i-did-during-my-master-s-thesis-on-novelty-detection-algorithms-for-drug-screening-was-published-in-acs-infectious-diseases",
          title: 'The work I did during my Master’s thesis on novelty detection algorithms for...',
          description: "",
          section: "News",},{id: "news-our-ieee-mic-2026-submission-was-accepted-for-a-short-talk-and-a-poster-presentation",
          title: 'Our IEEE MIC 2026 submission was accepted for a short talk and a...',
          description: "",
          section: "News",},{id: "presentations-unrolled-mapem-for-spect-reconstruction",
          title: 'Unrolled MAPEM for SPECT reconstruction',
          description: "",
          section: "Presentations",handler: () => {
              window.location.href = "/presentations/AIWILDWest/";
            },},{id: "presentations-unrolled-mapem-for-spect-reconstruction",
          title: 'Unrolled MAPEM for SPECT reconstruction',
          description: "",
          section: "Presentations",handler: () => {
              window.location.href = "/presentations/IABM2026/";
            },},{id: "presentations-jacobian-free-unrolling-memory-efficient-unrolled-network-for-3d-spect-reconstruction",
          title: 'Jacobian-Free Unrolling: memory-efficient unrolled network for 3D SPECT reconstruction',
          description: "",
          section: "Presentations",handler: () => {
              window.location.href = "/presentations/SynRBI/";
            },},{id: "teaching-analyse-de-données",
          title: 'Analyse de données',
          description: "Python et Data Sciences",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/analyse-de-donnees/";
            },},{id: "teaching-dlmi-2025-classification",
          title: 'DLMI 2025 - Classification',
          description: "Hands-on",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/DLMI2025/";
            },},{id: "teaching-deep-learning-project-4a",
          title: 'Deep Learning Project - 4A',
          description: "Resources for the 4th Year&#39;s Deep Learning Project at Polytech Lyon",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/DL_4A/";
            },},{id: "teaching-tp0-introduction-à-python",
          title: 'TP0 - Introduction à Python',
          description: "",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/analyse-de-donnees/introduction-python/";
            },},{id: "teaching-operational-research",
          title: 'Operational Research',
          description: "Linear programming and graph theory",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/RO/";
            },},{id: "teaching-statistiques-et-applications-médicales-avancées",
          title: 'Statistiques et applications médicales avancées',
          description: "Supports de cours et travaux pratiques",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/statistiques-applications-medicales/";
            },},{id: "teaching-traitement-des-signaux-physiologiques",
          title: 'Traitement des signaux physiologiques',
          description: "Supports de cours et travaux pratiques",
          section: "Teaching",handler: () => {
              window.location.href = "/teaching/traitement-signaux-physiologiques/";
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
