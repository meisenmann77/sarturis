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


#ifndef __GRAPH__
#define __GRAPH__

#include "sarturis/gtk/emptycursor.h"
#include "valuewindow.h"
#include "linedrawer.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Graph : public LineDrawer
    {
      public:
        // Konstruktor
        Graph(unsigned long Red, unsigned long Green, unsigned long Blue,
              unsigned char Style, unsigned char Thickness,
              unsigned int GridX, unsigned int GridY);

        // Grenzen setzen
        void SetXBounds(double X1, double X2);
        void SetYBounds(double Y1, double Y2);

        // Zeichnen
        void DrawComplete(double* X, double* Y, unsigned int Cnt);
        void DrawAppend(double* X, double* Y, unsigned int Cnt);

        // Zuruecksetzen
        void Reset();

      protected:
        // Destruktor
        ~Graph();

      private:
        // Zeichnen
        void configure();
        void draw();
        void draw_cross(unsigned int x);
        void release_cross();
        void draw_graph(double* X, double* Y, unsigned int Cnt);

        // Punkt im Widget
        bool is_inside(int x, int y);

        // Events
        static gint button_press(GtkWidget* widget, GdkEventButton* event,
                                 Graph* graph);
        static gint button_release(GtkWidget* widget, GdkEventButton* event,
                                   Graph* graph);
        static gint button_motion(GtkWidget* widget, GdkEventMotion* event, 
                                  Graph* graph);

        // Suche nach der Zeit
        static unsigned int look_x(double* values, double x, unsigned int cnt);

        // Member-Variablen
        unsigned int grid_x;
        unsigned int grid_y;
        unsigned int cross_old[2];
        unsigned int transform[2];
        bool show_cross;
        unsigned int last_x;
        unsigned int last_y;
        unsigned int fx1;
        unsigned int fx1_0;

        // Grenzen
        double x1;
        double x2;
        double y1;
        double y2;

        // Hintergrund-Rechteck
        GdkPixmap* bgr_pixmap;

        // Struktur fuer Wert-Speicher
        typedef struct
        {
          double x;
          double y;
          int py;
        } Value;
        Value* values;

        // leere Cursor und Wert-Anzeige
        sarturis::ref<EmptyCursor> emptycursor;
        sarturis::ref<ValueWindow> valuewindow;
    };
  }
}
/******************************************************************************/

#endif
