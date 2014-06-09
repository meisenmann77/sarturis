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


#ifndef __LOGGERWIDGET__
#define __LOGGERWIDGET__

#include "sarturis/gtk/activewidget.h"
#include "sarturis/base/mutex.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class LoggerWidget : public ActiveWidget
    {
      public:
        // Konstruktor
        LoggerWidget();

        // Impl LoggerInterface
        void Info(const std::string& msg);
        void Warning(const std::string& msg);
        void Exception(const std::string& msg);

        // Update
        void Update();

      protected:
        // Destruktor
        ~LoggerWidget();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Ausgabe-Funktion als Hilfe
        void output(const std::string& prefix, GtkTextTag* tag,
                    const std::string& tab, const std::string& msg);

        // Mutex fuer Ausgabe
        sarturis::ref<Mutex> lock;

        // Puffer fuer Nachrichten
        std::vector<std::string> infos;
        std::vector<std::string> warnings;
        std::vector<std::string> exceptions;

        // Widget und Textbuffer
        GtkWidget* textview;
        GtkTextBuffer* buffer;

        // Tags fuer Farbe bei Info, Warning und Exception
        GtkTextTag* tag_info;
        GtkTextTag* tag_warning;
        GtkTextTag* tag_exception;
    };
  }
}
/******************************************************************************/

#endif
