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
 
#ifndef SVNQT_DIRENT_H
#define SVNQT_DIRENT_H

#include "lock_entry.h"
#include "datetime.h"

// subversion api
#include "svnqt_global.h"
#include <subversion-1/svn_client.h>

#include <qstring.h>

namespace svn
{
  class DirEntry_Data;

  class SVNQT_EXPORT DirEntry
  {
  public:
    /**
     * default constructor
     */
    DirEntry ();

    /**
     * constructor for existing @a svn_dirent_t entries
     */
    DirEntry (const QString& name, const svn_dirent_t * dirEntry);
    /**
     * constructor for existing @a svn_dirent_t entries
     */
    DirEntry (const QString& name, const svn_dirent_t * dirEntry,const svn_lock_t*lockEntry);

    DirEntry (const QString& name, const svn_dirent_t * dirEntry,const LockEntry&lockEntry);
    /**
     * copy constructor
     */
    DirEntry (const DirEntry & src);

    /**
     * destructor
     */
    ~DirEntry ();

    /**
     * assignment operator
     */
    DirEntry &
    operator = (const DirEntry &);

    const QString&
    name () const;

    svn_node_kind_t
    kind () const;

    bool isDir()const;

    qlonglong
    size () const;

    bool
    hasProps () const;

    svn_revnum_t
    createdRev () const;

    const DateTime&
    time () const;

    const QString&
    lastAuthor () const;

    //! The assigned lock entry
    /*!
     * returns the assigned lock entry if set
     * \return a valid or an empty lock
     */
    const LockEntry&
    lockEntry() const;

    //! initialize and convert the internal lock entry
    /*!
     * This method should not needed to call outside the lib, it may just used
     * inside svn::Client::ls.
     * \param aLock the subversion lock description to convert.
     */
    void
    setLock(const svn_lock_t*aLock);


  private:
    DirEntry_Data * m;

  };
}

#endif
