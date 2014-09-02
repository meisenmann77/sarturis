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
from options import Options
from multiprocessing import cpu_count


class CMake(Executor):
  def __init__(self, srcdir, prefix, builddir ='.', buildtype = 'Release', nodev = False):
    Executor.__init__(self)

    self.srcdir    = srcdir
    self.prefix    = prefix
    self.builddir  = builddir
    self.buildtype = buildtype
    self.nodev     = nodev

    self.options  = Options()


  def configure(self):
    _l  = self.options.cmdline
    _l += ' -DCMAKE_BUILD_TYPE=%s' % self.buildtype
    _l += ' -DCMAKE_INSTALL_PREFIX=%s' % self.prefix
    if self.nodev:
      _l += ' -Wno-dev'

    self.execute('cmake', '%s %s' % (_l, self.srcdir), self.builddir)


  def make(self, target = None):
    _l = ' -j %d' % cpu_count()
    if target is not None:
      _l += ' %s' % target

    self.execute('make', _l, self.builddir)


  def install(self):
    self.make('install')
