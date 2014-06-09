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
 *      Author: marcus
 */

#ifdef WIN32
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "include/fillleveldisplay.h"
using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
FillLevelDisplay::FillLevelDisplay(sarturis::ref<AnalogInput> analogInput,
		double minValue, double maxValue, int steps, std::string caption) :
		analoginput(analogInput), lastInputValue(0),
		minValue(minValue), maxValue(maxValue), steps(steps), caption(caption)
/******************************************************************************/
{

}
/******************************************************************************/


/******************************************************************************/
FillLevelDisplay::~FillLevelDisplay()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void FillLevelDisplay::Update()
/******************************************************************************/
{
	//Muss neu gezeichnet werden?
	if(lastInputValue != analoginput->Get())
	{
		lastInputValue = analoginput->Get();
		Invalidate();
	}
}
/******************************************************************************/


/******************************************************************************/
cairo_text_extents_t FillLevelDisplay::CalculateMaxFontSize(cairo_t* cr,
		int width, int height, int minFontSize, int maxFontSize,
		const char* text, double* calculatedFontSize)
/******************************************************************************/
{
	bool still_fit = true;
	*calculatedFontSize = minFontSize;
	cairo_text_extents_t ext;

	do
	{
		(*calculatedFontSize)++;
		cairo_set_font_size(cr, (*calculatedFontSize));
		cairo_text_extents(cr, caption.c_str(), &ext);

		if(ext.height > height || ext.width > width)
			still_fit = false;
	}
	while(still_fit && (*calculatedFontSize) <= maxFontSize);

	(*calculatedFontSize)--;
	return ext;
}
/******************************************************************************/


/******************************************************************************/
void FillLevelDisplay::Draw(cairo_t* cr)
/******************************************************************************/
{
	//     20%       40%         40%
	// |<------->|<------->|<----------->|
	// +–––––––––––––––––––––––––––––––––+
	// |       C |         |–            |
	// |       A |   BAR   |             |
	// |       P |         |             |
	// |       T |–––––––––|–   SCALE    |
	// |       I |/////////|             |
	// |       O |/////////|             |
	// |       N |/////////|–            |
	// +–––––––––––––––––––––––––––––––––+

	//Draw border
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_stroke(cr);

	//Constant values
	int capPaddingLeft = 1;
	int captionFontSizeMin = 8;
	int captionFontSizeMax = 40;

	int scaleFontSizeMin = 8;
	int scaleFontSizeMax = 20;

	//Calculate position and size for all necessary controlparts
	int PaddingTop = height * 0.05;
	int PaddingBottom = height * 0.05;

	int capPaddingRight = width * 0.02; //2%
	int caption_max_size_x = width * 0.2 - capPaddingLeft - capPaddingRight;
	int caption_max_size_y = height - PaddingBottom - PaddingTop;
	int caption_width = width * 0.2; //20%
	int bar_width = width * 0.4; //40%
	int bar_height_max = height - PaddingTop - PaddingBottom;
	int bar_height = bar_height_max / (maxValue - minValue) *
			(lastInputValue - minValue);
	int bar_pos_X = width * 0.2; //20%
	int scaleline_width = width * 0.03; //3%
	int scaleText_width = width * 0.37; //37%

	//Draw bar
	cairo_rectangle (cr, bar_pos_X, PaddingTop + (bar_height_max - bar_height),
			bar_width, bar_height);
	cairo_set_source_rgba (cr, 0, 0, 1, 0.40);
	cairo_fill(cr);

	cairo_set_source_rgba (cr, 0, 0, 0, 1);

	cairo_move_to (cr, bar_pos_X, PaddingTop + (bar_height_max - bar_height));
	cairo_line_to (cr, bar_pos_X + bar_width,
			PaddingTop + (bar_height_max - bar_height));

	//Draw border for bar
	cairo_rectangle (cr, bar_pos_X, PaddingTop, bar_width, bar_height_max);
	cairo_stroke(cr);

	//Draw scalelines

		//max value
	cairo_move_to (cr, bar_pos_X + bar_width, PaddingTop);
	cairo_line_to (cr, bar_pos_X + bar_width + scaleline_width, PaddingTop);

		//min value
	cairo_move_to (cr, bar_pos_X + bar_width, PaddingTop + bar_height_max);
	cairo_line_to (cr, bar_pos_X + bar_width + scaleline_width,
			PaddingTop + bar_height_max);

		//others
	for (int i = 1; i < steps - 1; ++i)
	{
		cairo_move_to (cr, bar_pos_X + bar_width, PaddingTop +
				i * ((double)bar_height_max / (double)(steps - 1)));
		cairo_line_to (cr, bar_pos_X + bar_width + scaleline_width,
				PaddingTop + i *
				((double)bar_height_max / (double)(steps - 1)));
		cairo_stroke(cr);
	}

	//Draw Text
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
			CAIRO_FONT_WEIGHT_NORMAL);

		//Draw scale-text
	double scaleFontSize = 0;
	double scaleText_height = bar_height_max / (double)steps;

	if(scaleText_height > PaddingTop * 2)
		scaleText_height = PaddingTop * 2;

	cairo_text_extents_t scaleExt = CalculateMaxFontSize(cr, scaleText_width,
			scaleText_height, scaleFontSizeMin, scaleFontSizeMax,
			caption.c_str(), &scaleFontSize);
	cairo_set_font_size(cr, scaleFontSize);

			//Max value
	cairo_move_to(cr, bar_pos_X + bar_width + scaleline_width,
			PaddingTop + scaleExt.height/2);
	cairo_show_text(cr, str(maxValue).c_str());

			//Min value
	cairo_move_to(cr, bar_pos_X + bar_width + scaleline_width,
			PaddingTop + bar_height_max + scaleExt.height/2);
	cairo_show_text(cr, str(minValue).c_str());

	for (int i = 1; i < steps - 1; ++i)
	{
		cairo_move_to(cr, bar_pos_X + bar_width + scaleline_width,
				PaddingTop + scaleExt.height/2 + i *
				(bar_height_max / (double)(steps - 1)));
		cairo_show_text(cr, str(maxValue - i *
				(maxValue - minValue) / (steps - 1)).c_str());
	}

		//Draw caption-text
	double capFontSize = 0;
	cairo_text_extents_t capExt = CalculateMaxFontSize(cr, caption_max_size_y,
			caption_max_size_x, captionFontSizeMin, captionFontSizeMax,
			caption.c_str(), &capFontSize);
	cairo_set_font_size(cr, capFontSize);

	cairo_move_to(cr, caption_width - capPaddingLeft - capPaddingRight,
			height - (height - capExt.width)/2);
	cairo_rotate (cr, -M_PI/2);
	cairo_show_text(cr, caption.c_str());
}
/******************************************************************************/
