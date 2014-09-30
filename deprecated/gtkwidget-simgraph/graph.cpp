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


#include "include/graph.h"
#include "sarturis/base/generalexception.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Graph::Graph(unsigned long Red, unsigned long Green, unsigned long Blue,
             unsigned char Style, unsigned char Thickness, unsigned int GridX,
             unsigned int GridY):
        LineDrawer(Red,Green,Blue,Style,Thickness)
/******************************************************************************/
{
  // Initialisieren
  last_x=9;
  show_cross=false;
  fx1_0=0;
  values=0;
  bgr_pixmap=0;
  valuewindow=new ValueWindow("Sans 8");
  emptycursor=EmptyCursor::GetInstance();

  // Grid uebernehmen
  grid_x=GridX;
  grid_y=GridY;

  // Maushandler aktivieren
  gtk_widget_add_events(drawing_area,GDK_BUTTON_PRESS_MASK | 
                                     GDK_BUTTON_RELEASE_MASK | 
                                     GDK_BUTTON_MOTION_MASK);

  // Maus-Events verbinden
  g_signal_connect(G_OBJECT(drawing_area),"button_press_event",
                   G_CALLBACK(button_press),this);
  g_signal_connect(G_OBJECT(drawing_area),"button_release_event",
                   G_CALLBACK(button_release),this);
  g_signal_connect(G_OBJECT(drawing_area),"motion_notify_event",
                   G_CALLBACK(button_motion),this);
}
/******************************************************************************/


/******************************************************************************/
Graph::~Graph()
/******************************************************************************/
{
  if (values) delete [] values;
}
/******************************************************************************/


/******************************************************************************/
void Graph::SetXBounds(double X1, double X2)
/******************************************************************************/
{
  x1=X1;
  x2=X2;
}
/******************************************************************************/


/******************************************************************************/
void Graph::SetYBounds(double Y1, double Y2)
/******************************************************************************/
{
  y1=Y1;
  y2=Y2;
}
/******************************************************************************/


/******************************************************************************/
void Graph::DrawComplete(double* X, double* Y, unsigned int Cnt)
/******************************************************************************/
{
  // Testen
  if (y1==y2) return;

  // fx1_0 (Index ganz links) anpassen
  fx1_0+=look_x(X+fx1_0,x1,Cnt-fx1_0);

  // Hintergrund und Raster sowie Graph neuzeichnen
  draw();
  draw_graph(X,Y,Cnt);
}
/******************************************************************************/


/******************************************************************************/
void Graph::DrawAppend(double* X, double* Y, unsigned int Cnt)
/******************************************************************************/
{
  // Testen
  if (y1==y2) return;

  // Nur Graph neuzeichnen
  draw_graph(X,Y,Cnt);
}
/******************************************************************************/


/******************************************************************************/
void Graph::Reset()
/******************************************************************************/
{
  // Zuruecksetzen
  last_x=9;
  fx1_0=0;

  // Neuzeichnen
  gtk_widget_queue_resize(drawing_area);
}
/******************************************************************************/


/******************************************************************************/
void Graph::configure()
/******************************************************************************/
{
  // Speicher fuer values anlegen und initialisieren
  if (values)
  {
	  delete [] values;
	  values = 0;
  }
  values=new Value[drawing_area->allocation.width];
  if (!values)
  {
    SARTURIS_THROW(GeneralException("Cannot allocate Memory"));
  }
  for (int i=0;i<drawing_area->allocation.width;++i)
  {
    values[i].x=0.0;
    values[i].y=0.0;
    values[i].py=0;
  }

  // Bild fuer Hintergrund freigeben, wenn vorhanden
  if (bgr_pixmap) gdk_pixmap_unref(bgr_pixmap);

  // Neues Bild, mit entsprechender Groesse anlegen 
  bgr_pixmap=gdk_pixmap_new(drawing_area->window,drawing_area->allocation.width,
                            drawing_area->allocation.height,-1);

  // Hintergrundrechteck
  gdk_draw_rectangle(bgr_pixmap,drawing_area->style->mid_gc[0],TRUE,0,0,
                     drawing_area->allocation.width,
                     drawing_area->allocation.height);

  // GC für Gitterlinien erzeugen
  GdkGC* gc=gdk_gc_new(bgr_pixmap);
  gdk_gc_copy(gc,drawing_area->style->fg_gc[0]);
  gdk_gc_set_line_attributes(gc,1,GDK_LINE_ON_OFF_DASH,GDK_CAP_NOT_LAST,
                             GDK_JOIN_MITER);


  // Grid-Weite und Hoehe
  const unsigned int gw=(drawing_area->allocation.width-20)/(grid_x+1);
  const unsigned int gh=(drawing_area->allocation.height-20)/(grid_y+1);

  // horizontale Gitterlinien
  for (unsigned int i=0;i<grid_y+2;++i)
  {
    const unsigned int p=10+i*gh;
    gdk_draw_line(bgr_pixmap,gc,0,p,drawing_area->allocation.width,p);
  }

  // vertikale Gitterlinien
  for (unsigned int i=0;i<grid_x+2;++i)
  {
    const unsigned int p=10+i*gw;
    gdk_draw_line(bgr_pixmap,gc,p,0,p,drawing_area->allocation.height);
  }

  // GC fuer Gitterlinien freigeben
  gdk_gc_destroy(gc);
}
/******************************************************************************/


/******************************************************************************/
void Graph::draw()
/******************************************************************************/
{
  // Kein Bild
  if (pixmap==NULL) return;

  // fx1 (letzte Suchpos.) und last_x zuruecksetzen
  fx1=fx1_0;
  last_x=9;

  // Zeichne Hintergrundbild in pixmap
  gdk_draw_pixmap(pixmap,
                  drawing_area->style->fg_gc[GTK_WIDGET_STATE(drawing_area)],
                  bgr_pixmap,
                  0,0,0,0,
                  drawing_area->allocation.width,
                  drawing_area->allocation.height);
}
/******************************************************************************/


/******************************************************************************/
void Graph::draw_cross(unsigned int x)
/******************************************************************************/
{
  // Im Bereich
  if ((x<10) || (x>=(unsigned int)(drawing_area->allocation.width-10))) return;

  // y holen und Bereich testen
  const unsigned int y=values[x].py;
  if ((y<10) || (y>=(unsigned int)(drawing_area->allocation.height-10))) return;

  // GC anlegen
  GdkGC* gc=gdk_gc_new(drawing_area->window);
  gdk_gc_set_line_attributes(gc,1,GDK_LINE_ON_OFF_DASH,GDK_CAP_NOT_LAST,
                             GDK_JOIN_MITER);
  gint8 dash[]={5,5,2,5};
  gdk_gc_set_dashes(gc,0,dash,4);

  // Achsenkreuz zeichnen
  gdk_draw_line(pixmap,gc,x,10,x,
                drawing_area->allocation.height-10);
  gdk_draw_line(pixmap,gc,10,values[x].py,
                drawing_area->allocation.width-10,values[x].py);

  // GC freigeben
  gdk_gc_unref(gc);

  // Wertefenster
  valuewindow->SetValues(values[x].x,values[x].y);
  valuewindow->SetPosition(5+x+transform[0],5+y+transform[1]);
  valuewindow->Show();

  // Merke alte Position
  cross_old[0]=x;
  cross_old[1]=values[x].py;
}
/******************************************************************************/


/******************************************************************************/
void Graph::release_cross()
/******************************************************************************/
{
  // Bild in Umgebung der alten Mauspos neuzeichnen
  gdk_draw_pixmap(pixmap,
                  drawing_area->style->fg_gc[GTK_WIDGET_STATE(drawing_area)],
                  bgr_pixmap,10,cross_old[1],10,cross_old[1],
                  drawing_area->allocation.width,1);
  gdk_draw_pixmap(pixmap,
                  drawing_area->style->fg_gc[GTK_WIDGET_STATE(drawing_area)],
                  bgr_pixmap,cross_old[0],10,cross_old[0],10,1,
                  drawing_area->allocation.height);

  // Wertefenster
  valuewindow->Hide();
}
/******************************************************************************/


/******************************************************************************/
void Graph::draw_graph(double* X, double* Y, unsigned int Cnt)
/******************************************************************************/
{
  // Abfangen
  if (!pixmap) return;
  if (Cnt == 0) return;

  // Kontext fuer Linie und Farbe setzen
  GdkGC* gc=gdk_gc_new(pixmap);
  attach_to_gc(gc);

  // Fuer jeden x-Wert, Zeit und Y-Wert ausrechnen
  for (unsigned int i=last_x+1;(int)i<=(drawing_area->allocation.width-10);++i)
  {
    // Zeit (nicht ueber max. hinaus)
    const double x=x1+(x2-x1)*(double)(i-10)/
                              (double)(drawing_area->allocation.width-20);
    if (x>X[Cnt-1]) break;

    // Zugeordneter "linker" und "rechter" Wert
    fx1+=look_x(X+fx1,x,Cnt-fx1);
    unsigned int fx2=fx1;
    if ((fx1<Cnt-1) && (X[fx1]!=x)) ++fx2;

    // normierten y-Wert berechnen (aus Durchschnitt)
    const double y=0.5*(Y[fx1]+Y[fx2]);
    const double ny=(y-y1)/(y2-y1);
    const unsigned int py=
      10+(unsigned int)((1.0-ny)*(double)(drawing_area->allocation.height-20));

    // Linie zeichnen, wenn nicht erster Punkt
    if (i>10)
    {
      // Nur jeden 3. Pkt. zeichnen
      if (i-last_x==3)
      {
        gdk_draw_line(pixmap,gc,last_x,last_y,i,py);
        last_x=i;
        last_y=py;
      }
    }
    // Ersten Punkt merken
    else
    {
      last_x=i;
      last_y=py;
    }

    // Daten merken
    values[i].x=x;
    values[i].y=y;
    values[i].py=py;
  }

  // Gc freigeben und Widget neuzeichnen
  gdk_gc_unref(gc);
  gtk_widget_queue_draw(drawing_area);

  // Evtl. Kreuz anzeigen und Wertefenster aktualisieren
  if (show_cross) 
  {
    draw_cross(cross_old[0]);                             
  }
}
/******************************************************************************/


/******************************************************************************/
bool Graph::is_inside(int x, int y)
/******************************************************************************/
{
  if (x<10) return false;
  if (y<10) return false;
  if (x>drawing_area->allocation.width-10) return false;
  if (y>drawing_area->allocation.height-10) return false;

  return true;
}
/******************************************************************************/


/******************************************************************************/
gint Graph::button_press(GtkWidget* widget, GdkEventButton* event, Graph* graph)
/******************************************************************************/
{
  // Transformation speichern
  graph->transform[0]=(unsigned int)event->x_root-(unsigned int)event->x;
  graph->transform[1]=(unsigned int)event->y_root-(unsigned int)event->y;

  // Bereich der Maus
  if (!graph->is_inside((int)(event->x),(int)(event->y))) return TRUE;

  // Je nach Maustaste
  switch (event->button)
  {
    // linke Maustaste - Kreuz und Wert-Anzeige
    case 1:
            // Kreuz
            graph->show_cross=true;
            graph->draw_cross((unsigned int)event->x);
            break;
  }

  // Leeren Cursor setzen und return
  gdk_window_set_cursor(graph->drawing_area->window,
                        graph->emptycursor->GetCursor());
  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
gint Graph::button_release(GtkWidget* widget, GdkEventButton* event,
                           Graph* graph)
/******************************************************************************/
{
  // Bereich der Maus
  if (!graph->is_inside((int)(event->x),(int)(event->y))) return TRUE;

  // Kreuz loeschen
  if (graph->show_cross)
  {
    graph->release_cross();
    graph->show_cross=false;
  }

  // Graph neuzeichnen
  graph->draw();

  // Pfeil wiederherstellen und return
  gdk_window_set_cursor(graph->drawing_area->window,0);
  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
gint Graph::button_motion(GtkWidget* widget, GdkEventMotion* event, 
                          Graph* graph)
/******************************************************************************/
{
  // Transformation speichern
  graph->transform[0]=(unsigned int)event->x_root-(unsigned int)event->x;
  graph->transform[1]=(unsigned int)event->y_root-(unsigned int)event->y;

  // Ausserhalb des Bereiches kein Kreuz zeichnen
  if (!graph->is_inside((int)(event->x),(int)(event->y)))
  {
    // Kreuz loeschen
    graph->release_cross();
    graph->show_cross=false;

    // Graph neuzeichnen
    graph->draw();

    // Pfeil wiederherstellen und return
    gdk_window_set_cursor(graph->drawing_area->window,0);
    return TRUE;
  }

  // Kreuz und Werte-Fenster neuzeichnen
  if (graph->show_cross)
  {
    // Kreuz an alter Pos. loeschen (ueberzeichnet Graph)
    graph->release_cross();

    // Graph wiederherstellen
    graph->draw();

    // Kreuz an neuer Pos. zeichnen
    graph->draw_cross((unsigned int)event->x);
  }

  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
unsigned int Graph::look_x(double* values, double x, unsigned int cnt)
/******************************************************************************/
{
  unsigned int left=0;
  unsigned int right= cnt > 0 ? cnt-1 : 0;

  while (right-left>1)
  {
    unsigned int middle=left+(right-left)/2;

    if (values[middle]<=x) left=middle;
    if (values[middle]>x) right=middle;
  }

  return left;
}
/******************************************************************************/
