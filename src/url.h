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
 
#ifndef SVNQT_URL_H
#define SVNQT_URL_H

#include "svnqt_global.h"

#include <QString>

namespace svn
{
  class SVNQT_EXPORT Url
  {
  public:
    /** Constructor */
    Url ();

    /** Destructor */
    virtual ~Url ();

    /**
     * Checks if @a url is valid
     *
     * Example of a valid URL:
     *   http://svn.collab.net/repos/svn
     * Example of an invalid URL:
     *   /home/foo/bar
     */
    static bool
    isValid (const QString& url);

    /**
     * Checks if @a url points to a local filesystem.
     *
     * @return true if url is accessed local without network.
     */
    static bool
    isLocal(const QString& url);

    static QString
    transformProtokoll(const QString&);

  };
}

#endif
