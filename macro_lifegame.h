#ifndef MACRO_LIFEGAME_H_INCLUDED
#define MACRO_LIFEGAME_H_INCLUDED


#include "structure_lifegame.h"




void initialiser_grid_dessinable(Lifegame *Jeu,int lignes, int collones , int case_taille)
{
    for(int ind=0;ind<122;ind++)
        for(int jnd=0;jnd<202;jnd++) {Jeu->grid_zone.grid[ind][jnd].couleur=0;//les cellules sont toutes blanches au premiers temps
Jeu->grid_zone.grid[ind][jnd].etat_suiv=0;}
    //creation de la zone dessinable du grid
            Jeu->grid_zone.zone_dessinable=gtk_drawing_area_new();
            gtk_widget_set_size_request(GTK_DRAWING_AREA(Jeu->grid_zone.zone_dessinable), collones*case_taille, lignes*case_taille);

            Jeu->grid_zone.debut_coll=75;//l indice correspond au collone du debut de notre grid
            Jeu->grid_zone.fin_coll=125; // l'indice correspond au collone fin de notre grid dessinable
            Jeu->grid_zone.debut_ligne=45; // l indice correspond au ligne du debut
            Jeu->grid_zone.fin_ligne=75;   // l indice correspond au ligne du fin
            Jeu->grid_zone.case_taille=case_taille; // la taille de chaque case du grid
            return ;
}

static gboolean on_draw_event(GtkWidget *widget,cairo_t *cr,Lifegame *Jeu)
{
     dessiner_grid(&Jeu->grid_zone,cr,Jeu);
    return FALSE;

}

void dessiner_grid(Grid *zone,cairo_t *cr,Lifegame *Jeu)
{

    int ind1=0,ind2=0;
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0,1000,600);
    cairo_fill(cr);
    for(int i=zone->debut_ligne; i<zone->fin_ligne+1;i++)
    { ind1=0;
        for(int j=zone->debut_coll;j<zone->fin_coll+1;j++)
        {
            if(zone->grid[i][j].couleur)
            cairo_set_source_rgb(cr, Jeu->colors[0].red,
                                 Jeu->colors[0].green, Jeu->colors[0].blue
                                );
            else cairo_set_source_rgb(cr, Jeu->colors[1].red,
                                 Jeu->colors[1].green, Jeu->colors[1].blue
                                );

            cairo_rectangle(cr, ind1*zone->case_taille+ 1, ind2*zone->case_taille+ 1, zone->case_taille-1, zone->case_taille-1);
            cairo_fill(cr);
            ind1++;
         }
         ind2++;
    }
    if(Jeu->nbr_fourmi)
    {
    /*********dessiner la/les fourmi**********/
    cairo_set_source_rgb(cr, Jeu->fourmi_couleur.red, Jeu->fourmi_couleur.green, Jeu->fourmi_couleur.blue);

    fourmi_info *crt=Jeu->fourmis;
    while(crt)
    {
    cairo_rectangle(
                    cr, ((crt->pos_fourmi.x - zone->debut_coll) * zone->case_taille)+1,
                        ((crt->pos_fourmi.y-zone->debut_ligne) * zone->case_taille) +1,
                        zone->case_taille-1, zone->case_taille-1
                   );
    cairo_fill(cr);
    crt=crt->suiv;
    }
    free(crt);
    }

}
void couleur_cellule_vivante(GtkWidget *b,Lifegame *Jeu)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(b),&Jeu->colors[0]);
    printf("\n\nheeeere your color : %f %f %f",Jeu->colors[0].green,Jeu->colors[0].red,Jeu->colors[0].blue);
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}

void couleur_cellule_morte(GtkWidget *b,Lifegame *Jeu)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(b),&Jeu->colors[1]);
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}

static gboolean sourie_clicked(GtkWidget *widget, GdkEventButton *event,
                               Grid *zone)
{
   int x,y,a,b;
    if (event->button == 1) //si le boutton cliqué est le boutton gauch de sourie
    {
        x=(int)event->x;
        y=(int)event->y;
        a= zone->debut_ligne + y/zone->case_taille;
        b= zone->debut_coll +  x/zone->case_taille;
        if(!zone->grid[a][b].couleur)
        zone->grid[a][b].couleur=1;
        else zone->grid[a][b].couleur=0;
       gtk_widget_queue_draw(widget);
    }
    return TRUE;
}


void zoomer_grid(Grid *zone)
{
    if(zone->case_taille==5) return;
    zone->case_taille=zone->case_taille-5;
    if(zone->case_taille==5)
    {
        zone->debut_coll=zone->debut_ligne=1;
        zone->fin_coll=200;
        zone->fin_ligne=120;
        return;
    }
    int nv_nbr_case;
    /********pour les colonnes**********/
    nv_nbr_case=1000/zone->case_taille;
    zone->debut_coll=(200-nv_nbr_case)/2;
    zone->fin_coll=200-zone->debut_coll;

    /*******pour les lignes**********/
    nv_nbr_case=600/zone->case_taille;
    zone->debut_ligne=(120-nv_nbr_case)/2;
    zone->fin_ligne=120-zone->debut_ligne;
    return ;
}

static gboolean commencer_jeu(Lifegame *Jeu)
{
  if(Jeu->regle_standards[0])
    { int somme=0;
    for(int Y=Jeu->grid_zone.debut_ligne;Y<Jeu->grid_zone.fin_ligne;Y++)
    {
        for(int X=Jeu->grid_zone.debut_coll;X<Jeu->grid_zone.fin_coll;X++)
        {

                somme=  Jeu->grid_zone.grid[Y-1][X-1].couleur + Jeu->grid_zone.grid[Y-1][X].couleur+ Jeu->grid_zone.grid[Y-1][X+1].couleur
                      + Jeu->grid_zone.grid[Y][X-1].couleur + Jeu->grid_zone.grid[Y][X+1].couleur
                      + Jeu->grid_zone.grid[Y+1][X-1].couleur + Jeu->grid_zone.grid[Y+1][X].couleur + Jeu->grid_zone.grid[Y+1][X+1].couleur ;

                        if(somme==Jeu->regle_standards[1])
                            Jeu->grid_zone.grid[Y][X].etat_suiv=Jeu->grid_zone.grid[Y][X].couleur;
                        else if(somme==Jeu->regle_standards[2])
                            Jeu->grid_zone.grid[Y][X].etat_suiv=1;
                        else Jeu->grid_zone.grid[Y][X].etat_suiv=0;
        }

    }
    }
    else
    {
        int somme=0,ind;
      for(int Y=Jeu->grid_zone.debut_ligne;Y<Jeu->grid_zone.fin_ligne;Y++)
        {
           for(int X=Jeu->grid_zone.debut_coll;X<Jeu->grid_zone.fin_coll;X++)
           {
               somme=  Jeu->grid_zone.grid[Y-1][X-1].couleur*256 + Jeu->grid_zone.grid[Y-1][X].couleur*128 + Jeu->grid_zone.grid[Y-1][X+1].couleur*64
                      + Jeu->grid_zone.grid[Y][X-1].couleur *32+ Jeu->grid_zone.grid[Y][X+1].couleur*8
                      + Jeu->grid_zone.grid[Y+1][X-1].couleur*4 + Jeu->grid_zone.grid[Y+1][X].couleur *2+ Jeu->grid_zone.grid[Y+1][X+1].couleur ;
                for(ind=0;ind<=Jeu->ind_dern_regle;ind++)
                {
                      if(somme==Jeu->regle_position[ind][0])
                         {Jeu->grid_zone.grid[Y][X].etat_suiv=Jeu->grid_zone.grid[Y][X].couleur;break;}
                      else if (somme==Jeu->regle_position[ind][1])
                         {Jeu->grid_zone.grid[Y][X].etat_suiv=1;break;}
                }
                if(ind==Jeu->ind_dern_regle+1)
                    Jeu->grid_zone.grid[Y][X].etat_suiv=0;
           }
        }
    }
        for(int Y=Jeu->grid_zone.debut_ligne;Y<Jeu->grid_zone.fin_ligne;Y++)
        {
            for(int X=Jeu->grid_zone.debut_coll;X<Jeu->grid_zone.fin_coll;X++)
                {
                    Jeu->grid_zone.grid[Y][X].couleur=Jeu->grid_zone.grid[Y][X].etat_suiv ;

                    if (  (      Y==Jeu->grid_zone.debut_ligne || Y==Jeu->grid_zone.fin_ligne-1
                              || X==Jeu->grid_zone.debut_coll  || X==Jeu->grid_zone.fin_coll-1
                          )
                        && Jeu->grid_zone.grid[Y][X].etat_suiv==1
                       )
                        {zoomer_grid(&Jeu->grid_zone);}

                }
        }

        /***********************************************************************/
        fourmi_info *crt=Jeu->fourmis;
    /**Parcourir la liste de toutes les fourmis et faire les testes pour les deplacer*/
    while(crt)
    {
        /**si la zone de la fourmi est blanche*/
    if(!Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x].etat_suiv)
    {
        Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x].couleur=1;
        switch (crt->direction)
        {
            case 1:  crt->pos_fourmi.x++; break;
            case 2 : crt->pos_fourmi.y++;      break;
            case 3 : crt->pos_fourmi.x--;  break;
            case 4 : crt->pos_fourmi.y--;     break;
            }
            if(crt->direction==4) crt->direction=1;
            else crt->direction++;
    }
        else if (!Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x].couleur)
        {
           Jeu->grid_zone.grid[crt->pos_fourmi.y][crt->pos_fourmi.x].etat_suiv=0;
            switch(crt->direction)
            {
                case 1 : crt->pos_fourmi.x--;  break;
                case 2 : crt->pos_fourmi.y--;    break;
                case 3 : crt->pos_fourmi.x++;  break;
                case 4 : crt->pos_fourmi.y++;     break;
            }
            if(crt->direction==1) crt->direction=4;
            else crt->direction--;
        }
        if(crt->pos_fourmi.x<0) crt->pos_fourmi.x=199;
        else if(crt->pos_fourmi.x>=200) crt->pos_fourmi.x=0;
        else if(crt->pos_fourmi.y<0) crt->pos_fourmi.y=119;
        else if(crt->pos_fourmi.y>=120) crt->pos_fourmi.y=0;


          crt=crt->suiv;
    }

        /***********************************************************************/

    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);

    /*********Modifier les iterations dnas le status barre***********/
           Jeu->iter++;
           afficher_statu_iteration(Jeu);
           /******************************************************************/

        if(!Jeu->iteration_precise) return TRUE;
        else if(Jeu->iteration_precise==1)
            {Jeu->iteration_precise--; return FALSE;}

        Jeu->iteration_precise--;
        return TRUE;
}
void afficher_statu_iteration(Lifegame *Jeu)
{
    /*********Modifier les iterations dnas le status barre***********/
           int id = gtk_statusbar_get_context_id (GTK_STATUSBAR(Jeu->statu.statubare), "iteration");
           gtk_statusbar_pop (GTK_STATUSBAR(Jeu->statu.statubare), id);
           char iter[20];
           sprintf(iter,"iteration : %d",Jeu->iter);
           gtk_statusbar_push (GTK_STATUSBAR(Jeu->statu.statubare), id, iter);
           /******************************************************************/
           return;
}
void couleur_fourmi(GtkWidget *b,Lifegame *Jeu)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(b),&Jeu->fourmi_couleur);
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
}
void aller_iteration(GtkWidget *entry,Lifegame *Jeu)
{
    int var=atoi(gtk_entry_get_text(entry));
    if(var)
    {
        Jeu->iteration_precise=var;
        g_timeout_add(0.9,(GSourceFunc)commencer_jeu,(Lifegame*)Jeu);
    }
    return;
}

void changer_vitesse(GtkWidget *scale,Lifegame *Jeu)
{
    Jeu->vitesse=(int)1001-gtk_range_get_value(scale);
    return;
}
void iter_suivante(GtkWidget *toolbar,Lifegame *Jeu)
{
    commencer_jeu(Jeu);
    return;
}

void radio_clicked(GtkWidget *b,BoutonSpin *spin[2])
{
  if(!strcmp(gtk_button_get_label(b),"Regles Personnalisees") && gtk_toggle_button_get_active(b))
       {
        gtk_widget_set_sensitive(spin[0]->Spin,FALSE);
        gtk_widget_set_sensitive(spin[1]->Spin,FALSE);
        return;
       }
  if(!strcmp(gtk_button_get_label(b),"Regles Standards") && gtk_toggle_button_get_active(b))
       {
        gtk_widget_set_sensitive(spin[0]->Spin,TRUE);
        gtk_widget_set_sensitive(spin[1]->Spin,TRUE);
       }
  return;
}
Image *initialiser_image();

void afficher_msg_about(GtkWidget *tooll,gpointer data)
{
    GtkWidget *content_area,*dialog=gtk_dialog_new_with_buttons("About",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,
                                                  GTK_RESPONSE_OK,NULL);
    content_area=gtk_dialog_get_content_area(dialog);
    Image *image_about=initialiser_image();
    image_about->chemin=".\\images\\about.png";
    creer_image(image_about);
    gtk_widget_set_size_request(dialog,300,300);
    gtk_window_set_position(dialog,GTK_WIN_POS_CENTER);
    associer_element(content_area,image_about->Image);
    afficher_tout(dialog);
    gint reponse=gtk_dialog_run(dialog);
    gtk_widget_destroy(dialog);
}
void Placer_fourmi(GtkWidget *bouton,Lifegame *Jeu)
{
    Jeu->nbr_fourmi++;
    if(!Jeu->fourmis)
    {
    Jeu->fourmis=(fourmi_info *)malloc(sizeof(fourmi_info));
    Jeu->fourmis->suiv=NULL;
    Jeu->fourmis->direction=1;
    Jeu->fourmis->pos_fourmi.x=80;
    Jeu->fourmis->pos_fourmi.y=50;
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
    return;
    }
    fourmi_info *crt=Jeu->fourmis;
    while(crt->suiv) crt=crt->suiv;
    crt->suiv=(fourmi_info *)malloc(sizeof(fourmi_info));
    crt->suiv->suiv=NULL;
    crt->suiv->direction=1;
    crt->suiv->pos_fourmi.x=80;
    crt->suiv->pos_fourmi.y=60;
    gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
    return;
}
void New_game(GtkWidget *tooll,Lifegame *Jeu)
{

    if(Jeu->play)pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,4),Jeu);
    /*****************initialiser le nombre d'iteration dans le status barre**************************/
    Jeu->iter=0;
    afficher_statu_iteration(Jeu);
    /***************************************************************************************/
    for(int ind=0;ind<122;ind++)
        for(int jnd=0;jnd<202;jnd++)
            {
              Jeu->grid_zone.grid[ind][jnd].couleur=0;//les cellules sont toutes blanches au premiers temps
              Jeu->grid_zone.grid[ind][jnd].etat_suiv=0;
            }

            Jeu->grid_zone.debut_coll=75;//l indice correspond au collone du debut de notre grid
            Jeu->grid_zone.fin_coll=125; // l'indice correspond au collone fin de notre grid dessinable
            Jeu->grid_zone.debut_ligne=45; // l indice correspond au ligne du debut
            Jeu->grid_zone.fin_ligne=75;   // l indice correspond au ligne du fin
            Jeu->grid_zone.case_taille=20; // la taille de chaque case du grid
            Jeu->fourmis=NULL;
            Jeu->nbr_fourmi=0;
            gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);
            return ;
}

void save_game(GtkWidget *tooll,Lifegame *Jeu)
{
    if(Jeu->play) pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,4),Jeu);
GtkWidget *dialog;
GtkFileChooser *chooser;
gint res;

dialog = gtk_file_chooser_dialog_new ("Save File",
                                      Jeu->ma_fenetre->fenetre,
                                      GTK_FILE_CHOOSER_ACTION_SAVE,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Save",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
chooser = GTK_FILE_CHOOSER (dialog);

gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  gtk_file_chooser_set_current_name (chooser,"JeuDeVie.ilisi");


res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    int i,j;
    filename = gtk_file_chooser_get_filename (chooser);
    FILE *f = fopen(filename,"w");
    fprintf(f,"%d\n",Jeu->iter);

    fprintf(f,"%d\t%d\t%d\t%d\t%d\n",Jeu->grid_zone.case_taille,Jeu->grid_zone.debut_ligne,
                                    Jeu->grid_zone.debut_coll,Jeu->grid_zone.fin_ligne,Jeu->grid_zone.fin_coll);
    for( i=0;i<120;i++)
       for( j=0;j<200;j++)
           fprintf(f,"%c",Jeu->grid_zone.grid[i][j].couleur);
    fclose(f);
   g_free (filename);
  }

gtk_widget_destroy (dialog);
}


void open_game(GtkWidget *tooll,Lifegame *Jeu)
{
    if(Jeu->play) pause_game(gtk_toolbar_get_nth_item(Jeu->toolbar.toolbar,4),Jeu);
    GtkWidget *dialog;
gint res;

dialog = gtk_file_chooser_dialog_new ("Open File",
                                      Jeu->ma_fenetre->fenetre,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Open",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;int i,j;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);

    FILE *f = fopen(filename,"r");
    fscanf(f,"%d\n",&Jeu->iter);

    fscanf(f,"%d\t%d\t%d\t%d\t%d\n",&Jeu->grid_zone.case_taille,&Jeu->grid_zone.debut_ligne,
                                    &Jeu->grid_zone.debut_coll,&Jeu->grid_zone.fin_ligne,&Jeu->grid_zone.fin_coll);
    for( i=0;i<120;i++)
       for( j=0;j<200;j++)
           fscanf(f,"%c",&Jeu->grid_zone.grid[i][j].couleur);
           fclose(f);
    g_free (filename);
  }
   afficher_statu_iteration(Jeu);
  gtk_widget_queue_draw(Jeu->grid_zone.zone_dessinable);

gtk_widget_destroy (dialog);
}


void start_game(GtkWidget *b,Lifegame *Jeu);
void pause_game(GtkWidget *b,Lifegame *Jeu)
          {
              Jeu->play=0;
              gtk_tool_button_set_stock_id(GTK_TOOL_BUTTON(b),GTK_STOCK_MEDIA_PLAY);
              g_signal_handlers_destroy(GTK_TOOL_BUTTON(b));
              g_source_remove(Jeu->a);
              g_signal_connect(b,"clicked",G_CALLBACK(start_game),Jeu);
          }
void start_game(GtkWidget *b,Lifegame *Jeu)
{
    Jeu->play=1;
    gtk_tool_button_set_stock_id(b,GTK_STOCK_MEDIA_PAUSE);
    g_signal_handlers_destroy(GTK_TOOL_BUTTON(b));
    g_signal_connect(b,"clicked",G_CALLBACK(pause_game),Jeu);
    Jeu->a=g_timeout_add(Jeu->vitesse,(GSourceFunc)commencer_jeu,(Lifegame*)Jeu);
}



#endif // MACRO_LIFEGAME_H_INCLUDED
