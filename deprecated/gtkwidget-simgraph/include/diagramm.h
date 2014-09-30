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


#ifndef __DIAGRAMM__
#define __DIAGRAMM__

#include "sarturis/interface/analoginput.h"
#include "sarturis/interface/updateable.h"
#include "sarturis/interface/resettable.h"
#include "sarturis/gtk/widget.h"
#include "legend.h"
#include "vrule.h"
#include "hrule.h"
#include "graph.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Diagramm : public Widget, public Updateable, public Resettable
    {
      public:
        // Konstruktor
        Diagramm(sarturis::ref<AnalogInput> Data,
                 sarturis::ref<AnalogInput> Time,
                 const std::string& Caption, unsigned int GridX,
                 unsigned int GridY, const std::string& UnitX,
                 const std::string& UnitY, double Red, double Green,
                 double Blue, unsigned char Style, unsigned char Thickness);

        // Update- und Reset-Methode
        void Update();
        void Reset();

      protected:
        // Destruktor
        virtual ~Diagramm();

      private:
        // Referenzen
        sarturis::ref<AnalogInput> data;
        sarturis::ref<AnalogInput> time;

        // Zwischengespeicherte Konfiguration
        std::string caption;
        unsigned int gridx;
        unsigned int gridy;
        std::string unitx;
        std::string unity;
        double red;
        double green;
        double blue;
        unsigned char style;
        unsigned char thickness;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Elemente
        sarturis::ref<Legend> legend;
        sarturis::ref<HRule> hrule;
        sarturis::ref<VRule> vrule;
        sarturis::ref<Graph> graph;

        // Style-Set Signal aus GTK
        static void styleset(GtkWidget* widget, GtkStyle* previous_style,
                             GtkWidget* table);

        // Daten
        double* values;
        double* times;
        unsigned int cnt;
        unsigned int allocated;

    };
  }
}
/******************************************************************************/

#endif
