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


#include "sarturis/base/stringparser.h"
#include "include/loggerwidget.h"
using namespace sarturis;
using namespace gtk;

/******************************************************************************/
LoggerWidget::LoggerWidget():lock(new Mutex)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
LoggerWidget::~LoggerWidget()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void LoggerWidget::Info(const std::string& msg)
/******************************************************************************/
{
  // Merken
  lock->Lock();
  infos.push_back(msg);
  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
void LoggerWidget::Warning(const std::string& msg)
/******************************************************************************/
{
  // Merken
  lock->Lock();
  warnings.push_back(msg);
  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
void LoggerWidget::Exception(const std::string& msg)
/******************************************************************************/
{
  // Merken
  lock->Lock();
  exceptions.push_back(msg);
  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
void LoggerWidget::Update()
/******************************************************************************/
{
  lock->Lock();

  // Ausgabe
  for (unsigned int i=0;i<infos.size();++i)
  {
    output("Info",tag_info,"\t\t\t",infos[i]);
  }
  for (unsigned int i=0;i<warnings.size();++i)
  {
    output("Warning",tag_warning,"\t\t",warnings[i]);
  }
  for (unsigned int i=0;i<exceptions.size();++i)
  {
    output("Exception",tag_exception,"\t",exceptions[i]);
  }

  // Puffer leeren
  infos.clear();
  warnings.clear();
  exceptions.clear();

  lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* LoggerWidget::setup()
/******************************************************************************/
{
  // Textbuffer erzeugen
  buffer=gtk_text_buffer_new(0);

  // Textview ohne Zeilenumbruch
  textview=gtk_text_view_new_with_buffer(buffer);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview),GTK_WRAP_NONE);

  // Tags erzeugen
  tag_info=gtk_text_buffer_create_tag(buffer,"green_foreground","foreground",
                                      "green",0); 
  tag_warning=gtk_text_buffer_create_tag(buffer,"yellow_foreground",
                                         "foreground","yellow",0); 
  tag_exception=gtk_text_buffer_create_tag(buffer,"red_foreground",
                                           "foreground","red",0); 

  // Anzeigen und return
  gtk_widget_show(textview);
  return textview;
}
/******************************************************************************/


/******************************************************************************/
void LoggerWidget::output(const std::string& prefix, GtkTextTag* tag,
                          const std::string& tab, const std::string& msg)
/******************************************************************************/
{
  // Hole Text-Laenge fuer Farbe des Prefix
  const int ccount=gtk_text_buffer_get_char_count(buffer);

  // Ausgabe mit \n
  const std::string buf=prefix+":"+tab+
                        StringParser::ReplaceAll(msg,"\n"," ")+'\n';
  gtk_text_buffer_insert_at_cursor(buffer,buf.c_str(),-1);

  // Farbgestaltung
  GtkTextIter iter1,iter2;
  gtk_text_buffer_get_iter_at_offset(buffer,&iter1,ccount);
  gtk_text_buffer_get_iter_at_offset(buffer,&iter2,ccount+prefix.size()+1);
  gtk_text_buffer_apply_tag(buffer,tag,&iter1,&iter2);
}
/******************************************************************************/
