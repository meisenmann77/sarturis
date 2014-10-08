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


#include "include/listener.h"
using namespace sarturis;
using namespace sarturis::sound;

/******************************************************************************/
Listener::Listener(sarturis::ref<PositionInput> Position,
                    std::vector<sarturis::ref<Sound> > Sounds):
            position(Position),
            sounds(Sounds)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Listener::~Listener()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Listener::Update()
/******************************************************************************/
{
  // Matrix und Vector
  Matrix3x3 m(position->Get().mat);
  Vector3 v(position->Get().vec);

  // Position des Zuhörers
  ALfloat ListenerPos[] = { (float)v(0), (float)v(1), (float)v(2) };
  // Geschwindigkeit der Zuhörers
  ALfloat ListenerVel[] = { 0.0f, 0.0f, 0.0f };

  // 1. at-Vektor
  //Vector3 at = Vector3(1.0,0.0,0.0);
  //at = m * at;	
		
  // 2. Kreuzprodukt (0,0,1) und at (left-Vektor)
  //Vector3 left = Vector3::CrossProduct(Vector3(m(2,0),m(2,1),m(2,2)),at);
  
  // up-Vektor
  //Vector3 up = Vector3::CrossProduct(at,left);
	
  /*std::cout << "\nMatrix" << std::endl;
  std::cout << m(0,0) << " " << m(0,1) << " " << m(0,2) << std::endl;
  std::cout << m(1,0) << " " << m(1,1) << " " << m(1,2) << std::endl;
  std::cout << m(2,0) << " " << m(2,1) << " " << m(2,2) << "\n" << std::endl;*/
	
  /*std::cout << "AT: " << at(0) << " " << at(1) << " " << at(2) << std::endl;
  std::cout << "LEFT: " << left(0) << " " << left(1) << " " << left(2) << std::endl;
  std::cout << "UP: " << up(0) << " " << up(1) << " " << up(2) << std::endl;*/
	
  // Orientierung des Zurhörers (ersten drei Werte = Richtungsvektor, 
  //                             zweiten drei Werte = Obenvektor)
  // ALfloat ListenerOri[] = { at(0), at(1), at(2),  up(0), up(1), up(2) };
	
  ALfloat ListenerOri[] = { (float)m(0,0), (float)m(0,1), (float)m(0,2),
                            (float)m(2,0), (float)m(2,1), (float)m(2,2) };
	
  alListenerfv(AL_POSITION,    ListenerPos);
  alListenerfv(AL_VELOCITY,    ListenerVel);
  alListenerfv(AL_ORIENTATION, ListenerOri);

  // Aktualisiere Sounds
  for (unsigned int i=0;i<sounds.size();++i) sounds[i]->Update();
}
/******************************************************************************/
