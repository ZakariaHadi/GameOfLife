#include "macro_lifegame.h"
#include "Macro.h"
#include "fcts_regles_position.h"
#include "initialisation_fenetre.h"

int main(int argc, char** argv)
{

        initialiser_interface(argc,argv);

        Lifegame Jeu;
        Jeu.fourmis=NULL;
        Jeu.nbr_fourmi=0;
        Jeu.play=0;
        Jeu.iteration_precise=0;
        Jeu.iter=0;
        Jeu.vitesse=500;
        Jeu.regle_standards[0]=1;
        Jeu.regle_standards[1]=2;
        Jeu.regle_standards[2]=3;
        init_interface(&Jeu);
        gtk_main();
        return 0;
}
