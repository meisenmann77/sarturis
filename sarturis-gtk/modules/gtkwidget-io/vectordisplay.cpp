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


#ifdef WIN32
  #define _CRT_SECURE_NO_DEPRECATE
#endif
#include "sarturis/linalg/vector.h"
#include "sarturis/gtk/compat.h"
#include "include/vectordisplay.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
VectorDisplay::VectorDisplay(sarturis::ref<VectorInput> A):a(A),vbox(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
VectorDisplay::~VectorDisplay()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void VectorDisplay::Update()
/******************************************************************************/
{
  // Wenn keine Box da, kein Update
  if (!vbox) return;

  // Vector lesen
  Vector v(a->Get());

  // Texte in value_label setzen
  for (unsigned int i=0;i<value_label.size();++i)
  {
    char buf[100];
    sprintf(buf,"%.3g",v(i));
    gtk_label_set_text(GTK_LABEL(value_label[i]),buf);
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* VectorDisplay::setup()
/******************************************************************************/
{
  // Vbox
  vbox=_gtk_vbox_new(FALSE,2);
  gtk_widget_show(vbox);

  // Werte und Beschreibung, Dimension aus Vector
  Vector aval=a->Get();
  unsigned int dim=aval.Dimension();
  std::vector<std::string> ades;
  for (unsigned int i=0;i<dim;++i)
  {
      char buf[100];
	  sprintf(buf,"%d",i);
	  ades.push_back(std::string(buf));
  }
  // Anzeigen erzeugen
  for (unsigned int i=0;i<dim;++i)
  {
	  // H-Box fuer Label
    GtkWidget* hbox=_gtk_hbox_new(FALSE,5);
    gtk_widget_show(hbox);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);

    // Label fuer Beschriftung
    GtkWidget* label=gtk_label_new(ades[i].c_str());
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);

    // Label fuer Wert
    char buf[100];
    sprintf(buf,"%.3g",aval(i));
    GtkWidget* value=gtk_label_new(buf);
    gtk_widget_show(value);
    gtk_box_pack_end(GTK_BOX(hbox),value,FALSE,FALSE,0);

    // Merke Label
    value_label.push_back(value);
  }

  return vbox;
}
/******************************************************************************/
