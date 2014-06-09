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


#ifndef __SARTURIS_GTK_GTKAPPLICATION__
#define __SARTURIS_GTK_GTKAPPLICATION__

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include "sarturis/apps/application.h"
#include "sarturis/base/mutex.h"
#include "export.h"
#include "base.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DLLIMPORT Application : public sarturis::Application, public Base
    {
      public:
        // Konstruktor
        Application();

      protected:
        // Destruktor
        virtual ~Application();

        // Quit
        virtual void quit(int ReturnValue=0);

        // Fehlerausgabe
        virtual void display_error(Exception& E);
        virtual void display_error_console(Exception& E);
        virtual void display_error_dialog(Exception& E);
        void display_error_handler(Exception& E);

        // Flags
        bool test_run;
        bool quit_flag;

      private:
        // run_app (split into create_app, Main-Loop and shutdown_app)
        int run_app();
        virtual void create_app()=0;
        virtual void shutdown_app()=0;

        // Rueckgabe-Wert
        int return_value;

        // Exception aus anderen Threads und Klasse fuer Kopie
        Exception* foreign_exception;
        class ExceptionCopy : public Exception
        {
          public:
            ExceptionCopy(Exception& E);
            std::string GetName();
            std::string ToString();

          private:
            std::string name;
            std::string msg;
        };

        // Mutex
        sarturis::ref<Mutex> lock;

        // Test, ob Anwendung beendet wurde oder Fehler da ist
        static gboolean checker(Application* app);
    };
  }
}
/******************************************************************************/

#endif
