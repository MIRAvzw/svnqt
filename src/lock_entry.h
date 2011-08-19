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
 
#ifndef SVNQT_LOCK_ENTRY_H
#define SVNQT_LOCK_ENTRY_H

#include "datetime.h"

#include <qstring.h>

#include "svnqt_global.h"

// apr
#include <apr_time.h>

// subversion api
#include <subversion-1/svn_types.h>
#include <subversion-1/svn_wc.h>

namespace svn
{
  class SVNQT_EXPORT LockEntry
  {
  public:
    LockEntry ();

    LockEntry (const apr_time_t lock_time,
              const apr_time_t expiration_time,
              const char * lock_owner,
              const char * lock_comment,
              const char * lock_token);

    void init(const svn_wc_entry_t * src);

    void init(const apr_time_t lock_time,
              const apr_time_t expiration_time,
              const char * lock_owner,
              const char * lock_comment,
              const char * lock_token);
    void init(const svn_lock_t*);
    const QString&Comment()const;
    const QString&Owner()const;
    const QString&Token()const;
    const DateTime&Date()const;
    const DateTime&Expiration()const;
    bool Locked()const;

  protected:
    DateTime date;
    DateTime exp;
    QString owner;
    QString comment;
    QString token;
    bool locked;
  };
}

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */

