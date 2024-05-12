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

### Bonus
- Décélérateur de la balle : Ralentit la vitesse de la balle
- Agrandissement de la taille de la raquette
  
### Malus 
- Accélérateur de la balle
- Réduction de la taille de la raquette 
  
  
--- 
## Bonus et Malus
Les bonus et les malus tombent du ciel, offrant une variété d'effets différents pour pimenter le jeu. Voici les différents types de bonus et de malus disponibles :

### Bonus
- Bleu Foncé : Décélérateur de la balle - Ralentit la vitesse de la balle.
- Vert : Agrandissement de la taille de la raquette - Augmente la taille de la raquette du joueur.
- Magenta : Multiballe - Génère 2 nouvelles balles pour des actions plus dynamiques.

### Malus 
- Jaune : Accélérateur de la balle - Augmente la vitesse de la balle.
- Rouge : Réduction de la taille de la raquette - Diminue la taille de la raquette du joueur.

---
## Notions du cours utilisés / respectées 
- CRTP : SpecialBrick est templatisé à l'aide des classes dont il hérite : BonusBrick et MalusBrick
- polymophisme / héritage (ajouter image schéma héritage)

<img src="diagramme.png">


---
## Répartition des tâches
- Charlotte
- Zoé

---
todo
- patron de conception singleton pour les couleurs 
- simplifier les include / foward declaration
- écrire ce qu'on a implémenté / pas implémenté
- hexagones
- render brick identique à render cell
- ball : attributs inutiles
- pointeur : trasnformer les texture * ...
- const cohérent
- réf, ptr, ...
