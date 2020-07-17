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


/*
 * cairowidget.h
 *
 *  Created on: 23.01.2012
 *      Author: marcus, sebastian
 */

#ifndef CAIROWIDGET_H_
#define CAIROWIDGET_H_

#include "sarturis/gtk/activewidget.h"
#include "sarturis/gtk/base.h"
#include <cairo.h>

/******************************************************************************/
namespace sarturis {
	namespace gtk {
		/***
		 * Cairo-Widget ist eine abstrakte Klasse, die dem Programmierer beim
		 * Arbeiten mit Cairo einige Sachen in Bezug auf GTK erleichtert.
		 *
		 * Damit neu gezeichnet wird muss nur noch die Methode Invalidate()
		 * aufgerufen werden.
		 *
		 * Die Klasse fordert außerdem die Implementierung einer Update()-
		 * Methode (da sie von ActiveWidget erbt, welches Updateable ist)
		 * und die Implementierung einer Draw(cairo_t*)-Methode, die die
		 * eigentliche Zeichenroutine enthält.
		 * Die beiden GTK-Callbacks "expose-event" und "configure-event"
		 * werden von dieser Klasse automatisch behandelt.
		 */
		class CairoWidget: public ActiveWidget {
			public:
				// Konstruktor
				CairoWidget();

				// Destruktor
				virtual ~CairoWidget();

				// Die Methode Update muss implementiert werden
				virtual void Update()=0;

			protected:
				// Höhe und Breite des Fensters, werden im configure-Event
				// gesetzt
				int width;
				int height;

				// Die Methode Invalidate wird benutzt um die ganze Grafik neu
				// zu zeichnen
				void Invalidate();

				// Die Methode Draw() enthält die Zeichenroutine zum Zeichnen
				// der eigentlichen Grafik
				virtual void Draw(cairo_t* cr)=0;

			private:
				// Der Cairo-Kontext wird von dieser Klasse automatisch beim
				// Aufruf des OnExpose-Callbacks aufgerufen
				cairo_t* cairo_context;

				// GTK-Callbacks und Methoden die von dieser Klasse behandelt
				// werden
				GtkWidget* setup();
				static gboolean OnDraw(GtkWidget* widget, cairo_t* c,
						gpointer user_data);
				static gboolean OnConfigure(GtkWidget* w, GdkEventConfigure* e,
						gpointer user_data);
		};
	}
}
/******************************************************************************/

#endif /* CAIROWIDGET_H_ */
