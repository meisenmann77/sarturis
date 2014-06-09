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


#include "sarturis/gtk/compat.h"
#include "sarturis/reflection/type.h"
#include "include/mainwidget.h"
using namespace sarturis::gtk;
using namespace sarturis::reflection;


/******************************************************************************/
MainWidget::MainWidget()
/******************************************************************************/
{
  typetree=new TypeTree(*this);
  instancetree=new InstanceTree;
  instancefilter=new TextEntry(*this);
}
/******************************************************************************/


/******************************************************************************/
MainWidget::~MainWidget()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void MainWidget::AddInstance(sarturis::ref<Referenced> R)
/******************************************************************************/
{
  // Typ bestimmen
  sarturis::ref<Type> t=Type::Get(R);
  if (!t) return;

  // Typ in Baum und Liste
  typetree->Add(t->GetName());
  types.insert(t->GetName());

  // Instanz in Baum
  instancetree->Add(t,R);
  instancetree->SetFilter(types,instancefilter->GetText());
}
/******************************************************************************/


/******************************************************************************/
void MainWidget::Change()
/******************************************************************************/
{
  // Bestimme sichtbare Typen
  type_set vis_types;
  for (type_set::const_iterator iter=types.begin();iter!=types.end();++iter)
  {
    if (typetree->Active(*iter)) vis_types.insert(*iter);
  }

  // Instanzen filtern
  instancetree->SetFilter(vis_types,instancefilter->GetText());
}
/******************************************************************************/


/******************************************************************************/
sarturis::ref<InstanceTree> MainWidget::GetInstanceTree() const
/******************************************************************************/
{
  return instancetree;
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* MainWidget::setup()
/******************************************************************************/
{
  // HPaned und Frame1
  GtkWidget* main=_gtk_hpaned_new();
  GtkWidget* frm1=gtk_frame_new("");
  GtkWidget* frm2=gtk_frame_new("");
  gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frm1))),
                       " <b>Filter</b> ");
  gtk_label_set_markup(GTK_LABEL(gtk_frame_get_label_widget(GTK_FRAME(frm2))),
                       " <b>Instanzen</b> ");

  // Frames auf HPaned
  gtk_paned_add1(GTK_PANED(main),frm1);
  gtk_paned_add2(GTK_PANED(main),frm2);
  gtk_paned_set_position(GTK_PANED(main),250);

  // Alignments fuer Frames
  GtkWidget* al1=gtk_alignment_new(0.0,0.0,1.0,1.0);
  GtkWidget* al2=gtk_alignment_new(0.0,0.0,1.0,1.0);
  gtk_alignment_set_padding(GTK_ALIGNMENT(al1),5,5,5,5);
  gtk_alignment_set_padding(GTK_ALIGNMENT(al2),5,5,5,5);
  gtk_container_add(GTK_CONTAINER(frm1),al1);
  gtk_container_add(GTK_CONTAINER(frm2),al2);
  
  // VBox fuer linken Teil (Filter)
  GtkWidget* vbox=_gtk_vbox_new(FALSE,5);

  // Child-Widgets der Frames in Alignments
  gtk_container_add(GTK_CONTAINER(al1),vbox);
  gtk_container_add(GTK_CONTAINER(al2),instancetree->GetWidget());

  // Labels
  GtkWidget* l1=gtk_label_new("Typen");
  GtkWidget* l2=gtk_label_new("Instanz");
  gtk_misc_set_alignment(GTK_MISC(l1),0.0,0.5);
  gtk_misc_set_alignment(GTK_MISC(l2),0.0,0.5);

  // Baum Textfeld auf Box
  gtk_box_pack_start(GTK_BOX(vbox),l1                         ,FALSE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(vbox),typetree->GetWidget()      ,TRUE ,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox),l2                         ,FALSE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(vbox),instancefilter->GetWidget(),FALSE,TRUE,0);

  // Anzeigen und return
  gtk_widget_show(l1);
  gtk_widget_show(l2);
  gtk_widget_show(frm1);
  gtk_widget_show(frm2);
  gtk_widget_show(al1);
  gtk_widget_show(al2);
  gtk_widget_show(main);
  gtk_widget_show(vbox);
  return main;
}
/******************************************************************************/
