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
  #pragma warning(disable: 4251)
#endif

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <math.h>
#include "sarturis/base/generalexception.h"
#include "include/mapterrain.h"
using namespace sarturis;

/******************************************************************************/
HeightmapTerrain::HeightmapTerrain(const std::string& Filename,
                                   const Vector3& Min, const Vector3& Max, double Mue):
                    values(0),mue(Mue)
/******************************************************************************/
{
  load(Filename,Min,Max);
}
/******************************************************************************/


/******************************************************************************/
HeightmapTerrain::~HeightmapTerrain()
/******************************************************************************/
{
  free_values();
}
/******************************************************************************/


/******************************************************************************/
sarturis::ref<Terrain> HeightmapTerrain::CreateInterface()
/******************************************************************************/
{
  return new MapTerrain(this,mue);
}
/******************************************************************************/


/******************************************************************************/
double HeightmapTerrain::lookup_db(const double& X,const double& Y, double* a_eb,
                                   double* b_eb)
/******************************************************************************/
{
  // Index in X und Y
  int id_x=(int)floor((X-_min(0))/scale(0));
  int id_y=(int)floor((Y-_min(1))/scale(1));

  // Limits testen
  if (id_x<0) id_x=0; if (id_x>columns-2) id_x=columns-2;
  if (id_y<0) id_y=0; if (id_y>rows-2) id_y=rows-2;

  // Berechne lokales X und Y in der Zelle
  const double x=X-(double)id_x*scale(0);
  const double y=Y-(double)id_y*scale(1);

  // Ebenen-Koeffizienten
  double a,b,c;

  // Welches Dreieck
  if (y>x)
  {
    // Links oben
    c=values[id_x][id_y];
    b=(values[id_x][id_y+1]-c)/scale(1);
    a=(values[id_x+1][id_y+1]-b*scale(1)-c)/scale(0);
  }
  else
  {
    // Rechts unten
    c=values[id_x][id_y];
    a=(values[id_x+1][id_y]-c)/scale(0);
    b=(values[id_x+1][id_y+1]-a*scale(0)-c)/scale(1);
  }

  // Koeffizienten
  if (a_eb) *a_eb=a;
  if (b_eb) *b_eb=b;

  // return
  return a*x+b*y+c;
}
/******************************************************************************/


/******************************************************************************/
void HeightmapTerrain::load(const std::string& Filename, const Vector3& Min,
                            const Vector3& Max)
/******************************************************************************/
{
  // Erst mal freigeben
  free_values();

  // min und max uebernehmen
  _min=Min;
  _max=Max;

  // GTK initialisieren und Bild laden
  Base::Init();
  GError* err=0;
  GdkPixbuf* pb=gdk_pixbuf_new_from_file(Filename.c_str(),&err);
  if (!pb)
  {
    // Fehlermeldung kopieren und Speicher freigeben
    std::string e(err->message);
    g_error_free(err);

    // Exception werfen
    SARTURIS_THROW(GeneralException(e));
  }

  // Zeilen und Spalten
  columns=gdk_pixbuf_get_width(pb);
  rows=gdk_pixbuf_get_height(pb);

  // mind. 2 Spalten und Zeilen
  if (columns<2) SARTURIS_THROW(GeneralException("Map hat zuwenig Spalten"));
  if (rows<2) SARTURIS_THROW(GeneralException("Map hat zuwenig Zeilen"));

  // Skalierung
  scale(0)=(Max(0)-Min(0))/(double)columns;
  scale(1)=(Max(1)-Min(1))/(double)rows;
  scale(2)=(Max(2)-Min(2))/pow(2.0,gdk_pixbuf_get_bits_per_sample(pb));

  // Bild-Info
  const unsigned int nc=gdk_pixbuf_get_n_channels(pb);
  const unsigned int rs=gdk_pixbuf_get_rowstride(pb);

  // Z-Werte anlegen und ausrechnen
  values=new double*[columns];
  for (int i=0;i<columns;++i)
  {
    values[i]=new double[rows];
    for (int j=0;j<rows;++j)
    {
      // FIXME: regard bits per sample
      const guchar* p=gdk_pixbuf_get_pixels(pb)+(rows-j-1)*rs+i*nc;
      values[i][j]=_min(2)+(double)p[0]*scale(2);
    }
  }

  // Bild freigeben
  g_object_unref(pb);
}
/******************************************************************************/


/******************************************************************************/
void HeightmapTerrain::free_values()
/******************************************************************************/
{
  // Daten freigeben
  if (values)
  {
    for (int i=0;i<columns;++i) delete [] values[i];
    delete [] values;
  }
  values=0;
}
/******************************************************************************/


/******************************************************************************/
HeightmapTerrain::
  MapTerrain::MapTerrain(sarturis::ref<HeightmapTerrain> G,double Mue):geom(G),terrainmue(Mue)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
HeightmapTerrain::MapTerrain::~MapTerrain()
/******************************************************************************/
{

}
/******************************************************************************/


/******************************************************************************/
bool HeightmapTerrain::MapTerrain::GetAltitude(const double& X, const double& Y, const double& Z,
                                               double& height, double& mue)
/******************************************************************************/
{
  mue = terrainmue;
  height = geom->lookup_db(X,Y);
  return true;
}
/******************************************************************************/


/******************************************************************************/
const Vector3& HeightmapTerrain::MapTerrain::GetAltitudeAndDerivatives(const double& X,
                                                                       const double& Y)
/******************************************************************************/
{
  ret(0)=geom->lookup_db(X,Y,&(ret(1)),&(ret(2)));
  return ret;
}
/******************************************************************************/


/******************************************************************************/
const Vector3& HeightmapTerrain::MapTerrain::GetMin() const
/******************************************************************************/
{
  return geom->_min;
}
/******************************************************************************/


/******************************************************************************/
const Vector3& HeightmapTerrain::MapTerrain::GetMax() const
/******************************************************************************/
{
  return geom->_max;
}
/******************************************************************************/
