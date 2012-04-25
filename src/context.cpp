/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
// Apache Portable Runtime
#include <apr_xlate.h>

// Subversion api
#include <subversion-1/svn_auth.h>
#include <subversion-1/svn_config.h>
#include <subversion-1/svn_subst.h>
//#include <subversion-1/svn_utf.h>

// svncpp
#include <apr_general.h>
#include "context.h"
#include "context_listener.h"
#include "contextdata.h"

namespace svn
{
  Context::Context (const QString &configDir)
    : ref_count()
  {
    m = new ContextData (configDir);
  }

  Context::Context (const Context & src)
    : ref_count()
  {
    m = new ContextData (src.m->configDir());
    setLogin (src.getUsername (), src.getPassword ());
  }

  Context::~Context ()
  {
    delete m;
  }

  void
  Context::setAuthCache (bool value)
  {
    m->setAuthCache (value);
  }

  void
  Context::setLogin (const QString& username, const QString& password)
  {
    m->setLogin (username, password);
  }

  Context::operator svn_client_ctx_t * ()const
  {
    return m->ctx();
  }

  svn_client_ctx_t *
  Context::ctx ()const
  {
    return m->ctx();
  }

  void
  Context::setLogMessage (const QString& msg)
  {
    m->setLogMessage (msg);
  }

  const QString&
  Context::getUsername () const
  {
    return m->getUsername ();
  }

  const QString&
  Context::getPassword () const
  {
    return m->getPassword ();
  }

  const QString&
  Context::getLogMessage () const
  {
    return m->getLogMessage ();
  }

  void
  Context::setListener (ContextListener * listener)
  {
    m->setListener(listener);
  }

  ContextListener *
  Context::getListener () const
  {
    return m->getListener();
  }

  void
  Context::reset ()
  {
    m->reset();
  }

  bool Context::contextAddListItem(DirEntries*entries, const svn_dirent_t*dirent,const svn_lock_t*lock,const QString&path)
  {
    return m->contextAddListItem(entries,dirent,lock,path);
  }
}
