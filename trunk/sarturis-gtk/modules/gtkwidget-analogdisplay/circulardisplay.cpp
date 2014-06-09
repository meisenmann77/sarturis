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
 * fillleveldisplay.cpp
 *
 *  Created on: 06.12.2011
 *      Author: sebastian
 */

#ifdef WIN32
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "include/circulardisplay.h"
using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
CircularDisplay::CircularDisplay(sarturis::ref<AnalogInput> analogInput,
		double minValue, double maxValue, double expansion, double steps,
		std::string caption) :
		analoginput(analogInput), minValue(minValue), maxValue(maxValue),
		expansion(expansion), steps(steps), caption(caption)
/******************************************************************************/
{

}
/******************************************************************************/

/******************************************************************************/
CircularDisplay::~CircularDisplay()
/******************************************************************************/
{

}
/******************************************************************************/

/******************************************************************************/
void CircularDisplay::Update()
/******************************************************************************/
{
	if(analoginput->Get()!=currentValue){
		lastValue = currentValue;
		currentValue = analoginput->Get();
		Invalidate();
	}
}
/******************************************************************************/

/******************************************************************************/
void CircularDisplay::Draw(cairo_t* cr)
/******************************************************************************/
{
	// Height and width of the box we are going to draw in
	int w_height = this->height;
	int w_width = this->width;

	// Min, max, current, steps and caption as specified in the xml
	double minValue = this->minValue;
	double maxValue = this->maxValue;
	double currentValue = this->currentValue;
	double steps = this->steps;
	std::string caption = this->caption;

	// Draw a little Box so we see where we're drawing
	cairo_rectangle(cr, 0, 0, w_width, w_height);
	cairo_stroke(cr);

	// Radius is 90% of the smallest edge
	double radius = 0.9*((w_height<w_width)? w_height: w_width)/2;

	// The range of numbers, that will be displayed
	double range = maxValue-minValue;

	// Length of the needle is 85% of the radius, scale is 10% of the radius
	double length = 0.85*radius;
	double size_scale = 0.1*radius;

	double scaling_factor = expansion/range;

	// Position of the needle as angle
	double position = (-expansion/2)-
			(minValue*scaling_factor)+(currentValue*scaling_factor);

	// Center of the drawing area
	double cx = (w_width/2);
	double cy = (w_height/2);

	// Angles in radian
	double left_radian = (270-(expansion/2)) * (M_PI/180.0);
	double right_radian = (270+(expansion/2)) * (M_PI/180.0);
	double pos_radian = (270+position) * (M_PI/180.0);

	// Warn, if the position of the needle is out of bounds
	if(currentValue<minValue){
		Logger::Warning("Input value ("+str(currentValue)+
				") smaller than minimum Value ("+str(minValue)+")!");
	}else if(currentValue>maxValue){
		Logger::Warning("Input value ("+str(currentValue)+
				") larger than maximum Value ("+str(maxValue)+")!");
	}

	// Outer arc
	cairo_arc(cr, cx, cy, radius, left_radian, right_radian);
	cairo_stroke(cr);

	// Scale + Labels
	double current_value = minValue;
	cairo_set_font_size(cr, 0.1*radius);

	for(int i=0; i<=(range/steps); i++){
		double curr_angle = i*(expansion/(range/steps));
		double curr_radian = (270-(expansion/2)+curr_angle) * (M_PI/180.0);

		// Scale
		cairo_move_to(cr, cx+(radius-size_scale)*cos(curr_radian),
				cy+(radius-size_scale)*sin(curr_radian));
		cairo_line_to(cr, cx+radius*cos(curr_radian),
				cy+radius*sin(curr_radian));
		cairo_stroke(cr);

		//Label
		std::string label = str(current_value);
		cairo_text_extents_t ext;
		cairo_text_extents(cr,label.c_str(),&ext);
		cairo_set_source_rgba(cr,0.5,0.5,0.5,1);
		cairo_move_to(cr, cx+(0.8*radius)*cos(curr_radian)-(ext.width/2),
				cy+(0.8*radius)*sin(curr_radian)+(ext.height/2));
		cairo_show_text(cr, label.c_str());
		current_value += steps;
		cairo_set_source_rgba(cr,0,0,0,1);
	}

	// Needle
	cairo_move_to(cr, cx, cy);
	cairo_line_to(cr, cx+length*cos(pos_radian), cy+length*sin(pos_radian));
	cairo_stroke(cr);

	// Text
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
			CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 0.25*radius);
	cairo_text_extents_t ext;
	cairo_text_extents(cr, caption.c_str(), &ext);
	cairo_move_to(cr, cx-(ext.width/2), w_height*0.9);
	cairo_show_text(cr, caption.c_str());

	cairo_close_path(cr);
}
/******************************************************************************/
