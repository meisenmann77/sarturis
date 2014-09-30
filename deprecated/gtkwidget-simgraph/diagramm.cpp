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


#include <string.h>
#include "include/diagramm.h"
#include "sarturis/common/str.h"
#include "sarturis/base/generalexception.h"
#include "sarturis/apps/application.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Diagramm::Diagramm(sarturis::ref<AnalogInput> Data,
                   sarturis::ref<AnalogInput> Time, const std::string& Caption,
                   unsigned int GridX, unsigned int GridY,
                   const std::string& UnitX, const std::string& UnitY,
                   double Red, double Green, double Blue, unsigned char Style,
                   unsigned char Thickness):
            data(Data),
            time(Time),
            caption(Caption),
            gridx(GridX),
            gridy(GridY),
            unitx(UnitX),
            unity(UnitY),
            red(Red),
            green(Green),
            blue(Blue),
            style(Style),
            thickness(Thickness),
            values(0),
            times(0),
            cnt(0),
            allocated(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Diagramm::~Diagramm()
/******************************************************************************/
{
  if (values) delete [] values;
  if (times) delete [] times;
}
/******************************************************************************/


/******************************************************************************/
void Diagramm::Update()
/******************************************************************************/
{
  // evtl. neuen Speicher allokieren
  if (cnt==allocated)
  {
    // Speicher fuer 10000 zusaetzliche Werte
    allocated+=10000;
    double* v= 0;
    double* t= 0;
    v = new double[allocated];
    t = new double[allocated];

    // Fehler
    if (!v || !t)
    {
      SARTURIS_THROW(GeneralException("Cannot allocate new Memory"));
    }

    // Wenn alte Daten da - kopieren und freigeben
    if (cnt)
    {
      memcpy(v,values,cnt*sizeof(double));
      memcpy(t,times,cnt*sizeof(double));
      delete [] values;
      values = 0;
      delete [] times;
      times = 0;
    }

    // Pointer uebernehmen
    values=v;
    times=t;
  }
  if (!times || !values)
  {
    SARTURIS_THROW(GeneralException("Cannot allocate Memory"));
  }

  // Hochzaehlen und Werte holen
  if (times[cnt] != time->Get())
  {
	++cnt;
	values[cnt]=data->Get();
	times[cnt]=time->Get();
  }

  // Lineale anpassen
  bool vrule_changed=vrule->FitToValue(values,cnt);
  bool hrule_changed=hrule->FitToValue(times,cnt);

  // Limits des Graphen anpassen
  if (hrule_changed) graph->SetXBounds(hrule->GetLower(),hrule->GetUpper());
  if (vrule_changed) graph->SetYBounds(vrule->GetLower(),vrule->GetUpper());

  // Wenn ein Lineal veraendert, komplett, sonst nur "neue" Daten zeichnen
  if ((vrule_changed || hrule_changed) && (cnt != 0))
    graph->DrawComplete(times,values,cnt);
  else
    graph->DrawAppend(times,values,cnt);
}
/******************************************************************************/


/******************************************************************************/
void Diagramm::Reset()
/******************************************************************************/
{
  if (values) delete [] values;
  if (times) delete [] times;
  values=0;
  times=0;
  cnt=0;
  allocated=0;  

  if ((vrule == NULL) || (hrule == NULL) || (graph == NULL))
  {
	  SARTURIS_THROW(GeneralException("Diagram has not been properly initialised! Make sure it is displayed in a window."));
  }

  vrule->Reset();
  hrule->Reset();
  graph->Reset();

  graph->SetXBounds(hrule->GetLower(),hrule->GetUpper());
  graph->SetYBounds(vrule->GetLower(),vrule->GetUpper());
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Diagramm::setup()
/******************************************************************************/
{
  // Farben
  const unsigned long _red=(unsigned long)(red*65535.0);
  const unsigned long _green=(unsigned long)(green*65535.0);
  const unsigned long _blue=(unsigned long)(blue*65535.0);

  // Elemente
  legend=new Legend(caption,_red,_green,_blue,style,thickness);
  hrule=new HRule(gridx,unitx);
  vrule=new VRule(gridy,unity);
  graph=new Graph(_red,_green,_blue,style,thickness,gridx,gridy);
  gtk_widget_show(legend->GetWidget());
  gtk_widget_show(hrule->GetWidget());
  gtk_widget_show(vrule->GetWidget());
  gtk_widget_show(graph->GetWidget());

  // Limits des Graphen initialisieren
  graph->SetXBounds(hrule->GetLower(),hrule->GetUpper());
  graph->SetYBounds(vrule->GetLower(),vrule->GetUpper());

  // Tabelle
  GtkWidget* table=gtk_table_new(2,3,FALSE);
  gtk_widget_show(table);

  // Anordnen
  gtk_table_attach(GTK_TABLE(table),legend->GetWidget(),1,2,0,1,
                   (GtkAttachOptions)(GTK_FILL),
                   (GtkAttachOptions)(GTK_FILL),0,0);
  gtk_table_attach(GTK_TABLE(table),vrule->GetWidget(),0,1,1,2,
                   (GtkAttachOptions)(GTK_FILL),
                   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),0,0);
  gtk_table_attach(GTK_TABLE(table),graph->GetWidget(),1,2,1,2,
                   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
                   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),0,0);
  gtk_table_attach(GTK_TABLE(table),hrule->GetWidget(),1,2,2,3,
                   (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
                   (GtkAttachOptions)(GTK_FILL),0,0);

  // Verbinde Style-Set der Drawing-Areas
  g_signal_connect(G_OBJECT(legend->GetWidget()),"style-set",
                   G_CALLBACK(styleset),table);
  g_signal_connect(G_OBJECT(hrule->GetWidget()),"style-set",
                   G_CALLBACK(styleset),table);
  g_signal_connect(G_OBJECT(vrule->GetWidget()),"style-set",
                   G_CALLBACK(styleset),table);
  g_signal_connect(G_OBJECT(graph->GetWidget()),"style-set",
                   G_CALLBACK(styleset),table);

  return table;
}
/******************************************************************************/


/******************************************************************************/
void Diagramm::styleset(GtkWidget* widget, GtkStyle* previous_style,
                        GtkWidget* table)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(table));
}
/******************************************************************************/
