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


#ifndef __RULER__
#define __RULER__

#include <string>
#include "drawedwidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Ruler : public DrawedWidget
    {
      public:
        // Konstruktor
        Ruler(unsigned int Grid, const std::string& Unit);

        // Setter
        void SetGrid(unsigned int Grid);
        void SetBounds(double Lower, double Upper);

        // Getter
        double GetLower() const;
        double GetUpper() const;

        // Auf Wert einpassen
        bool FitToValue(double* Values, unsigned int Cnt);

        // Reset
        virtual void Reset();

      protected:
        // Destruktor
        virtual ~Ruler();

        // Gitter (0 entspricht keiner zusaetzlichen Linie)
        unsigned int grid;

        // Grenzen
        double lower;
        double upper;

        // Einheit
        std::string unit;

      private:
        unsigned int fitted;
        virtual bool fit_to_value(double value)=0;
    };
  }
}
/******************************************************************************/

#endif
