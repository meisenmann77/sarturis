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


#include "sarturis/apps/datamanager.h"
#include "sarturis/base/logger.h"
#include "sarturis/config/source.h"
#include "include/objectmanipulator.h"
using namespace sarturis::gtk;
using namespace sarturis::data;


/******************************************************************************/
ObjectManipulator::ObjectManipulator():
                     mainwidget(new MainWidget),
                     instancetree(mainwidget->GetInstanceTree()),
                     lock(new Mutex)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
ObjectManipulator::~ObjectManipulator()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void ObjectManipulator::Read(sarturis::data::Data& d)
/******************************************************************************/
{
  lock->Lock();

  // Request
  unsigned int id;
  d.Read<unsigned int>(id);

  // In set
  requests.insert(id);

  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
void ObjectManipulator::Write(sarturis::data::Data& d) const
/******************************************************************************/
{
  lock->Lock();

  // Initialisieren
  unsigned int id=0;
  std::string s;

  // set muss Element haben, sonst 0 und leeren string schicken
  if (!requests.empty())
  {
    // Erstes Element und String dazu
    id=*(requests.begin());
    s=instancetree->GetChange(id);

    // erstes Element entfernen, wenn Change vorhanden, sonst id wieder auf 0
    if (s!="") requests.erase(requests.begin()); else id=0;
  }

  // Schreiben
  d.Write<unsigned int>(id);
  d.Write<std::string>(s);

  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* ObjectManipulator::setup()
/******************************************************************************/
{
  // Widget holen - baut alle GTK-Strukturen auf, erst dann koennen
  //                Instanzen hinzugefuegt werden
  GtkWidget* w=mainwidget->GetWidget();

  // Hole globale Config
  sarturis::ref<ConfigSource> cs=
    DataManager::Get("__ALL_CONFIG__").as<ConfigSource>();
  if (!cs) Logger::Warning("No global configuration object available!");
  else
  {
    // Hole Instance-Elemente und addiere dann die Instanzen
    std::vector<Config> v_cfg=cs->GetConfig().GetChildren("Instance",false);
    for (unsigned int i=0;i<v_cfg.size();++i)
    {
      const std::string n=v_cfg[i].GetSingleAttribute<std::string>("Name");
      mainwidget->AddInstance(DataManager::Get(n));
    }
  }

  // Widget zurueckgeben
  return w;
}
/******************************************************************************/
