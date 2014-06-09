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


#ifdef WIN32
  #pragma warning(disable: 4996)
  #include <io.h>
  #include <fcntl.h>
#endif

#include "sarturis/base/os.h"
#include "sarturis/apps/thread.h"
#include "sarturis/gtk/application.h"
using namespace sarturis;


/******************************************************************************/
gtk::Application::Application():test_run(false),
                                quit_flag(false),
                                return_value(0),
                                foreign_exception(0),
                                lock(new Mutex)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
gtk::Application::~Application()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void gtk::Application::quit(int ReturnValue)
/******************************************************************************/
{
  // Setze Flag
  lock->Lock();
  quit_flag=true;
  return_value=ReturnValue;
  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
void gtk::Application::display_error(Exception& E)
/******************************************************************************/
{
  // foreign_exception nutzen, auch wenn aus Haupt-Thread geworfen wurde
  lock->Lock();
  if (!foreign_exception) foreign_exception=new ExceptionCopy(E);
  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
int gtk::Application::run_app()
/******************************************************************************/
{
  // Anwendung erstellen
  create_app();

  // Timeout fuer checker
  g_timeout_add(40,(GSourceFunc)checker,this);

  // gtk_main und Anwendung beenden
  gtk_main();
  shutdown_app();

  // return
  return return_value;
}
/******************************************************************************/


/******************************************************************************/
gboolean gtk::Application::checker(gtk::Application* app)
/******************************************************************************/
{
  // Sperren
  app->lock->Lock();

  // Beenden
  if (app->quit_flag)
  {
    // Erst mal die foreign_exception behandlen
    if (!app->foreign_exception)
    {
      app->lock->Unlock();
      gtk_main_quit();
      return FALSE;
    }
  }

  // Exception
  if (app->foreign_exception)
  {
    // kritischen Abschnitt verlassen
    app->lock->Unlock();

    // Kopie der Exception erstellen
    ExceptionCopy e(*(app->foreign_exception));

    // foreign_exception entfernen
    delete app->foreign_exception;
    app->foreign_exception=0;

    // Kopierte Exception werfen
    throw e;
  }

  // Freigeben und weiter testen
  app->lock->Unlock();
  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
void gtk::Application::display_error_handler(Exception& E)
/******************************************************************************/
{
  // Wenn wir eine Konsole haben, dann darauf ausgeben
  if (OS::HasConsole() || test_run) display_error_console(E);

  // Wenn wir ein Display haben, dann im Fenster ausgeben
  else if (Base::Display()) display_error_dialog(E);

  // Wir haben keine Konsole und auch kein Display - dumm gelaufen,
  // aber vielleicht wird stderr ja umgeleitet
  else display_error_console(E);
}
/******************************************************************************/


/******************************************************************************/
void gtk::Application::display_error_console(Exception& E)
/******************************************************************************/
{
  // Benutze geerbte Application-Methode
  sarturis::Application::display_error(E);
}
/******************************************************************************/


/******************************************************************************/
void gtk::Application::display_error_dialog(Exception& E)
/******************************************************************************/
{
  Base::ErrorDialog(E.GetName(),E.ToString());
}
/******************************************************************************/


/******************************************************************************/
gtk::Application::ExceptionCopy::ExceptionCopy(Exception& E):Exception(E),
                                                             name(E.GetName()),
                                                             msg(E.ToString())
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
std::string gtk::Application::ExceptionCopy::GetName()
/******************************************************************************/
{
  return name;
}
/******************************************************************************/


/******************************************************************************/
std::string gtk::Application::ExceptionCopy::ToString()
/******************************************************************************/
{
  return msg;
}
/******************************************************************************/
