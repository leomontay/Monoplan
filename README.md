JALON 4 : 

Création du tableur avec l'outil glade, "monopla.glade", qui définit la structure de l'interface graphique : une fenêtre contenant une grille vide où le code C ajoutera dynamiquement les cellules du tableur.

Ajout de la fonction ajouter_cellule, dans cellules.c et son en-tête dans le .h.

Création du dossier gui qui contient ce qui est nécessaire pour l'IHM.
    Dans gui.c, ajout des méthodes : - bind_create qui permet la création d'un bind
                                     - bindLookupByCell qui fait une recherche par modèle interne
                                     - bindLookupByPos qui fait une recherche par position dans la grille
                                     - on_cell_edited qui, Callback : quand l’utilisateur modifie une cellule
                                     - on_cell_focus_out qui évalue la formule de la cellule quand l'utilisateur clique ailleurs ou quitte la cellule
                                     - gui_init qui initialise l'IHM
                            
Création d'un main avec main.c qui initialise GTK, crée l'interface graphique, puis lance la boucle d'événements qui attend les interactions utilisateur.

Création du MakeFile pour lancer le projet donc le tableur.