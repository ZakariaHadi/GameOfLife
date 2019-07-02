#ifndef INITIALISATION_FENETRE_H_INCLUDED
#define INITIALISATION_FENETRE_H_INCLUDED

#include "structure_lifegame.h"
#include "struct_macro.h"
#include "macro_lifegame.h"
#include "Macro.h"
#include "fcts_regles_position.h"


void QUITTER(GtkWidget *widget,gpointer data)
{
    gtk_widget_destroy(widget);
    system(".\\bin\\Debug\\menu.exe");
}

void init_interface(Lifegame *Jeu)
{

          initialiser_grid_dessinable(Jeu,30,50,20);
          Taille taille;
          taille.hauteur=600;
          taille.largeur=1000;

          Jeu->ma_fenetre=Creer_fenetre("JeuDeVie",taille,0);

          Box *Hboite=creer_box(HORIZONTAL),*Vboite=creer_box(VERTICAL),*Vboite1=creer_box(VERTICAL);
          //*****************LE MENU***********
          Le_Menu menuu;
          creer_Menu(&menuu,Jeu);
          /*************barre d outils*************/
           creer_toolbar((Lifegame*)Jeu);

          /*********** Statu barre *********/

           Jeu->statu.statubare=gtk_statusbar_new ();
           int id = gtk_statusbar_get_context_id (GTK_STATUSBAR(Jeu->statu.statubare), "iteration");
           //gtk_statusbar_pop (GTK_STATUSBAR(Jeu->statu.statubare), id);
           gtk_statusbar_push (GTK_STATUSBAR(Jeu->statu.statubare), id, "iteration : 0");

         /********scrolled bar (les informations de jeu)************/
         ScrollBar *S=init_scrolled_window();
         creer_scrollBar(S);


         creer_echelle(Jeu,1,1000,10,500);
         ajouter_element_box(Vboite1->Box,Jeu->Echelle.scale,1,0,0,75);


         zoneSaisi *nvzone=initialiser_entry();
         creer_entry(nvzone);
         g_signal_connect(nvzone->zone,"activate",G_CALLBACK(aller_iteration),Jeu);
         ajouter_element_box(Vboite1->Box,nvzone->zone,1,0,0,0);

        /*********definition des couleurs initiales*************/
         Jeu->colors[0].green=0;
         Jeu->colors[0].red=0;
         Jeu->colors[0].blue=0;
         Jeu->colors[1].green=1;
         Jeu->colors[1].red=1;
         Jeu->colors[1].blue=1;
         Jeu->fourmi_couleur.blue=1;
         Jeu->fourmi_couleur.red=0;
         Jeu->fourmi_couleur.green=0;
         GtkWidget *couleur_boutton=gtk_color_button_new_with_rgba(&Jeu->colors[0]);
         gtk_widget_set_size_request(couleur_boutton,100,20);
         g_signal_connect(couleur_boutton,"color-set",G_CALLBACK(couleur_cellule_vivante),Jeu);
         ajouter_element_box(Vboite1->Box,couleur_boutton,1,0,0,75);

         GtkWidget *couleur_boutton1=gtk_color_button_new_with_rgba(&Jeu->colors[1]);
         gtk_widget_set_size_request(couleur_boutton1,100,20);
         g_signal_connect(couleur_boutton1,"color-set",G_CALLBACK(couleur_cellule_morte),Jeu);
         ajouter_element_box(Vboite1->Box,couleur_boutton1,1,0,0,0);

         GtkWidget *couleur_boutton2=gtk_color_button_new_with_rgba(&Jeu->fourmi_couleur);
         gtk_widget_set_size_request(couleur_boutton2,100,20);
         g_signal_connect(couleur_boutton2,"color-set",G_CALLBACK(couleur_fourmi),Jeu);
         ajouter_element_box(Vboite1->Box,couleur_boutton2,1,0,0,20);

        taille.hauteur=20;
        taille.largeur=50;

        Bouton *boutton_regle=creer_texte_boutton(taille,"_Modifier les Regles",1);
        g_signal_connect(boutton_regle->Bouton,"clicked",G_CALLBACK(modifier_regle),Jeu);
        Jeu->Liste_regle=NULL;
        ajouter_element_box(Vboite1->Box,boutton_regle->Bouton,1,0,0,45);

        Bouton *bouton_placer_fourmi=creer_texte_boutton(taille,"_Placer fourmi",1);
        g_signal_connect(bouton_placer_fourmi->Bouton,"clicked",G_CALLBACK(Placer_fourmi),Jeu);
        ajouter_element_box(Vboite1->Box,bouton_placer_fourmi->Bouton,1,0,0,20);

         GtkWidget *Fixed=gtk_fixed_new();
         //****************L'IMAGE***********
         Image *image=initialiser_image();
         image->chemin=".\\images\\image2.jpg";
         creer_image(image);

         gtk_fixed_put(Fixed,image->Image,5,0);
         gtk_fixed_put(Fixed,Vboite1->Box,5,11);

         associer_element_scroll(S,Fixed);

          ajouter_element_box(Vboite->Box,Jeu->toolbar.toolbar,1,1,1,0);
          ajouter_element_box(Vboite->Box,Jeu->grid_zone.zone_dessinable,1,1,1,0);
          ajouter_element_box(Vboite->Box,Jeu->statu.statubare,1,1,1,0);

          ajouter_element_box(Hboite->Box,S->sw,1,1,1,0);
          ajouter_element_box(Hboite->Box,Vboite->Box,1,1,1,0);
          ajouter_element_box(Jeu->ma_fenetre->fBox,Hboite->Box,1,1,1,0);

          gtk_container_add(GTK_CONTAINER(Jeu->ma_fenetre->fenetre),Jeu->ma_fenetre->fBox);
          gtk_widget_add_events(Jeu->grid_zone.zone_dessinable, GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK);

          g_signal_connect(G_OBJECT(Jeu->grid_zone.zone_dessinable), "draw",
                     G_CALLBACK(on_draw_event),Jeu);
          g_signal_connect(Jeu->grid_zone.zone_dessinable, "button-press-event",
                     G_CALLBACK(sourie_clicked), &Jeu->grid_zone);
          g_signal_connect(Jeu->ma_fenetre->fenetre, "delete-event",
                     G_CALLBACK(QUITTER), NULL);
                     gtk_widget_show_all(Jeu->ma_fenetre->fenetre);

}

#endif // INITIALISATION_FENETRE_H_INCLUDED
