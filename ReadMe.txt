Prérecis:
	- Un systeme de type Unix
	- Compilateur C
	- cmake
	- ncurses
	- SDL
	- SDL_TTF (avec les polices FreeMono et FreeSerifBoldItalic installées dans le repertoire /usr/share/fonts/truetype/freefont/)

Création de l'éxecutable:
	 entrez les commandes suivantes :
	 -cmake .
	 -make

Création de la documentation:
	- Utilisez la commande "make doc" à la racine du projet et après avoir fais un cmake .
	vous obtiendrai ainsi un "compteRenduFinale.pdf"

L'exécutable de jeu ainsi qu'un programme de test est créé dans un dossier bin à la racine du projet.
La bibliothèque grid est créée dans un dossier lib à la racine du projet.



Dans le jeu en mode console:
			-rentrez la direction du mouvement souhaité à l'aide des flèches multidirectionnelle du clavier.
			-Si le mouvement est impossible, aucun ne sera effectué.
			-Pour quitter le jeu en pleine partie, faites un CTRl-C.


Dans le jeu en mode console:
			-rentrez la direction du mouvement souhaité à l'aide des flèches multidirectionnelle du clavier. Ou en faisant glisser en maintenant le clic gauche enfoncé puis en relachant le bouton après afin d'effectuer un autre mouvement.
			-Si le mouvement est impossible, aucun ne sera effectué.
			-Pour quitter le jeu, utilisez la touche Echap ou la croix de la fenetre.
Stratégie:
	-Les 2 stratégies sont éxécutées sans mode graphique dans le programme grid-test
	-Vous pouvez choisir la stratégie que vous souhaitez éxecutés en mode graphique dans stratMain 