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


from executor import Executor
import os


class Mercurial(Executor):
  def __init__(self, repodir ='.'):
    Executor.__init__(self)

    self.repodir  = repodir


  def update(self, changeset = None):
    _cng = ''
    if changeset is not None:
      _cng = ' --rev %s' % changeset

    self.execute('hg', ' update%s' % _cng, self.repodir)


  def pull(self, update = True):
    _arg = ' pull'
    if update:
      _arg += ' --update'

    self.execute('hg', _arg, self.repodir)


  def changeset(self):
    _out, _err = self.execute_return('hg', ' identify --num', self.repodir)
    return _out


  def clone(self, src, update = True):
    _d0, _d1 = os.path.split(self.repodir)

    _up = ''
    if not update:
      _up += '--noupdate'
    
    self.execute('hg', ' clone%s %s %s' % (_up, src, _d1), _d0)

