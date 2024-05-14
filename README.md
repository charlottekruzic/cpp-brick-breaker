# Projet : Programmation Avancée
_Charlotte Kruzic & Zoé Marquis_

## Jeu du Casse-briques
Ce projet implémente un jeu du casse-briques classique avec plusieurs types de briques, des bonus et des malus.

---
## Briques
Le jeu comprend différents types de briques, chacune ayant une force différente :

- Brique bleu très clair : force 1
- Brique bleu clair  : force 2
- Brique bleu moyen : force 3
- Brique violette : force 4
- Brique violette foncée : force 5

Dans cette version du jeu, nous avons ajouté des briques Bonus/Malus. Ces briques spéciales sont masquées derrière une image, ce qui signifie que vous ne pouvez pas savoir à l'avance quels types de bonus <img src="img/etoile.png" width="30" height="30"> (ou vert foncé si le mode de jeu n'est pas celui avec des carrés)
 ou de malus <img src="img/goomba.png" width="30" height="30"> (ou rouge foncé si le mode de jeu n'est pas celui avec des carrés)
 se cachent derrière elles. Contrairement aux briques basiques, ces briques n'ont pas besoin d'être cassées pour remporter la partie.

### Briques Indestructibles
En plus des briques cassables, il existe des briques indestructibles, des murs 
<img src="img/wall.png" width="30" height="30"> (ou marron si le mode de jeu n'est pas celui avec des carrés),  qui ajoutent de la complexité d'accès à certaines zones du jeu. Ces briques ne peuvent pas être détruites et ne contribuent pas à la victoire du joueur.

### Briques Bonus
- Décélérateur de la balle: Réduit (progressivement) la vitesse de la balle. Cette action s'applique à toutes les balles, même si elles ont des vitesses différentes dûes à leur moment de création (à l'initialisation d'une balle elle a une vitesse définie). Une vitesse minimale est définie.
- Agrandissement de la taille de la raquette : Augmente la taille de la raquette, permettant au joueur de couvrir une zone plus large du terrain de jeu.
  
### Briques Malus 
- Accélérateur de la balle: Augmente (progressivement) la vitesse de la balle. Cette action s'applique à toutes les balles, même si elles ont des vitesses différentes dûes à leur moment de création (à l'initialisation d'une balle elle a une vitesse définie). Une vitesse maximale est définie.
- Réduction de la taille de la raquette : Réduit la taille de la raquette, permettant au joueur de couvrir une zone plus restreinte du terrain de jeu.
  
--- 
## Bonus et Malus
Les bonus et les malus tombent du ciel, offrant une variété d'effets différents pour pimenter le jeu. Voici les différents types de bonus et de malus disponibles :

### Bonus
- Bleu Foncé : Décélérateur de la balle.
- Vert : Agrandissement de la taille de la raquette
- Magenta : Multiballe - Génère 2 nouvelles balles pour des actions plus dynamiques.

### Malus 
- Jaune : Accélérateur de la balle.
- Rouge : Réduction de la taille de la raquette.

---
## Répartition des tâches

- Charlotte s'est occupée de la plateforme, de la balle, des collisions entre la plateforme, les briques et la balle, et en partie de la gestion de jeu. Elle a aussi réalisé les différentes formes pour Carré / Triangle / Hexagone.
  
- Zoé s'est occupée de la grille, des différentes briques (polymorphisme, CRTP), des différents bonus/malus ainsi que leurs interactions avec le reste du jeu. Elle a aussi réalisé la *"templitasion"* afin de pouvoir réaliser les différentes formes de grille.

---
## todo 
- police : dire qu'on a utilisé une police ilbre de droit ?
- documentation
- const et ref ?
- écrire ce qu'on a implémenté / pas implémenté
- simplifier les include / foward declaration
- écrire ce qu'on a implémenté / pas implémenté
- weak_ptr
- to do zoé
- h / hpp / cpp comme il faut ?
----
## Énoncé : 
- [x] une plateforme déplaçable au clavier ou à la souris
- [x] une balle qui rebondit en fonction de son angle d'impact
- [x] des briques de différents types avec différentes résistances
- [x] au moins trois types de bonus/malus dont le multi-balle
- [x] différentes grilles chargées depuis un fichier ASCII 
- [x] supporter différentes formes de grilles de briques : hexagonales et triangulaires
- [x] Utilisez la STL au maximum  :
  - [x] Pas de tableau! des conteneurs STL
  - [x] Pas de pointeur! des unique/shared/weak_ptr
  <p style="color:purple;">
    ... on a fait au maximum
    - des fois pas nécessaires : SDL2 typiquement quand dans la meme fonction on ouvre et ferme proprement, pas nécessaire d'utiliser ce genre de pointeur, qui ne sont présents que dans ce bloc </p>  
  - [x] Utilisez les algorithmes de la STL
    - donner un exemple
- [x] Écrivez des classes pour vos objets et encapsulez la SDL2
- [x] Utilisez de l'héritage et du polymorphisme
<img src="diagramme.png">
- [ ] Soyez const-correct et efficaces, pas de copie inutile
    - on pense que c'est fait, mais il reste certainement des choses à améliorer ! 
    - par manque de temps, on n'a pas pu s'en assurer
- [x] Documentez votre code
    - Doxygen
- [x] Utilisez une convention de codage
  - mettre convention, langue etc


---
## Notions du cours utilisées
- **CRTP** : *SpecialBrick* est templatisée à l'aide des classes dont il hérite : *BonusBrick* et *MalusBrick* (qui ont un cacun attribut *static* pour ne charger qu'une fois les images dans le jeu avec la forme carré).
- **Mixin** : *SquareCell*, *TriangleCell* et *HexagonCell* partagent des fonctionnalités (typiquement la fonction *draw*)
