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


#ifndef __NOTIFYWIN32__
#define __NOTIFYWIN32__

#include <windows.h>
#include "include/notify.h"


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class NotifyWIN32 : public Notify
    {
      public:
        // Konstruktur
        NotifyWIN32(GdkPixbuf* Icon);

        // Anzeige der Balloon-Nachricht
        void Balloon(const std::string& Title, const std::string& Info);

      protected:
        // Destruktor
        ~NotifyWIN32();

      private:
        // id (generiert aus Anzahl) und Icon
        int id;
        HICON icon;
    };
  }
}
/******************************************************************************/

#endif // __NOTIFYWIN32__
