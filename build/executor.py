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
import shlex
from subprocess import Popen, PIPE


class Executor(object):
  def __init__(self):
    object.__init__(self)


  def execute(self, cmd, arg, dir):
    _cwd = os.getcwd()
    os.chdir(dir)
    os.system('%s%s' % (cmd, arg))
    os.chdir(_cwd)


  def execute_return(self, cmd, arg, dir):
    _exe = shlex.split('%s%s' % (cmd, arg))
    _cwd = os.getcwd()
    os.chdir(dir)
    _prc = Popen(_exe, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    _out, _err = _prc.communicate()
    os.chdir(_cwd)

    return (_out.rstrip().strip(), _err.rstrip().strip())

