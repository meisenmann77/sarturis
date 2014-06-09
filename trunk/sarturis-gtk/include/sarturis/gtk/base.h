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


#ifndef __SARTURIS_GTK_BASE__
#define __SARTURIS_GTK_BASE__

#include <string>
#include <gtk/gtk.h>
#include "sarturis/base/exception.h"
#include "export.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DLLIMPORT Base
    {
      public:
        // Initialisieren
        static void Init();

        // Abfrage Display
        static bool Display(bool InitIfNot=true);

        // Exception
        class DLLIMPORT DisplayException : public Exception
        {
          public:
            std::string ToString();
            std::string GetName();
        };

        // GTK-Version
        static int GtkVersion();

      protected:
        // Konstruktor
        Base();

        // Dialoge
        static void InfoDialog(const std::string& Caption,
                               const std::string& Text);
        static void ErrorDialog(const std::string& Caption,
                                const std::string& Message);
        static std::string LoadDialog(const std::string& Caption,
                                      const std::string& Filename="");
        static std::string SaveDialog(const std::string& Caption,
                                      const std::string& Filename="");

        // Pixbuf aus Daten erzeugen
        static GdkPixbuf* Pixbuf(unsigned char* Data, unsigned int Size);

      private:
        // Flags
        static bool init;
        static bool display;
    };
  }
}
/******************************************************************************/

#endif
