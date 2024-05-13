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
 se cachent derrière elles. Contrairement aux briques normales, ces briques n'ont pas besoin d'être cassées pour remporter la partie.

### Briques Indestructibles
En plus des briques cassables, il existe des briques indestructibles qui ajoutent de la complexité d'accès à certaines zones du jeu. Ces briques ne peuvent pas être détruites et ne contribuent pas à la victoire du joueur.
<img src="img/wall.png" width="30" height="30">
(ou marron si le mode de jeu n'est pas celui avec des carrés)

### Briques Bonus
- Décélérateur de la balle : Ralentit la vitesse de la balle
- Agrandissement de la taille de la raquette
  
### Briques Malus 
- Accélérateur de la balle
- Réduction de la taille de la raquette 
  
--- 
## Bonus et Malus
Les bonus et les malus tombent du ciel, offrant une variété d'effets différents pour pimenter le jeu. Voici les différents types de bonus et de malus disponibles :

### Bonus
- Bleu Foncé : Décélérateur de la balle - Ralentit la vitesse de la balle.
- Vert : Agrandissement de la taille de la raquette - Augmente la taille de la raquette du joueur.
- Magenta : Multiballe - Génère 2 nouvelles balles pour des actions plus dynamiques.

### Malus 
- Jaune : Accélérateur de la balle - Augmente la vitesse de la balle.
- Rouge : Réduction de la taille de la raquette - Diminue la taille de la raquette du joueur.

---
## Notions du cours utilisées et respectées 
- Polymophisme / Héritage
<img src="diagramme.png">
- **CRTP** : SpecialBrick est templatisée à l'aide des classes dont il hérite : BonusBrick et MalusBrick, qui ont un attribut *static* pour ne charger qu'une fois les images (dans le jeu avec la forme carré).

- ptr
- const
- ...

---
## Répartition des tâches
- Charlotte s'est occupée de la plateforme, de la balle, des collisions entre la plateforme, les briques et la balle, et en partie de la gestion de jeu. Elle a aussi réalisé les différentes formes pour Carré / Triangle / Hexagone.
- Zoé s'est occupée de la grille, des différentes briques (polymorphisme, CRTP), des différents bonus/malus ainsi que leurs interactions avec le reste du jeu. Elle a aussi réalisé la *"templitasion"* afin de pouvoir réaliser les différentes formes de grille.

---
## todo
- patron de conception singleton pour les couleurs 
- simplifier les include / foward declaration
- écrire ce qu'on a implémenté / pas implémenté
- render brick identique à render cell
- ball : attributs inutiles
- pointeur : trasnformer les texture * ...
- const cohérent
- réf, ptr, ...
- images libres de droits