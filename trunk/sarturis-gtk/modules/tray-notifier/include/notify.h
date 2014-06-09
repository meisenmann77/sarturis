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

#ifdef WIN32
  #include <windows.h>
#endif

#include <gdk/gdk.h>
#include <string>


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Notify
    {
      public:
        // Konstruktur und Destruktor
        Notify(GdkPixbuf* Icon);
        ~Notify();

        // Anzeige der Balloon-Nachricht
        void Balloon(const std::string& Title, const std::string& Info);

      private:
        // Anzahl
        static int cnt;

        #ifdef WIN32
          // Windows, merke id (generiert aus Anzahl) und Icon
          int id;
          HICON icon;
        #else
          // Linux, merke Icon anders
          GdkPixbuf* icon;
        #endif
    };
  }
}
/******************************************************************************/

#endif // __NOTIFY__
