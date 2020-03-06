# Pong3DS
Mon Projet Tutoré 4

# Qu'est-ce que c'est ?
Je suppose que vous connaissez déjà le jeu Pong. Sinon, Google est votre ami.
Il s'agit donc d'un pong compatible avec les :
  - Nintendo 3DS
  - Nintendo 3DS XL
  - Nintendo 2DS
  - New Nintendo 3DS
  - New Nintendo 3DS XL
  - New Nintendo 2DS XL

Il y a, à l'heure où j'écris ces lignes, 2 projets séparés : Le mode 2 Joueur sur même machine, ainsi qu'un mode solo.

# Ok mais c'est quoi le Projet Tutoré ?
C'est un projet obligatoire qui compte dans les études en DUT. Il y en a un par Semestre, donc c'est le projet du 4ème Semestre (2ème semestre de la seconde année).

# C'est fait comment ?
Le jeu est codé en C avec l'aide de la bibliothèque libre Devkitpro 3DS. Ce projet n'utilise donc pas les bibliothèques officielles Nintendo.

# Que contient les dossiers ?
Les dossiers sont organisés ainsi :
Un dossier "build" contenant les fichiers créés à la compilation
Un dossier "gfx" contenant les sprites (les fichiers .png) ainsi que la spritesheet (le fichier .t3s) référençant les sprites.
Un dossier "romfs" contenant un dossier "gfx" contenant un fichier .t3x qui est utilisé par l'exécutable. En gros, c'est le fichier .t3s compilé.
Un dossier "source" contenant le fichier source .c.
Un fichier "Makefile" qui sert pour compiler.
Un fichier .3dsx qui est l'exécutable (le jeu lui-même une fois compilé).
Un fichier .elf, une sorte d'éditeur de lien à ce que j'ai compris.
Un fichier .smdh, qui contient des infos concernant l'exécutable (l'auteur/dev, une description etc...).

# Ok c'est bien cool mais comment j'y joue ?
Pour ça il y a deux moyens.
Vous pouvez passer par l'émulateur N3DS Citra et vous chargez le fichier .3dsx.
Vous pouvez également passer par la vraie console, mais pour cela, il va falloir la cracker/hacker. Ce n'est pas bien compliqué, mais je ne détaillerai pas ici comment faire. Si vous avez une 3DS hackée, vous mettez les fichiers .smdh et.3dsx dans le dossier 3ds de votre carte SD, lancer le Homebrew Launcher et voilà.

# Super ! Mais... Est-ce illégal ?
Non. Hacker votre console et jouer à ce jeu n'est pas illégal. Ce n'est juste pas approuvé par Nintendo, et donc par conséquent, la garantie ne s'applique pas si vous avez un problème avec votre console hackée.

# Ouais mais du coup... C'est safe de jouer à ce jeu ?
Oui. C'est juste un jeu codé assez "aisément", et le code source est en libre accès. Donc si vous doutez, allez voir le code source, et si vous ne savez pas lire du C, demandez à quelqu'un pour le faire pour vous. Mais il n'y a aucun risques avec mon jeu puisque je l'ai testé.

# Puis-je modifier et republier le jeu si je veux l'améliorer ?
Oui. Le jeu, ainsi que le code source sont en libre accès, c'est pas pour rien.

# Y aura-t-il des mises à jour du jeu ?
C'est possible. Cela dépend du temps que j'ai à lui consacrer, mais j'ai de bonnes idées, et je vais voir petit à petit si je peux les implémenter.

# BREF BON JEU !
