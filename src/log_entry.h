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
 
#ifndef SVNQT_LOG_ENTRY_H
#define SVNQT_LOG_ENTRY_H

#include "datetime.h"
#include "svnqt_global.h"

#include <QString>
#include <QList>

// apr
#include <apr-1/apr_time.h>

// subversion api
#include <subversion-1/svn_types.h>
#include <subversion-1/svn_version.h>

namespace svn
{

  class StringArray;
  class SVNQT_EXPORT LogChangePathEntry
  {
  public:
    LogChangePathEntry (const char *path_,
                        char action_,
                        const char *copyFromPath_,
                        const svn_revnum_t copyFromRevision_);

    LogChangePathEntry (const QString &path_,
                        char action_,
                        const QString &copyFromPath_,
                        const svn_revnum_t copyFromRevision_);

    LogChangePathEntry (const QString &path_,
                        char action_,
                        const QString &copyFromPath_,
                        const svn_revnum_t copyFromRevision_,
                        const QString &copyToPath_,
                        const svn_revnum_t copyToRevision_);

    LogChangePathEntry();

    QString path;
    char action;
    QString copyFromPath;
    //! future use or useful in backends
    QString copyToPath;

    qlonglong copyFromRevision;
    //! future use or useful in backends
    qlonglong copyToRevision;
  };

  typedef QList<LogChangePathEntry> LogChangePathEntries;

  class SVNQT_EXPORT LogEntry
  {
  public:
    LogEntry ();

    LogEntry (const svn_revnum_t revision,
              const char * author,
              const char * date,
              const char * message);
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
    LogEntry(svn_log_entry_t*,const StringArray&excludeList);
#endif
    void setDate(const char*date);

    //! if -1 the entry is a fake entry and not real usable!
    qlonglong revision;
    qlonglong date;
    QString author;
    QString message;
    LogChangePathEntries changedPaths;
    QList<qlonglong> m_MergedInRevisions;
  };
}

SVNQT_EXPORT QDataStream &operator<<(QDataStream&s,const svn::LogEntry&r);
SVNQT_EXPORT QDataStream &operator<<(QDataStream&s,const svn::LogChangePathEntry&r);

SVNQT_EXPORT QDataStream &operator>>(QDataStream&s,svn::LogEntry&r);
SVNQT_EXPORT QDataStream &operator>>(QDataStream&s,svn::LogChangePathEntry&r);

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
