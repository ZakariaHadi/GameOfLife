#ifndef STRUCTURE_LIFEGAME_H_INCLUDED
#define STRUCTURE_LIFEGAME_H_INCLUDED

#include <cairo.h>
#include "struct_macro.h"

typedef struct
{
    int x;
    int y;
}pos;
typedef struct
{
    short int couleur;
    short int etat_suiv;
}cellule;
typedef struct
{
    GtkWidget *zone_dessinable; // notre zone qui contient le grid
    cellule grid[122][202];//tableau de deux dimentions contient les informations sur le grid
                // chaque case correspond a une cellule dans le grid
                // 'N' : la cellule est Noire
                // 'B' : la cellule est blanche
                // 'F' : elle contient la fourmi
    int case_taille; // la taille de chaque cellule
    int debut_ligne; //l indice du debut des lignes qu'on affiche dans le grid
    int fin_ligne; //l indice de fin des lignes qu'on affiche dans le grid
    int debut_coll;  //l indice du debut des colonnes qu'on affiche dans le grid
    int fin_coll;  // l indice de fin des colonnes qu'on affiche dans le grid

}Grid;


typedef struct fourmi_info
{
  pos pos_fourmi;  // la position de fourmi
  short int direction; // contient la direction de fourmi
                // 1: Haut  2: Droite  3: Bas  4: Gauche
  struct fourmi_info *suiv;
}fourmi_info;

typedef struct Liste_regles_position
{
    Box *vbox;
    GtkWidget *zone_dessinable_survive;//
    GtkWidget *zone_dessinable_relance;
    short int regle_pos_survive[9];
    short int regle_pos_relance[9];
    struct Liste_regles_position *suiv;

}Liste_regles_position;


typedef struct
{
    Grid grid_zone;
    Fenetre *ma_fenetre; //la fenetre du jeu
    Toolbar toolbar;//la barre des outils
    Statubare statu; // la barre du statuu
    Scale Echelle; // l'echelle de la vitesse
    int iter;    //  numero d'iteration
    int vitesse;  // la vitesse de la fourmi
    short int regle_standards[3];// pour indiquer les nombres des voisines pour personnaliser les regles
    int regle_position[256][2]; // contient les regles par position .
    short int ind_dern_regle;   // indice pour indiquer le nombre des regles choisies par position
    Liste_regles_position *Liste_regle;//liste des regles personnalisées .
    GdkRGBA colors[2];//les couleurs des cellules vivantes/mortes
    Fixed CONTAINER;// un container fixe pour positionner les petites images des regles.
    GtkWidget *dialog;//la fenetre qui contient les regles du jeu de la vie.
    guint a;//indicateur de la fct qui tourne le jeu.
    short int play; // indicateur si le jeu est demarré ou non (play or pause)
    int iteration_precise; // pour indiquer une iteration precise.
    fourmi_info *fourmis;
    short int nbr_fourmi;
    GdkRGBA fourmi_couleur;
}Lifegame;

/****************************************************************************************************/



//typedef struct
//{
//    fourmi_info *fourmis; /**structure qui contient les infos de la fourmi*/
//    short int nbr_fourmi;/** indique le nbr des fourmis dans le jeu*/
//    Grid grid_zone; /**la structure de la grille*/
//    Fenetre *ma_fenetre; /**la fenetre du jeu*/
//    Toolbar toolbar;/**la barre des outils*/
//    Statubare statu;/** la barre du statuu*/
//    Scale Echelle; /**l'echelle de la vitesse*/
//    int iter;    /** numero d'iteration*/
//    int vitesse;  /** la vitesse de la fourmi*/
//    GdkRGBA fourmi_couleur; /** la couleur de la fourmi */
//    guint a;   /** indicateur de la fct qui tourne le jeu.*/
//    short int fourmi_test,play; /** indicateur si le jeu est demarré ou non (play or pause)*/
//    int iteration_precise; /** pour indiquer une iteration precise.*/
//}IlisiFourmi;
#endif // STRUCTURE_LIFEGAME_H_INCLUDED
