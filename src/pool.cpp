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
 
// svncpp
#include "pool.h"


namespace svn
{
   bool Pool::s_initialized = false;

  apr_pool_t *
  Pool::pool_create (apr_pool_t * parent)
  {
    if (!s_initialized) {
        apr_pool_initialize();
        s_initialized=true;
    }
    return svn_pool_create (parent);
  }

  Pool::Pool (apr_pool_t * parent)
    : m_parent (parent), m_pool (pool_create (parent))
  {
  }

  Pool::~Pool ()
  {
    if(m_pool)
    {
        svn_pool_destroy (m_pool);
    }
  }

  apr_pool_t *
  Pool::pool () const
  {
    return m_pool;
  }

  void
  Pool::renew ()
  {
    if (m_pool)
    {
      svn_pool_destroy (m_pool);
    }
    m_pool = pool_create (m_parent);
  }
}
