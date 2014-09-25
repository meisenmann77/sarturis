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


#ifndef __NOTIFY__
#define __NOTIFY__

#include <gdk/gdk.h>
#include <string>

#include "sarturis/base/referenced.h"


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Notify : virtual public Referenced
    {
      public:
        // Methode zum Erzeugen der Implementierung
        static sarturis::ref<Notify> Create(GdkPixbuf* Icon);

        // Anzeige der Balloon-Nachricht
        virtual void Balloon(const std::string& Title,
                             const std::string& Info)=0;

      protected:
        // Konstruktor und Destruktor
        Notify();
        virtual ~Notify();

        // Anzahl
        static int cnt;
    };
  }
}
/******************************************************************************/

#endif // __NOTIFY__
