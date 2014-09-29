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


/*********************************************************************************
\file		playercontrol.cpp

\author		Robin Kramer

\version	1.0
*********************************************************************************/
#ifndef WIN32
#define LINUX
#endif

#include "include/playercontrol.h"
#include "sarturis/common/str.h"
#include "sarturis/gtk/compat.h"
#include <gtk/gtk.h>

using namespace sarturis;
using namespace gtk;

/******************************************************************************/
PlayerControl::PlayerControl(sarturis::ref<AnalogOutput> Time,
						     sarturis::ref<DigitalOutput> Play,
							 sarturis::ref<Executable> OnStart,
						     double Schrittweite,
							 unsigned int Startzeit,
							 unsigned int Endzeit):
t(Time),p(Play),onStart(OnStart),startZeit(Startzeit),endZeit(Endzeit),time(Startzeit),
schrittweite(Schrittweite),factor(1),play(false)
/******************************************************************************/
{
	if(t.valid()) t->Set(time);
	if(p.valid()) p->Set(play);
}
/******************************************************************************/

/******************************************************************************/
PlayerControl::~PlayerControl()
/******************************************************************************/
{
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::Update()
/******************************************************************************/
{
	// run prüfen
	if (play)	 
	{
		// aktuellen Wert von Scale holen, es könnte ja jemand geschoben haben
		time = gtk_range_get_value(GTK_RANGE(scale));
		// neue Zeit mit factor berechnen
		time += schrittweite * factor;	 
		// neuen Wert bei Scale setzen
		gtk_range_set_value(GTK_RANGE(scale),time);
	}
	// wenn nicht dann alte Zeit

	// ausgaben setzen
	if(t.valid()) t->Set(time);
	if(p.valid()) p->Set(play);
}
/******************************************************************************/

/******************************************************************************/
GtkWidget* PlayerControl::setup()
/******************************************************************************/
{
	bool homogeneous = false;
	unsigned int spacing = 0;
	unsigned int borderwidth=0;
	bool expand = true;
	bool fill = true;
	unsigned int padding = 0;

	// äußere VBox anlegen
	GtkWidget* box=_gtk_vbox_new(homogeneous,spacing);
	gtk_widget_show(box);

	// Randbreite
	gtk_container_set_border_width(GTK_CONTAINER(box),borderwidth);

	// Konfiguriere PackStart

	// obere HBox anlegen
	GtkWidget* hbox=_gtk_hbox_new(homogeneous,spacing);
	gtk_widget_show(hbox);

	// Randbreite
	gtk_container_set_border_width(GTK_CONTAINER(hbox),borderwidth);

	// StartButton mit Child-Widget erzeugen und anzeigen
	startbutton=gtk_button_new_with_label ("Start");
	gtk_widget_show(startbutton);

	// Callback
	g_signal_connect(G_OBJECT(startbutton),"clicked",G_CALLBACK(startclicked),this);
	// Packe
	gtk_box_pack_start(GTK_BOX(hbox),startbutton,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(startbutton),"style-set",G_CALLBACK(styleset),hbox);

	// PauseButton mit Child-Widget erzeugen und anzeigen
	GtkWidget* pausebutton=gtk_button_new_with_label ("Pause");
	gtk_widget_show(pausebutton);
	// Callback
	g_signal_connect(G_OBJECT(pausebutton),"clicked",G_CALLBACK(pauseclicked),this);
	// Packe
	gtk_box_pack_start(GTK_BOX(hbox),pausebutton,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(pausebutton),"style-set",G_CALLBACK(styleset),hbox);


	// BackwardButton mit Child-Widget erzeugen und anzeigen
	GtkWidget* backwardbutton=gtk_button_new_with_label ("Zurueck");
	gtk_widget_show(backwardbutton);
	// Callback
	g_signal_connect(G_OBJECT(backwardbutton),"clicked",G_CALLBACK(backwardclicked),this);
	// Packe
	gtk_box_pack_start(GTK_BOX(hbox),backwardbutton,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(backwardbutton),"style-set",G_CALLBACK(styleset),hbox);
	/* TODO */
	

	// ForwardButton mit Child-Widget erzeugen und anzeigen
	GtkWidget* forwardbutton=gtk_button_new_with_label ("Vor");
	gtk_widget_show(forwardbutton);
	// Callback
	g_signal_connect(G_OBJECT(forwardbutton),"clicked",G_CALLBACK(forwardclicked),this);
	// Packe
	gtk_box_pack_start(GTK_BOX(hbox),forwardbutton,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(forwardbutton),"style-set",G_CALLBACK(styleset),hbox);
	/* TODO */
	
	// Label fuer Factor
	factorlabel =gtk_label_new("Factor: ");
	gtk_widget_show(factorlabel);
	// Packe
	gtk_box_pack_start(GTK_BOX(hbox),factorlabel,expand,fill,padding);
	setFactorLabel();

	// Packe VBox in HBox
	gtk_box_pack_start(GTK_BOX(box),hbox,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(hbox),"style-set",G_CALLBACK(styleset),box);

	// Scale anlegen
	// Adjustment mit aktuellem Wert
  GtkAdjustment* adj=gtk_adjustment_new(startZeit,startZeit,endZeit,0.001,0.01,0.0);

	// Schieber horizontal oder vertical
	scale=_gtk_hscale_new(GTK_ADJUSTMENT(adj));
	// Stellen, Wert anzeigen
	gtk_scale_set_digits(GTK_SCALE(scale),4);
	gtk_scale_set_draw_value(GTK_SCALE(scale),TRUE);
	// Widget anzeigen
	gtk_widget_show(scale);

	// Packe Scale in HBox 
	gtk_box_pack_end(GTK_BOX(box),scale,expand,fill,padding);
	// Verbinde mit Style-Set-Callback
	g_signal_connect(G_OBJECT(scale),"style-set",G_CALLBACK(styleset),box);

	// Return oberstes Widget (box)
	return box;
}
/******************************************************************************/


/******************************************************************************/
void PlayerControl::styleset(GtkWidget* widget, GtkStyle* previous_style,
								   GtkWidget* parent)
/******************************************************************************/
{
	gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::startclicked(GtkWidget* button, PlayerControl* b)
/******************************************************************************/
{
	if (b->play)
	{
		b->play = false;
		gtk_button_set_label ((GtkButton *)button ,"Start");
		b->reset();
	}
	else
	{
		b->play = true;
		gtk_button_set_label ((GtkButton *)button ,"Stop");
	}
	if(b->onStart.valid()) b->onStart->Exec();
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::pauseclicked(GtkWidget* button, PlayerControl* b)
/******************************************************************************/
{
	// Pause function 
	/* TODO */
	if (!b->play) return;
	
	b->play = false;
	gtk_button_set_label((GtkButton*)b->startbutton,"Weiter");
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::forwardclicked(GtkWidget* button, PlayerControl* b)
/******************************************************************************/
{
	// factor ++
	/* TODO */
	b->factor = b->factor + 1;
	if(b->factor==0) b->factor++;
    // Factorlabel neu setzen
	b->setFactorLabel();
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::backwardclicked(GtkWidget* button, PlayerControl* b)
/******************************************************************************/
{
	// factor --
	/* TODO */
	b->factor = b->factor - 1;
	if(b->factor==0) b->factor--;
	b->setFactorLabel();
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::reset()
/******************************************************************************/
{
	// Zeit auf Startwert setzen
	time = startZeit;
	factor = 1;
	if (scale) gtk_range_set_value(GTK_RANGE(scale),time);
	setFactorLabel();
}
/******************************************************************************/

/******************************************************************************/
void PlayerControl::setFactorLabel()
/******************************************************************************/
{
	gtk_label_set_text((GtkLabel*)factorlabel,std::string("Factor: " + str(factor)).c_str());
}
/******************************************************************************/
