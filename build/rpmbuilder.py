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
import shutil
import sys
from string import Template
from executor import Executor


class RPMBuilder(Executor):
  def __init__(self, package, version, changeset, srcdir, builddir, installdir, prefix = '/usr', rpmbuild = None):
    Executor.__init__(self)

    self.package    = package
    self.version    = version
    self.changeset  = changeset
    self.srcdir     = srcdir
    self.builddir   = builddir
    self.installdir = installdir
    self.prefix     = prefix
    self.rpmbuild   = rpmbuild

    if self.rpmbuild is None:
      self.rpmbuild = os.path.join(os.path.expanduser('~'), 'rpmbuild')

    _arch = 'i386'
    if sys.maxsize > 2**32:
      _arch = 'x86_64'

    self.dist = 'unknown'
    try:
      self.dist = 'fc%s' % open('/etc/fedora-release', 'r').read().split()[2]
    except:
      pass

    self.template  = os.path.join(self.srcdir  ,'common', '%s.spec.template' % package)
    self.specfile  = os.path.join(self.rpmbuild, 'SPECS', '%s.spec' % package)

    _pname = '%s%s-hg%s.%s.%s' % (version[0], version[1], changeset, self.dist, _arch)
    self.buildroot = os.path.join(self.rpmbuild, 'BUILDROOT', '%s-%s' % (package, _pname))


  def build(self):
    _fl = self.file_list()
    self.create_spec(_fl)
    self.create_buildroot(_fl)
    self.create_rpm()


  def create_spec(self, files):
    try:
      os.makedirs(os.path.split(self.specfile)[0])
    except OSError:
      pass

    _files =''
    for _f in sorted(files.keys()):
      _files += '%s\n' % _f

    _subs = {}
    _subs['files']  = _files
    _subs['prefix'] = self.prefix
    _subs['vmajor'] = self.version[0]
    _subs['vminor'] = self.version[1]
    _subs['chgset'] = self.changeset

    _s = file(self.template,'r').read()
    _s = Template(_s).safe_substitute(_subs)
    file(self.specfile, 'w').write(_s)


  def create_buildroot(self, files):
    for _f in files.keys():
      _src = files[_f]
      _dst = os.path.join(self.buildroot, os.path.relpath(_f, '/'))
      try:
        os.makedirs(os.path.split(_dst)[0])
      except OSError:
        pass

      shutil.move(_src, _dst)


  def create_rpm(self):
    self.execute('rpmbuild', ' -ba %s.spec' % self.package, os.path.join(self.rpmbuild, 'SPECS'))


  def file_list(self):
    _ret = {}
    _mft = open(os.path.join(self.builddir, 'install_manifest.txt'), 'r')
    for _f in _mft:
      _f = _f.strip().rstrip()
      _rel = os.path.relpath(_f, self.installdir)
      _ret[os.path.join(self.prefix, _rel)] = _f

    return _ret

