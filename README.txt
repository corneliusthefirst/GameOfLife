NOTE sur le mouse click:

Je traite une clique comme un evenement EVT_LEFT_UP (le left click est laché). Donc, la clique dépende de la position où
le souris est laché, pas sur la position où le souris est cliqué

Je le fait comme ca car wxWidgets n'a pas un evenement clique donc il faut recreer l'evenement et son handler, et je ne suis pas arrivé à le faire.

-------------------------------------------------------
DES FICHIERS + COMPILATION

Paquetage grille: l'implementation de la grille du jeu
Paquetage jeu: l'implementation du jeu avec la méthode Avance()
Paquetage fenetre: l'implementation de l'interface. Comme la méthode RenderLoopOn et RenderLoopOff demande que l'application doit être déjà définie, j'ai mis la déclaration de l'application
dans fenetre.h aussi. Alors, il n'y a pas le fichier app.h
app.cpp: la définition de l'application et des fonctions pour la boucle render

Pour compiler, la commande make est suffisante. Pour tester, simplement lancer l'exe jeu_de_la_vie
Pour ajouter/supprimer une cellule, c'est suffit de cliquer sur la carree.
Le menu SELECT est pour dessiner des configs dans la question 4
