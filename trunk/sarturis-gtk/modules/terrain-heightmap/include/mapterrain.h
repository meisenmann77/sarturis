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


#ifndef __MAPGEOMETRY__
#define __MAPGEOMETRY__

#include "sarturis/gtk/base.h"
#include "sarturis/interface/terraingeometry.h"

/******************************************************************************/
namespace sarturis
{
  class HeightmapTerrain : public TerrainGeometry, public gtk::Base
  {
    public:
      // Konstruktor
      HeightmapTerrain(const std::string& Filename, const Vector3& Min,
                       const Vector3& Max, double Mue);

      // Interface erzeugen
      sarturis::ref<Terrain> CreateInterface();

    protected:
      // Destruktor
      ~HeightmapTerrain();

    private:
      // Punkt finden
      double lookup_db(const double& X,const double& Y, double* a_eb=0, double* b_eb=0);

      // Daten lesen
      void load(const std::string& Filename, const Vector3& Min,
                const Vector3& Max);

      // Daten freigeben
      void free_values();

      // Daten
      double** values;
      int columns;
      int rows;

      // Min, Max und Skalierung
      Vector3 _min;
      Vector3 _max;
      Vector3 scale;
	  double mue;
  
      // Klasse fuer Terrain-Interface
      class MapTerrain : public Terrain
      {
        public:
          // Konstruktor
          MapTerrain(sarturis::ref<HeightmapTerrain> G, double Mue);

          // implementierte Funktionen des Interface
          bool GetAltitude(const double& X, const double& Y, const double& Z,
                           double& height, double& mue);

          const Vector3& GetAltitudeAndDerivatives(const double& X, const double& Y);

          // Min und Max
          const Vector3& GetMin() const;
          const Vector3& GetMax() const;

        protected:
          // Destruktor
          ~MapTerrain();

        private:
          // return fuer GetAltitudeAndDerivations
          Vector3 ret;

          // Referenz auf Geometry
          sarturis::ref<HeightmapTerrain> geom;
		  // mue
		  double terrainmue;
      };
  };
}
/******************************************************************************/

#endif
