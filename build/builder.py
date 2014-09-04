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
from mercurial import Mercurial
from cmake import CMake
from rpmbuilder import RPMBuilder
from options import Options


class Builder(object):
  def __init__(self, package, srcdir, repodir, version, options = Options()):
    object.__init__(self)

    self.package    = package
    self.srcdir     = os.path.join(srcdir, 'src', package)
    self.builddir   = os.path.join(srcdir, 'build', package)
    self.installdir = os.path.join(srcdir, 'install')
    self.repodir    = os.path.join(repodir, package)
    self.version    = version
    self.options    = options

  def build(self, first = None):
    print self.package
    print '---------------------'
    print ''

    if first is None:
      first = not os.path.isdir(self.srcdir)

    if first:
      self.make_dirs()
      self.clone()
    else:
      self.pull()

    self.install()


  def make_dirs(self):
    try:
      os.makedirs(os.path.split(self.srcdir)[0])
    except OSError:
      pass

    try:
      os.makedirs(self.builddir)
    except OSError:
      pass
 

  def clone(self):
      _hg = Mercurial(self.srcdir)
      _hg.clone(self.repodir)


  def pull(self):
      _hg = Mercurial(self.srcdir)
      _hg.pull()


  def install(self):
      _cm = CMake(self.srcdir, self.installdir, self.builddir, options = self.options)
      _cm.options.path('SARTURIS_PREFIX', self.installdir)
      _cm.options.string('SARTURIS_MODULE_VERSION_MAJOR', self.version[0])
      _cm.options.string('SARTURIS_MODULE_VERSION_MINOR', self.version[1])
      _cm.options.string('SARTURIS_MODULE_VERSION_PATCH', self.version[2])      
      _cm.configure()
      _cm.make()
      _cm.install()


  def createRPM(self):
      _hg = Mercurial(self.srcdir)
      _rb = RPMBuilder(self.package, self.version, _hg.changeset(), self.srcdir, self.builddir , self.installdir)
      _rb.build()

