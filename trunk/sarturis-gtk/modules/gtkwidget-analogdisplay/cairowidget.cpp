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
 * cairowidget.cpp
 *
 *  Created on: 23.01.2012
 *      Author: marcus, sebastian
 */

#include "include/cairowidget.h"

using namespace sarturis::gtk;

/******************************************************************************/
CairoWidget::CairoWidget(): width(0),height(0)
/******************************************************************************/
{}
/******************************************************************************/

/******************************************************************************/
CairoWidget::~CairoWidget()
/******************************************************************************/
{
	if(cairo_context != NULL)
		cairo_destroy(cairo_context);
}
/******************************************************************************/

/******************************************************************************/
void CairoWidget::Invalidate()
/******************************************************************************/
{
	gtk_widget_queue_draw(GetWidget());
}
/******************************************************************************/

/******************************************************************************/
GtkWidget* CairoWidget::setup()
/******************************************************************************/
{
	GtkWidget* w = gtk_drawing_area_new();
	g_signal_connect(
			G_OBJECT(w), "expose-event", G_CALLBACK (OnExpose), this);
	g_signal_connect(
			G_OBJECT(w),"configure-event",G_CALLBACK(OnConfigure),this);
	gtk_widget_show(w);

	return w;
}
/******************************************************************************/

/******************************************************************************/
gboolean CairoWidget::OnExpose(GtkWidget* widget, GdkEventExpose* e,
		gpointer user_data)
/******************************************************************************/
{
	CairoWidget* cw = (CairoWidget*)user_data;
	cw->cairo_context =
			gdk_cairo_create(gtk_widget_get_window(cw->GetWidget()));
	cw->Draw(cw->cairo_context);

	return TRUE;
}
/******************************************************************************/

/******************************************************************************/
gboolean CairoWidget::OnConfigure(GtkWidget* w, GdkEventConfigure* e,
		gpointer user_data)
/******************************************************************************/
{
	CairoWidget* cw = (CairoWidget*)user_data;
	cw->width = e->width;
	cw->height = e->height;

	return TRUE;
}
/******************************************************************************/
