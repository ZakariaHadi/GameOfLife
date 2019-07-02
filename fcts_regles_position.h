#ifndef FCTS_REGLES_POSITION_H_INCLUDED
#define FCTS_REGLES_POSITION_H_INCLUDED

#include "structure_lifegame.h"
#include "struct_macro.h"
#include "macro_lifegame.h"
#include "Macro.h"

int calc_binary(short int tab[9]);
Liste_regles_position *nv_case_regles()
{
    int ind;
    Taille taille;
    taille.hauteur=20;
    taille.largeur=20;
    Liste_regles_position *nv=(Liste_regles_position*)malloc(sizeof(Liste_regles_position));
    nv->vbox=creer_box(HORIZONTAL);
    nv->suiv=NULL;
    for(ind=0;ind<9;ind++)
        nv->regle_pos_relance[ind]=nv->regle_pos_survive[ind]=0;

    nv->zone_dessinable_relance=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_DRAWING_AREA(nv->zone_dessinable_relance),60,60);
    nv->zone_dessinable_survive=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_DRAWING_AREA(nv->zone_dessinable_survive),60,60);

    return ( (Liste_regles_position *) nv);
}

static gboolean event_regle_survive(GtkWidget *widget,cairo_t *cr,Liste_regles_position *zone)
{
    int ind=0,ind1=0;
    float couleur;
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_rectangle(cr, 0, 0,60,60);
    cairo_fill(cr);
    for(ind1=0;ind1<9;ind1++)
        {  if(ind1==4) couleur=0.7;
           else couleur= 1-zone->regle_pos_survive[ind1];
           cairo_set_source_rgb(cr,couleur,couleur,couleur);
           if(ind1==3 || ind1==6 ) ind=0;
           cairo_rectangle(cr, ind*20,(ind1/3)*20,19,19);
           cairo_fill(cr);
           ind++;
        }
}
static gboolean event_regle_relance(GtkWidget *widget,cairo_t *cr,
                                    Liste_regles_position *zone)
{
    int ind=0,ind1=0;
    float couleur;
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_rectangle(cr, 0, 0,60,60);
    cairo_fill(cr);
    for(ind1=0;ind1<9;ind1++)
        {  if(ind1==4) couleur=0.7;
           else couleur= 1-zone->regle_pos_relance[ind1];
           cairo_set_source_rgb(cr,couleur,couleur,couleur);
           if(ind1==3 || ind1==6 ) ind=0;
           cairo_rectangle(cr, ind*20,(ind1/3)*20,19,19);
           cairo_fill(cr);
           ind++;
        }
}

static gboolean sourie_clicked_regle_survive(GtkWidget *widget, GdkEventButton *event,
                               Liste_regles_position *zone)
{
   int x,y,a;
    if (event->button == 1) //si le boutton cliqué est le boutton gauch de sourie
    {
        x=(int)event->x;
        y=(int)event->y;
        a=((y/20)*3)+(x/20);
        if(!zone->regle_pos_survive[a])
           zone->regle_pos_survive[a]=1;
        else zone->regle_pos_survive[a]=0;
       gtk_widget_queue_draw(widget);
    }
    return TRUE;
}
static gboolean sourie_clicked_regle_relance(GtkWidget *widget, GdkEventButton *event,
                               Liste_regles_position *zone)
{
   int x,y,a;
    if (event->button == 1) //si le boutton cliqué est le boutton gauch de sourie
    {
        x=(int)event->x;
        y=(int)event->y;
        a=((y/20)*3)+(x/20);
        if(!zone->regle_pos_relance[a])
           zone->regle_pos_relance[a]=1;
        else zone->regle_pos_relance[a]=0;
       gtk_widget_queue_draw(widget);
    }
    return TRUE;
}


void ajouter_regle(GtkWidget *widget,Lifegame *Jeu)
{
     Liste_regles_position *crt=nv_case_regles(),*crt1;
     Jeu->CONTAINER.pos.y+=80;
     ajouter_element_box(crt->vbox->Box,crt->zone_dessinable_relance,1,0,0,0);
     ajouter_element_box(crt->vbox->Box,crt->zone_dessinable_survive,1,0,0,30);
     g_signal_connect(G_OBJECT(crt->zone_dessinable_relance),"draw",
                       G_CALLBACK(event_regle_relance),crt);
     g_signal_connect(G_OBJECT(crt->zone_dessinable_survive),"draw",
                       G_CALLBACK(event_regle_survive),crt);
     gtk_widget_add_events(crt->zone_dessinable_relance, GDK_BUTTON_PRESS_MASK);
     gtk_widget_add_events(crt->zone_dessinable_survive, GDK_BUTTON_PRESS_MASK);

     g_signal_connect(crt->zone_dessinable_relance, "button-press-event",
                     G_CALLBACK(sourie_clicked_regle_relance),crt);
     g_signal_connect(crt->zone_dessinable_survive, "button-press-event",
                     G_CALLBACK(sourie_clicked_regle_survive), crt);

     if( !Jeu->Liste_regle )
           Jeu->Liste_regle=crt;
    else
    {
        crt1=Jeu->Liste_regle;
        while(crt1->suiv) crt1=crt1->suiv;
        crt1->suiv=crt;
    }
    gtk_fixed_put(Jeu->CONTAINER.fixed,crt->vbox->Box,Jeu->CONTAINER.pos.x,Jeu->CONTAINER.pos.y);
    afficher_tout(Jeu->dialog);
    return;
}

void recuperer_cases_regles(Liste_regles_position *nv,Lifegame *Jeu)
{
    Jeu->CONTAINER.pos.y+=80;
    nv->vbox=creer_box(HORIZONTAL);
    nv->zone_dessinable_relance=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_DRAWING_AREA(nv->zone_dessinable_relance),60,60);
    nv->zone_dessinable_survive=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_DRAWING_AREA(nv->zone_dessinable_survive),60,60);
    ajouter_element_box(nv->vbox->Box,nv->zone_dessinable_relance,1,0,0,0);
     ajouter_element_box(nv->vbox->Box,nv->zone_dessinable_survive,1,0,0,30);
     g_signal_connect(G_OBJECT(nv->zone_dessinable_relance),"draw",
                       G_CALLBACK(event_regle_relance),nv);
     g_signal_connect(G_OBJECT(nv->zone_dessinable_survive),"draw",
                       G_CALLBACK(event_regle_survive),nv);
     gtk_widget_add_events(nv->zone_dessinable_relance, GDK_BUTTON_PRESS_MASK);
     gtk_widget_add_events(nv->zone_dessinable_survive, GDK_BUTTON_PRESS_MASK);

     g_signal_connect(nv->zone_dessinable_relance, "button-press-event",
                     G_CALLBACK(sourie_clicked_regle_relance),nv);
     g_signal_connect(nv->zone_dessinable_survive, "button-press-event",
                     G_CALLBACK(sourie_clicked_regle_survive), nv);
    gtk_fixed_put(Jeu->CONTAINER.fixed,nv->vbox->Box,Jeu->CONTAINER.pos.x,Jeu->CONTAINER.pos.y);
    return;
}


void modifier_regle(GtkWidget *widget,Lifegame *Jeu)
{
    if(Jeu->play)pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,4),Jeu);
    BoutonSpin *spin_regle[2];
    Taille taille;
    GtkWidget *content_area,*label;
    ScrollBar *S=init_scrolled_window();
    creer_scrollBar(S);
              Jeu->dialog=gtk_dialog_new_with_buttons("Modifier Les Regles",NULL,GTK_DIALOG_MODAL,
                                                  GTK_STOCK_APPLY,GTK_RESPONSE_APPLY,
                                                  GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                                  NULL);
    gtk_widget_set_size_request(Jeu->dialog,320,600);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (Jeu->dialog));
    Jeu->CONTAINER.fixed=gtk_fixed_new();

    //*******************RADIO BOUTTON**************
    BoutonRadio radio;
    radio.vbox=gtk_vbox_new(1,1);
    creer_bouton_radio(NULL,&radio,"Regles Standards");
    g_signal_connect(radio.radioGrp,"clicked",G_CALLBACK(radio_clicked),spin_regle);
    creer_bouton_radio(&radio,&radio,"Regles Personnalisees");
    g_signal_connect(radio.Boutonradio,"clicked",G_CALLBACK(radio_clicked),spin_regle);
    gtk_fixed_put(Jeu->CONTAINER.fixed,radio.radioGrp,10,10);
    gtk_fixed_put(Jeu->CONTAINER.fixed,radio.Boutonradio,10,240);

    Jeu->CONTAINER.pos.x=10;
    Jeu->CONTAINER.pos.y=270;

    /************************************************************/

     Image *image1=initialiser_image();
     image1->chemin=".\\images\\vive.png";
     creer_image(image1);
     gtk_fixed_put(Jeu->CONTAINER.fixed,image1->Image,10,65);

    spin_regle[0]=creer_bouton_spin(8,0,1);
    gtk_spin_button_set_value(spin_regle[0]->Spin,Jeu->regle_standards[2]);
    gtk_widget_set_tooltip_text (spin_regle[0]->Spin, "valeur par default: 3");
    gtk_fixed_put(Jeu->CONTAINER.fixed,spin_regle[0]->Spin,170,90);

    label=gtk_label_new("le nbr des voisines vivante\npour qu'une cellule relance");
    gtk_fixed_put(Jeu->CONTAINER.fixed,label,140,55);

     Image *image2=initialiser_image();
     image1->chemin=".\\images\\survive.png";
     creer_image(image1);
     gtk_fixed_put(Jeu->CONTAINER.fixed,image1->Image,10,140);

     label=gtk_label_new("le nbr des voisines vivante\n     pour qu'une cellule \n\treste a son etat");
     gtk_fixed_put(Jeu->CONTAINER.fixed,label,140,130);

     spin_regle[1]=creer_bouton_spin(8,0,1);
     gtk_spin_button_set_value(spin_regle[1]->Spin,Jeu->regle_standards[1]);
      gtk_widget_set_tooltip_text (spin_regle[1]->Spin, "valeur par default: 2");
    gtk_fixed_put(Jeu->CONTAINER.fixed,spin_regle[1]->Spin,170,180);

    Bouton *boutton_regle;
    taille.hauteur=10;
    taille.largeur=40;
    boutton_regle=creer_texte_boutton(taille,"Ajouter Nv regle",0);
    g_signal_connect(boutton_regle->Bouton,"clicked",G_CALLBACK(ajouter_regle),Jeu);
    gtk_fixed_put(Jeu->CONTAINER.fixed,boutton_regle->Bouton,10,280);

    label=gtk_label_new("Cel vive");
    gtk_fixed_put(Jeu->CONTAINER.fixed,label,20,330);
    label=gtk_label_new("Cel survive");
    gtk_fixed_put(Jeu->CONTAINER.fixed,label,100,330);


    if(Jeu->Liste_regle)
    {
        gtk_toggle_button_set_active(radio.Boutonradio,TRUE);
        Liste_regles_position *crt=Jeu->Liste_regle;
        while(crt)
            { recuperer_cases_regles(crt,Jeu);crt=crt->suiv;}
    }

    gtk_window_set_position(GTK_DIALOG(Jeu->dialog),GTK_WIN_POS_CENTER);

    associer_element_scroll(S,Jeu->CONTAINER.fixed);
    gtk_container_add(GTK_CONTAINER(content_area),S->sw);
    afficher_tout(Jeu->dialog);

    gint a=gtk_dialog_run(Jeu->dialog),countt=-1;

    if(a==GTK_RESPONSE_APPLY)
    {
        if(gtk_toggle_button_get_active(radio.radioGrp))
             {  Jeu->regle_standards[0]=1;
                Jeu->regle_standards[1]=gtk_spin_button_get_value_as_int(spin_regle[1]->Spin);
                Jeu->regle_standards[2]=gtk_spin_button_get_value_as_int(spin_regle[0]->Spin);
             }
        else
            {   Jeu->regle_standards[0]=0;
                Liste_regles_position *crt=Jeu->Liste_regle;
                while(crt)
                    {
                       Jeu->regle_position[++countt][0]=calc_binary(crt->regle_pos_survive);
                       Jeu->regle_position[countt][1]=calc_binary(crt->regle_pos_relance);
                       crt=crt->suiv;
                    }
                    Jeu->ind_dern_regle=countt;
             }

    }
    gtk_widget_destroy(Jeu->dialog);
}

int calc_binary(short int tab[9])
{
    int res=0,ind;
    for(ind=8;ind>=0;ind--)
    {
        if(ind==4) continue;
        res+=tab[ind]*pow(2,8-ind);
    }
    return res;
}
#endif // FCTS_REGLES_POSITION_H_INCLUDED
