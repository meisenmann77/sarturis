/*******************************************************************************
 *
 * Sarturis is (C) Copyright 2006-2011 by Dresden University of Technology
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * 
 ******************************************************************************/


#include <stdlib.h>
#include <fstream>
#include "sarturis/common/str.h"
#include "sarturis/apps/application.h"
#include "sarturis/base/os.h"
#include "sarturis/apps/datamanager.h"
#include "include/errordialog.h"
#include "include/glade.h"
#include "joe.h"
using namespace sarturis;


/******************************************************************************/
#define GETWIDGET(A) (GtkWidget*)g_object_get_data(G_OBJECT(dialog),A)
/******************************************************************************/


/******************************************************************************/
ErrorDialog::ErrorDialog()
/******************************************************************************/
{
  // Dialog erzeugen
  dialog=create_errordialog();
  gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
}
/******************************************************************************/


/******************************************************************************/
ErrorDialog::~ErrorDialog()
/******************************************************************************/
{
  gtk_widget_destroy(dialog);
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::Show(const std::string& Caption,
                       const std::string& ErrorMessage,
                       bool SarturisThrow, const Referenced* Object,
                       const std::string& Filename, unsigned int LineNumber)
/******************************************************************************/
{
  // Setze Ueberschrift und Text
  gtk_window_set_title(GTK_WINDOW(dialog),Caption.c_str());
  gtk_label_set_text(GTK_LABEL(GETWIDGET("la_main")),ErrorMessage.c_str());

  // Expander
  events=Logger::GetEvents();
  setup_source_expander(SarturisThrow,Object,Filename,LineNumber);
  setup_logging_expander();

  // JOE ca. 20 Prozent Wahrscheinlichkeit
  srand(OS::GetTickCount());
  if ((double)rand()>0.8*(double)RAND_MAX)
  {
    gtk_image_set_from_pixbuf(GTK_IMAGE(GETWIDGET("image1")),
                              Pixbuf(_joe_,sizeof(_joe_)));
  }

  // Setze Focus auf OK-Button
  gtk_widget_grab_focus(GETWIDGET("btn_ok"));

  // Starte Dialog
  gtk_dialog_run(GTK_DIALOG(dialog));
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::update_list()
/******************************************************************************/
{
  // Erst mal alles loeschen
  gtk_list_store_clear(liststore);

  // Listen-Eintraege
  for (unsigned int i=0;i<events.size();++i)
  {
    if (filter(events[i]))
    {
      // Kategorie
      std::string c;
      switch (events[i].first)
      {
        case Logger::DEBUG:     c="Debug"; break;
        case Logger::INFO:      c="Info"; break;
        case Logger::WARNING:   c="Warnung"; break;
        case Logger::EXCEPTION: c="Fehler"; break;
        case Logger::NONE:      break;
        case Logger::ALL:       break;
      }

      // Neuer Eintrag
      GtkTreeIter it;
      gtk_list_store_append(liststore,&it);
      gtk_list_store_set(liststore,&it,0,c.c_str(),1,events[i].second.c_str(),
                         -1);
    }
  }
}
/******************************************************************************/


/******************************************************************************/
bool ErrorDialog::filter(const Logger::event& e)
/******************************************************************************/
{
  return (((e.first==Logger::INFO) &&
          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_info))) ||
          ((e.first==Logger::WARNING) &&
          gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_warning))) ||
          ((e.first==Logger::EXCEPTION) &&
           gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_error))));
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::setup_source_expander(bool SarturisThrow,
                                        const Referenced* Object,
                                        const std::string& Filename,
                                        unsigned int LineNumber)
/******************************************************************************/
{
  // Deaktiviere Expander, wenn kein SARTURIS_THROW
  if (!SarturisThrow)
  {
    gtk_widget_set_sensitive(GETWIDGET("ex_source"),FALSE);
    return;
  }

  // Liste
  GtkListStore* ls=gtk_list_store_new(2,G_TYPE_STRING,G_TYPE_STRING);

  // Liste
  GtkWidget* tv_source=GETWIDGET("tv_source");
  gtk_tree_view_set_model(GTK_TREE_VIEW(tv_source),GTK_TREE_MODEL(ls));

  // Textrenderer
  GtkCellRenderer* textrenderer=gtk_cell_renderer_text_new(); 

  // Spalte fuer Level
  GtkTreeViewColumn* spalte1=
    gtk_tree_view_column_new_with_attributes("",textrenderer,"text",0,NULL);
  g_object_set(spalte1,"resizable",TRUE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tv_source),spalte1);

  // Spalte fuer Text
  GtkTreeViewColumn* spalte2=
    gtk_tree_view_column_new_with_attributes("",textrenderer,"text",1,NULL);
  g_object_set(spalte2,"resizable",TRUE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tv_source),spalte2);

  // Name
  GtkTreeIter it;
  gtk_list_store_append(ls,&it);
  gtk_list_store_set(ls,&it,0,"Object",1,
                     DataManager::GetName(Object).c_str(),-1);

  // Type
  Config cfg=DataManager::GetConfig(Object);
  if (cfg.HasAttribute("xsi:type"))
  {
    gtk_list_store_append(ls,&it);
    gtk_list_store_set(ls,&it,0,"Type",1,
                       cfg.GetSingleAttribute<std::string>("xsi:type").c_str(),
                       -1);
  }

  // Konfiguration
  if (cfg.HasAttribute("XMLFile"))
  {
    gtk_list_store_append(ls,&it);
    gtk_list_store_set(ls,&it,0,"Config",1,
                       cfg.GetSingleAttribute<std::string>("XMLFile").c_str(),
                       -1);
  }

  // Quelle
  const std::string source=Filename+":"+str(LineNumber);
  gtk_list_store_append(ls,&it);
  gtk_list_store_set(ls,&it,0,"Source",1,source.c_str(),-1);
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::setup_logging_expander()
/******************************************************************************/
{
  // Deaktiviere Expander wenn keine Events
  if (events.size()==0)
  {
    gtk_widget_set_sensitive(GETWIDGET("ex_logging"),FALSE);
    return;
  }

  // Liste
  liststore=gtk_list_store_new(2,G_TYPE_STRING,G_TYPE_STRING);

  // Widgets
  cb_info=GETWIDGET("cb_info");
  cb_warning=GETWIDGET("cb_warning");
  cb_error=GETWIDGET("cb_error");

  // Liste
  GtkWidget* tv_logging=GETWIDGET("tv_logging");
  gtk_tree_view_set_model(GTK_TREE_VIEW(tv_logging),GTK_TREE_MODEL(liststore));

  // Textrenderer
  GtkCellRenderer* textrenderer=gtk_cell_renderer_text_new(); 

  // Spalte fuer Level
  GtkTreeViewColumn* spalte1=
    gtk_tree_view_column_new_with_attributes("",textrenderer,"text",0,NULL);
  g_object_set(spalte1,"resizable",TRUE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tv_logging),spalte1);

  // Spalte fuer Text
  GtkTreeViewColumn* spalte2=
    gtk_tree_view_column_new_with_attributes("",textrenderer,"text",1,NULL);
  g_object_set(spalte2,"resizable",TRUE,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tv_logging),spalte2);

  // Liste aufbauen
  update_list();

  // Setze Events fuer Checkboxen
  g_signal_connect(G_OBJECT(cb_info),"clicked",G_CALLBACK(oncheck),this);
  g_signal_connect(G_OBJECT(cb_warning),"clicked",G_CALLBACK(oncheck),this);
  g_signal_connect(G_OBJECT(cb_error),"clicked",G_CALLBACK(oncheck),this);

  // Setze Event fuer Speichern-Button
  g_signal_connect(G_OBJECT(GETWIDGET("btn_save")),"clicked",
                   G_CALLBACK(onsave),this);
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::oncheck(GtkButton* btn, ErrorDialog* e)
/******************************************************************************/
{
  // Liste neu aufbauen
  e->update_list();
}
/******************************************************************************/


/******************************************************************************/
void ErrorDialog::onsave(GtkButton* btn, ErrorDialog* e)
/******************************************************************************/
{
  // Dialog anzeigen
  std::string fname=Base::SaveDialog("Speichern");
  if (fname!="")
  {
    // Datei oeffen
    std::ofstream str(fname.c_str());
    if (str.is_open())
    {
      // Alle Events
      for (unsigned int i=0;i<e->events.size();++i)
      {
        if (e->filter(e->events[i]))
        {
          // Kategorie
          std::string c;
          switch (e->events[i].first)
          {
            case Logger::DEBUG:     c="Debug:   "; break;
            case Logger::INFO:      c="Info:    "; break;
            case Logger::WARNING:   c="Warnung: "; break;
            case Logger::EXCEPTION: c="Fehler:  "; break;
            case Logger::NONE:      break;
            case Logger::ALL:       break;
          }

          // Ausgabe
          str << c << e->events[i].second << std::endl;
        }
      }
    }
    else Base::ErrorDialog("Fehler","Datei "+fname+
                              " konnte nicht zum Schreiben geoeffnet werden!");
  }
}
/******************************************************************************/
