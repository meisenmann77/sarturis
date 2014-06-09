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


#include "sarturis/common/entry.h"
#include "include/gtk-error-dialog-meta.h"
#include "version.h"
using namespace sarturis;


/******************************************************************************/
SARTURIS_ENTRY void __sarturis_module_init__()
/******************************************************************************/
{
  // NOTHING
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY void __sarturis_module_exit__()
/******************************************************************************/
{
  // NOTHING
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY bool __sarturis_module_nodelete__()
/******************************************************************************/
{
  return false;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY const char* __sarturis_module_getname__()
/******************************************************************************/
{
  return MODULE_NAME;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY const char* __sarturis_module_getvendor__()
/******************************************************************************/
{
  return MODULE_VENDOR;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY unsigned int __sarturis_module_getversionmajor__()
/******************************************************************************/
{
  return SARTURIS_VERSION_MAJOR;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY const char*  __sarturis_module_getversionminor__()
/******************************************************************************/
{
  return SARTURIS_VERSION_MINOR;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY const char* __sarturis_module_getversionpatch__()
/******************************************************************************/
{
  return SARTURIS_VERSION_PATCH;
}
/******************************************************************************/


/******************************************************************************/
SARTURIS_ENTRY unsigned int __sarturis_module_getversionrevision__()
/******************************************************************************/
{
  return SARTURIS_VERSION_REVISION;
}
/******************************************************************************/
