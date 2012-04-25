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
 
#ifndef SVNQT_POOL_H
#define SVNQT_POOL_H

#include "svnqt_global.h"

// subversion api
#include <subversion-1/svn_pools.h>


namespace svn
{
  /**
   * Class for encapsulation of apr/subversion pools
   */
  class Pool
  {
  public:
    /**
     * creates a subpool new pool to an existing pool
     *
     * @param parent NULL -> global pool
     */
    Pool (apr_pool_t * parent = (apr_pool_t *)0);

    virtual ~ Pool ();

    /**
     * @return apr handle to the pool
     */
    apr_pool_t *
    pool () const;

    /**
     * operator to return apr handle to the pool
     */
    operator apr_pool_t * () const
    {
      return m_pool;
    }

    /**
     * release pool and create a new one
     */
    void renew ();
  private:
    apr_pool_t * m_parent;
    apr_pool_t * m_pool;

    Pool& operator=(const Pool&);

    Pool (const Pool &);

    static bool s_initialized;
    static apr_pool_t * pool_create (apr_pool_t * parent);
  };
}

#endif
