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
 *      Author: sebastian
 */

#ifndef CIRCULARDISPLAY_H_
#define CIRCULARDISPLAY_H_

#include "sarturis/common/str.h"
#include "sarturis/base/logger.h"
#include "sarturis/interface/analoginput.h"
#include "cairowidget.h"
#include <math.h>

/******************************************************************************/
namespace sarturis {
	namespace gtk {
		/***
		 * Die Klasse CircularDisplay erstellt eine einem Tacho ähnliche
		 * Zeichnung, die in vielerlei Hinsicht konfigurierbar ist.
		 * Folgende Parameter können frei gewählt werden:
		 *
		 * minValue - der minimale Wert, der am linken Rand angezeigt werden
		 *            soll
		 * maxValue - der maximale Wert, der am rechten Rand angezeigt werden
		 *            soll
		 * expansion - Welchen Winkel der Tacho aufspannen soll
		 * steps - In welchem Abstand die Einteilungen erfolgen sollen
		 * caption - Ein Text, der unter dem Tacho angezeigt werden soll
		 */
		class CircularDisplay : public CairoWidget {
			public:
				CircularDisplay(sarturis::ref<AnalogInput> analogInput,
						double minValue, double maxValue, double expansion,
						double steps, std::string caption);

				void Update();

			protected:
				~CircularDisplay();

			private:
				sarturis::ref<AnalogInput> analoginput;
				double minValue;
				double maxValue;
				double expansion;
				volatile double currentValue;
				double steps;
				std::string caption;
				double lastValue;

				void Draw(cairo_t* cr);
		};
	}
}
/******************************************************************************/

#endif /* CIRCULARDISPLAY_H_ */
