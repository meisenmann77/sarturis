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


#ifndef _SARTURIS_PLAYERCONTROL_H_
#define _SARTURIS_PLAYERCONTROL_H_


#include "sarturis/interface/updateable.h"
#include "sarturis/interface/analogoutput.h"
#include "sarturis/interface/digitaloutput.h"
#include "sarturis/interface/executable.h"
#include "sarturis/gtk/widget.h"

/******************************************************************************/
namespace sarturis
{
	namespace gtk
	{
	class PlayerControl : public Updateable, public Widget
		{

		public: 
			PlayerControl(sarturis::ref<AnalogOutput> Time,
						  sarturis::ref<DigitalOutput> Play,
						  sarturis::ref<Executable> OnStart,
				          double Schrittweite,
				          unsigned int Startzeit,
						  unsigned int Endzeit);
						
			// Implementation Updateable
			void Update();
			
		protected: 

			~PlayerControl();

		private:
			sarturis::ref<AnalogOutput> t;
			sarturis::ref<DigitalOutput> p;
			sarturis::ref<Executable> onStart;
			// Startzeit
			unsigned int startZeit;
			// Endzeit
			unsigned int endZeit;
			// aktuelle Zeit
			double time;
			// Schrittweite
			double schrittweite;
			// Faktor für Abspielgeschwindigkeit
			int factor;
			// Play
			bool play;

			// Scale
			GtkWidget* scale;
			// FactorLabel
			GtkWidget* factorlabel;

			// Start/stop/Weiter-Knopf
			GtkWidget* startbutton;
			// Zurücksetzen bei Stop
			void reset();

			// Impl. Widget::setup
            GtkWidget* setup();

			// Style-Set Signal aus GTK
			static void styleset(GtkWidget* widget, GtkStyle* previous_style,
                             GtkWidget* parent);

			// Callback fuer GTK
			static void startclicked(GtkWidget* button, PlayerControl* b);
			static void pauseclicked(GtkWidget* button, PlayerControl* b);
			static void forwardclicked(GtkWidget* button, PlayerControl* b);
			static void backwardclicked(GtkWidget* button, PlayerControl* b);

			void setFactorLabel();
		};
	};
}; 
/******************************************************************************/

#endif 
