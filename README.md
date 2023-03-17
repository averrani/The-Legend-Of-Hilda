# The-Legend-Of-Hilda

Informations factuelles :

NOM DU PROJET : The Legend Of Hilda

The Legend Of Hilda :
    Incarnez Link dans le monde de Lorule, infesté par des créatures abominables n'ayant que pour unique but de vous corrompre.
    Détruisez ces calamités et avancez dans ce monde afin de récolter des rubis et devenir plus puissant.
    Le jeu est toujours en cours de développement. Uniquelent le coeur du jeu et les fonctionnalités principales ont été ajoutées. 

Manuel :

Une fois dans le répertoire de rendu (celui dans lequel se trouve ce readme), la commande "make" permet de compiler le code et de produire trois exécutables.

Le premier peut être lancé grâce à la commande "./bin/mainTxt".
Il représente la version en mode texte archaïque du programme graphique. La fenêtre représente une petite carte de 15*15 cellules.
En haut à gauche de celle-ci se trouve le personnage contrôlé par l'utilisateur : Link, représenté par un H.
Ce-dernier peut être déplacé respectivement vers le haut, gauche, bas et droite grâce aux touches Z, Q, S et D.
Le programme peut être interrompu avec la touche P.

Le deuxième exécutable peut être lancé grâce à la commande "./bin/mainSFML".
Une fois exécuté, le programme prend la forme d'une fenêtre SFML. Le programme est un jeu vidéo. Le joueur contrôle Link : le personnage blond aux habits verts.
Ce-dernier peut être déplacé respectivement vers le haut, gauche, bas et droite grâce aux touches Z, Q, S et D.
Maintenir la touche Shift gauche enfoncée a pour effet de faire courir Hilda, qui se déplace alors plus vite.
Appuyer sur la touche Shift gauche enclenche l'attaque d'Hilda. Il utilise alors son épée pour frapper en arc-de-cercle devant lui, selon son orientation actuelle.
Enfin, appuyer sur la touche ESC a pour effet de fermer la fenêtre et d'arrêter l'exécution.
Hilda se trouve sur une carte et est entouré d'autres entités, désignées ci-après par le terme "monstre".
Si Hilda touche un monstre avec son épée lors d'une attaque, le monstre perdra un coeur.
Si un monstre n'a plus de coeur, il disparaitra. A son emplacement se trouvera parfois un rubis. Les rubis sont la monnaie du jeu. Hilda peut les ramasser en marchant dessus.
Si Hilda touche un monstre sans l'attaquer, c'est lui qui subira des dégats et perdra un coeur.
Si Hilda n'a plus de coeur, il retournera automatiquement à son point de départ sur la carte et perd quelques rubis.
Sur la carte se trouve également des obstacles tels que des arbres ou des maisons. Hilda ne peut pas marcher dessus.
Si Hilda franchit le bord de la carte, il se retrouvera dans une autre carte, sur laquelle se trouvent d'autres monstres et obstacles.

Le troisième exécutable peut être lancé grâce à la commande "./bin/mainDefil".
Une fois exécuté, le programme prend la forme d'une fenêtre SFML. L'utilisateur ne peut pas intéragir avec le programme (excepté pour y mettre un terme).
La fenêtre représente la carte présentée ci-avant, défilant toute seule.

Finalement, la commande "make clean" a pour effet de supprimer tous les fichiers objets et les exécutables de l'archive.



Organisation de l'archive :

Ci-dessous se trouve une description du rôle de chacun des répertoires de l'archive :
"bin" contient, s'ils sont produits, les exécutables décrits ci-avant.
"Data" contient tous les fichiers de données à savoir :
    "font" contenant le fichier .ttf définissant la police de caractère utilisée par le programme principal.
    "graphics" contenant les images servant d'éléments du programme principal, tels que la spritesheet d'Hilda ou les images des obstacles.
    "map" contenant les fichiers .txt dans lesquels sont contenues toutes les cartes du programme principal, sous forme de caractère ensuites traduits par le code.
    "music" contenant le fichier .ogg définissant la musique entendue en jouant au jeu ainsi que les fichiers de sons.
"obj" contient les fichiers objets utilisés pour créer les exécutables.
"src" contient les fichiers .h et .cpp ayant servis à coder le programme.
De plus, Makefile est le fichier servant à compiler le code et créer les exécutables.
