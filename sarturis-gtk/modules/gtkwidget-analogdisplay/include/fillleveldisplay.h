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
 * fillleveldisplay.h
 *
 *  Created on: 05.12.2011
 *      Author: marcus
 */

#ifndef FILLLEVELDISPLAY_H_
#define FILLLEVELDISPLAY_H_

#include <string>
#include <math.h>
#include "cairowidget.h"
#include "sarturis/common/str.h"
#include "sarturis/interface/analoginput.h"

/******************************************************************************/
namespace sarturis
{
	namespace gtk
	{
		/***
		 * Die Klasse FillLevelDisplay erstellt eine Zeichnung einer
		 * Füllstandsanzeige, die in vielerlei Hinsicht konfigurierbar ist.
		 * Folgende Parameter können frei gewählt werden:
		 *
		 * minValue - der minimale Wert, der ganz am unteren Rand angezeigt
		 *            werden soll
		 * maxValue - der maximale Wert, der ganz am oberen Rand angezeigt
		 *            werden soll
		 * steps - Wie viele Einteilungen angezeigt werden sollen
		 * caption - Ein Text, der um 90 Grad nach links gedreht links neben
		 *           der Füllstandsanzeige angezeigt werden soll
		 */
		class FillLevelDisplay: public CairoWidget
		{
			//TODO: Schriftgroesse mit angeben
			public:
				FillLevelDisplay(sarturis::ref<AnalogInput> analogInput,
						double minValue, double maxValue, int steps,
						std::string caption);

				void Update();

			protected:
				~FillLevelDisplay();
				void Draw(cairo_t* cr);

			private:
				sarturis::ref<AnalogInput> analoginput;
				double lastInputValue;
				double minValue;
				double maxValue;
				int steps;
				std::string caption;

				cairo_text_extents_t CalculateMaxFontSize(cairo_t* cr, int width,
						int height, int minFontSize, int maxFontSize,
						const char* text, double* calculatedFontSize);
		};
	}
}
/******************************************************************************/

#endif /* FILLLEVELDISPLAY_H_ */
