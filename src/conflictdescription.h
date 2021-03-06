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
 
#ifndef SVNCONFLICTDESCRIPTION_H
#define SVNCONFLICTDESCRIPTION_H

struct svn_wc_conflict_description_t;

#include "svnqt_global.h"
#include "pool.h"
#include <subversion-1/svn_types.h>

#include <qstring.h>

namespace svn {

/** Wrapper for svn_wc_conflict_description_t
 * does nothing when build against subversion prior 1.5
 * @since subversion 1.5
 * @author Rajko Albrecht (ral@alwins-world.de)
*/
class SVNQT_EXPORT ConflictDescription
{
public:
    enum ConflictType {
        ConflictText,
        ConflictProperty,
        ConflictTree
    };
    enum ConflictReason {
        ReasonEdited,
        ReasonObstructed,
        ReasonDeleted,
        ReasonMissing,
        ReasonUnversioned,
        ReasonAdded
    };
    enum ConflictAction {
        ConflictEdit,
        ConflictAdd,
        ConflictDelete
    };
    ConflictDescription();
    ConflictDescription(const svn_wc_conflict_description_t*);
    ~ConflictDescription();

    ConflictAction action() const;
    ConflictType Type() const;
    ConflictReason reason() const;
    svn_node_kind_t nodeKind() const;
    bool binary() const;
    const QString& baseFile() const;
    const QString& theirFile() const;
    const QString& propertyName() const;
    const QString& Path() const;
    const QString& myFile() const;
    const QString& mimeType() const;
    const QString& mergedFile() const;

protected:
    //! don't use it.
    ConflictDescription(const ConflictDescription&);
    void init();
protected:
    Pool m_pool;
    bool m_binary;
    ConflictAction m_action;
    ConflictType m_Type;
    ConflictReason m_reason;
    QString m_baseFile;
    QString m_mergedFile;
    QString m_mimeType;
    QString m_myFile;
    QString m_Path;
    QString m_propertyName;
    QString m_theirFile;
    svn_node_kind_t m_nodeKind;
};

}

#endif
