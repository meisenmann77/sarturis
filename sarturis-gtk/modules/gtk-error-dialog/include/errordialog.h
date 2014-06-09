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


#ifndef __ERRORDIALOG__
#define __ERRORDIALOG__

#include <gtk/gtk.h>
#include <string>
#include "sarturis/base/referenced.h"
#include "sarturis/base/logger.h"
#include "sarturis/gtk/base.h"

/******************************************************************************/
namespace sarturis
{
  class ErrorDialog : public Referenced, public gtk::Base
  {
    public:
      // Konstruktor
      ErrorDialog();

      // Anzeigen
      void Show(const std::string& Caption, const std::string& ErrorMessage,
                bool SarturisThrow, const Referenced* Object,
                const std::string& Filename, unsigned int LineNumber);

    protected:
      // Destruktor
      ~ErrorDialog();

    private:
      // Widgets
      GtkWidget* dialog;
      GtkWidget* cb_info;
      GtkWidget* cb_warning;
      GtkWidget* cb_error;

      // Events
      std::vector<Logger::event> events;

      // Liste
      GtkListStore* liststore;

      // Liste aufbauen
      void update_list();
      bool filter(const Logger::event& e);

      // Helfer
      void setup_source_expander(bool SarturisThrow, const Referenced* Object,
                                 const std::string& Filename,
                                 unsigned int LineNumber);
      void setup_logging_expander();

      // Callback fuer Check-Buttons
      static void oncheck(GtkButton* btn, ErrorDialog* e);

      // Callback fuer Save-Button
      static void onsave(GtkButton* btn, ErrorDialog* e);
  };
}
/******************************************************************************/

#endif
