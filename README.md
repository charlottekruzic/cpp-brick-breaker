# Projet : Programmation Avancée
_Charlotte Kruzic & Zoé Marquis_

### Briques :
- de différentes forces : 
    - vert = force 1
    - jaune = force 2
    - orange = force 3
    - rouge = force 4
    - violet = force 5
- bonus (juste une image, pas identifiable)
  - décélérateur de la balle
  - agrandissement de la taille de la raquette
- malus (juste une image, pas identifiable)
  - accélérateur de la balle
  - taille de la raquette réduite

- Les briques Bonus et Malus n'ont pas besoin d'etre détruites pour gagner la partie.
- brique indestructible réutiliser wall ? ? : mur => incassable (ne fait pas partie des briques à casser)

### Bonus / Malus tombant : 
- COULEUR : décélérateur de la balle
- COULEUR : accélérateur de la balle
- COULEUR : agrandissement de la taille de la raquette
- COULEUR : taille de la raquette réduite

## Notions du cours utilisés / respectées 
- CRTP : MalusBonusBrick et BonusMalus dérievent de leurs enfants
- polymophisme / héritage (ajouter image schéma héritage)

---
todo
- multiballes : idée gérer une map de pointeur dans game comme pour les 
  - compteur pour savoir si il reste au moins une balle -> détermine la fin de partie
  - supprimer une balle à chaque fois qu'elle sort du cadre

- dossier bonus malus et brique
- simplifier les include

- moins de bonus / malus
- écrire ce qu'on a implémenté / pas implémenté
- triangles 
- hexagones