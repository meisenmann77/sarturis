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


#include "sarturis/base/generalexception.h"
#include "include/sizegroup.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
SizeGroup::SizeGroup(const std::vector<sarturis::ref<Widget> >& Children,
                     const std::string& Orientation):
             children(Children)
/******************************************************************************/
{
  // Orientierung
  GtkSizeGroupMode mode=GTK_SIZE_GROUP_NONE;
  if (Orientation=="Horizontal") mode=GTK_SIZE_GROUP_HORIZONTAL;
  else if (Orientation=="Vertical") mode=GTK_SIZE_GROUP_VERTICAL;
  else if (Orientation=="Both") mode=GTK_SIZE_GROUP_BOTH;
  else if (Orientation=="None") mode=GTK_SIZE_GROUP_NONE;
  else SARTURIS_THROW(GeneralException("Unbekannte Orientierung "+Orientation));

  // Size-Group
  size_group=gtk_size_group_new(mode);

  // Elemente
  for (unsigned int i=0;i<children.size();++i)
    gtk_size_group_add_widget(size_group,children[i]->GetWidget());
}
/******************************************************************************/


/******************************************************************************/
SizeGroup::~SizeGroup()
/******************************************************************************/
{
}
/******************************************************************************/
