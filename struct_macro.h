#ifndef STRUCT_MACRO_H_INCLUDED
#define STRUCT_MACRO_H_INCLUDED
#include <gtk/gtk.h>
#include <math.h>


/*********              LES STRUCTURES DE DONNEES       *****************/



/* la structure de position */
typedef struct
{
    int x;//position sur l'abscisse
    int y;//position sur l'ordonnée
} coordonnes;
/* taille  */
typedef struct
{
    int hauteur;//hauteur
    int largeur;//largeur
} Taille;

/*********************  STRUCTURE FENETRE ************************/
typedef struct fenetre
{
    GtkWidget *fenetre;//identifiant de la fenetre
    GtkWidget *fBox;//Le BOX Horizontal ou Vertcal
    GtkImage *fImg;//si la fenetre contient une image
    int fenetrePosDebut;//centre ou position de sourie etc...
    int ftype;// 0 toplevel 1 popup
    gchar icone[50];//chemin de l'icone
    char fTitre[10];//titre de la fenetre
    coordonnes fPos;//position de la fenetre
    GdkColor couleur;//couleur
    Taille fTaille;//taille
    int fBarredefilement;//si la fenetre contient un "scroll bar"
    int fConteneur;
    gboolean resizable;//0 ou 1
    gdouble opacity;//
} Fenetre;


/*********************  STRUCTURE D UNE Image   ********************************/
typedef struct img
{
    GtkWidget *Image;//widget image
    char *chemin;//chemin de l'image
    coordonnes iPos;//position de l'image
    int itype; // CH_IMG ou Q_IMG
} Image;



/************************ STRUCTURE CADRE *******************************/

typedef struct cadre
{
    GtkWidget *Cadre;     //widget du cadre
    GtkWidget *cContent;  //conteneur du cadre
    char cLabel[50];      //label du cadre
    int cStyle;           //style cadre, l'ombre etc..
    float cPoslabelX;     //position horizontale label cadre
    float cPoslabelY;     //position verticale label cadre
    GdkColor cCouleur;    //couleur du cadre
    Taille cTaille;       //taille du cadre
    coordonnes cPos;        //position du cadre

} Cadre;



/************************ STRUCTURE D UN BOUTTON *******************************/
typedef struct bouton
{
    GtkWidget* Bouton;// le bouton
    int bRelief;//0 normal , 1 moitie
    gchar bIcone[50];// choisi du stock
    int bType ;// label,mnemonic,image,ou bien "from stock"
    char bLabel[50];//label du bouton
    Image bImg;//image
    GdkColor bColor;//couleur
    int couleur;//coulleur
    Taille bTaille;//taille
} Bouton;



/************************** COMBO BOX  **********************************/
typedef struct cmbbox
{
   GtkWidget *ComboBox;//widget de la combobox
   coordonnes cbPos;//position
}ComboBox;


/**************************** BOUTONS RADIO *****************************/
typedef struct rad
{
    GtkWidget *Boutonradio;//widget du bouton radio
    GtkWidget *radioGrp;
    GtkWidget *vbox;
} BoutonRadio;

/*une liste des boutons Radio*/
typedef struct lb
{
    BoutonRadio *btn;
    struct lb *svt;
}Rliste;


/**************************   CHECK BOX *********************************/
typedef struct check
{
    GtkWidget* Check; //widget de la check box
    GtkWidget *v_box;
    coordonnes cPos;      //position du checkbox
    char cLabel[50];       //lable du checkbox
}CheckBox;

/************* STRUCTURE BOUTON SPIN *************/
typedef struct spin
{
    GtkWidget *Spin;//widget du boutton spin
    gdouble sMin;//la valeur Min
    gdouble sMax;//la valeur Max
    gdouble sPas;//pas de chaque clique
    coordonnes sPos;//la position du boutton
    Taille sTaille;//la taille
} BoutonSpin;

/*********************** STRUCTURE TABLE *************************/

typedef struct table
{
  GtkWidget *table;     //widget de la table
  int nbLignes;         //nombre de lignes de la table
  int nbColonnes;       //nombre de colonnes de la table
  int homogene;         //1 elem occupent le même espace, 0 si non
  coordonnes posTable;         //position de la table
}Table;

/*********************** STRUCTURE de barre d'outils *************************/
typedef struct
{
    GtkWidget   *toolbar;
    GtkToolItem *toolitem;
    GtkToolItem *separator;
}Toolbar;

/*********************** STRUCTURE de barre du statut *************************/
typedef struct
{
    GtkWidget   *statubare;
    char iter[7];
}Statubare;


/************************ Structures de la barre du menu ****************/

typedef struct menuItem
{
    GtkWidget *menuItem;
    char label[50];//label du menu
    int type;//
    int separateur;//si le menu item est suivi par un séparateur
    struct menuItem *sous_menu;//liste sous menu lié à un menu item
    struct menuItem *suivant; // pointeur vers le suivant

} MenuItem;

typedef struct menu
{
    char label[50];
    int tearOff;//si le menu est détachable
    MenuItem *listeMenuItem;//liste des menu items
    struct menu *suivant;

} Menu;
typedef struct menuBar
{
    GtkWidget *menuBar;//barre de menu
    Menu *listeMenu;//liste des menus
    coordonnes p;
    Taille t;
} MenuBar;


/************* STRUCTURE D UNE BOITE ***********************/
typedef struct box
{
    GtkWidget *Box;       //widget de la box
    int bType;            //horizontal box ou bien vertical box
    int bHomogene;        //si tout les widget occupe le même espace
    int bSpacing;         //espacement entre les widgets contenu dans la boite
    Taille bTaille;       //taille
    coordonnes bPos;        //position
}Box;

/************* STRUCTURE DE  ***********************/
typedef struct scroll_window
{
    GtkWidget *sw;// Id widgets
    int sideBar;  // Bar du coté
    int bottomBar; // Bar du bas
}ScrollBar;
/************* STRUCTURE D UNE notebook ***********************/
typedef struct Bloc_note
{
    GtkWidget *bloc_note;
    int pos_onglet;//en haut ou en bas
    int nbr_page;
    char **titre_page; //tableau des titre de chaque page du bloc_note, on fait l'allocation apres savoir le nombre de page.

}Bloc_note;

/************* STRUCTURE D UNE ZONE DE SAISIR D'UN TEXTE ***********************/
typedef struct text_view
{
  GtkWidget *texte;
  Taille taiile_texte;
}text_view;
/*********************** STRUCTURE ZONE DE SAISI ************************/
typedef struct zonesaisir
{
    GtkWidget* zone;    //widget de la zone de saisi
    coordonnes zPos;    //la position
    int zMaxlenght;     //la longueur maximale du texte à saisir dans la zone
    Taille zTaille;     //taille
    char* zText;        //texte présent initialement
    int zCursorposition;//position du curseur
    int zVisible;       // 0 si oui 1 non
    int zAlign;         //0 en cas de gauche et 1 cas de droite
    char zTremp;
} zoneSaisi;

/************************STRUCTURE DE SCALE**************************/
typedef struct
{
    GtkWidget *scale;
    int val_min;
    int val_max;
    int pas;
}Scale;
/*************************STRUCTURE LABEL***************************/
/* style ou formatage du text */
typedef struct style_texte
{
    char Police[40];   //pour definir la police utilsee
    char Size[4];      /*pour definir la taille du text*/
    char Style[20];    /*pour definir le style du text*/
    char Weight[20];   /*pour definir l'epaisseur du text*/
    char Color[10];    /*pour definir la couleur du text*/
    char fColor[10];    /*pour definir la couleur du fond*/
    char Underline[10];/*pour le soulignement du text*/
    char Barer[10];    /*pour barrer le text*/
}style_texte;

typedef struct label
{
    GtkWidget* label;      //widget du label
    char lTexte[50];       //texte du label
    int lJustify;          //1 LEFT 2 RIGHT 3 CENTER
    coordonnes lPos;       //position
    style_texte lFormat;   //format du texte
    int lStyle;            // utiliser un format ou pas
    gboolean selectionnable; // selectionnable ou non
    gdouble rotation;
}Label;

/*************************STRUCTURE SEPARATEUR***************************/
typedef struct sep
{
   GtkWidget *Separateur;//widget du séparateur
   int type;// 0 : séparateur horizontal ; 1 : séparateur verticale
   Taille sTaille;  /*taille du séparateur: pour horizontal spécifier que
                    le parametre "largeur" , Hauteur pour le vertical*/
   coordonnes sPosition;//position du séparateur
}Separateur;

/*********************STRUCTURE D'UN CONTAINER FIX*******************/
typedef struct fix
{
   GtkWidget *fixed;
   coordonnes pos;//position du dernier element dans le container

}Fixed;

/********************* STRUCTURE D 'UNE ZONE DESSINABLE "drawable_zone" **********************************/

typedef struct drawzone
{
    GtkWidget *dzone; // le widget de la zone
    cairo_t *cr;      // le pointeur du peindre
    GdkRGBA couleur;  //la couleur du peindre
    coordonnes dpos;  // la position de la zone dessinable
    Taille dtaille;   // la taille de la zone dessinable
} drawzone;

typedef struct _Menu Le_Menu;
struct _Menu
{
    GtkWidget  *Menu_bar, *Menu_champ, *sous_menu;
};
/************************* Les Enumeration ***************************************/
//enumeration d'une Fenetre
//enum {GTK_WINDOW_TOPLEVEL,GTK_WINDOW_POPUP};// type
//enum {GTK_WIN_POS_NONE,GTK_WIN_POS_CENTER,GTK_WIN_POS_MOUSE,GTK_WIN_POS_CENTER_ALWAYS,GTK_WIN_POS_CENTER_ON_PARENT};//position initiale
enum {VERTICAL,HORIZONTAL};//BOX type

//enumeration d'un Bouton
enum {BIMAGE,BADD,BDELETE,BOPEN,BCLOSE,
      BABOUT,BFILECH, BCOLOR,BFONTCH,
     };// type
enum {BR_NORMAL, BR_NONE=2};// type de relief

////enumeration Cadre
enum {C_SHADOW_IN,C_SHADOW_OUT,C_SHADOW_ETCHED_IN,C_SHADOW_ETCHED_IN_OUT};
//
//
enum {LEFT,CENTER,RIGHT};//justify du label
////enum scale
enum {S_LEFT,S_RIGHT,S_TOP,S_BOTTOM};
//
enum {BMP_COLUMN,TEXT_COLUMN,N_COLUMN};

#endif // STRUCT_MACRO_H_INCLUDED
