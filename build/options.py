'''

   Sarturis is (C) Copyright 2006-2011 by Dresden University of Technology

   This software is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this software; if not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

'''


class Options(object):
  def __init__(self):
    object.__init__(self)

    self.cmdline = ''
    self.file    = lambda o, v: self.append('FILEPATH', o, v)
    self.path    = lambda o, v: self.append('PATH'    , o, v)
    self.string  = lambda o, v: self.append('STRING'  , o, v)
    self.boolean = lambda o, v: self.append('BOOL'    , o, v)

    
  def append(self, t, o, v):
    self.cmdline +=' -D%s:%s=%s' % (o, t, v)
