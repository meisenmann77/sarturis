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


import os
from builder import Builder
from options import Options


class Project(object):
  def __init__(self, version, builddir = None, repository = None):
    object.__init__(self)

    self.version  = version
    self.packages = []
    self.options  = {}

    self.builddir = builddir
    if self.builddir is None:
      self.builddir = os.path.join(os.path.expanduser('~'), 'sarturis')

    self.repository = repository
    if self.repository is None:
      self.repository = os.path.join(os.path.expanduser('~'), 'Dropbox', 'sarturis', 'devel')


  def package(self, pkg):
    self.packages.append(pkg)
    self.options[pkg] = Options()


  def option(self, pkg):
    return self.options[pkg]


  def build(self):
    for _pkg in self.packages:
      b = Builder(_pkg, self.builddir, self.repository, self.version)
      b.build()

    for _pkg in self.packages:
      b = Builder(_pkg, self.builddir, self.repository, self.version)
      b.createRPM()

