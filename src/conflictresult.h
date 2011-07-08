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
 
#ifndef SVNQT_CONFLICT_RESULT_H
#define SVNQT_CONFLICT_RESULT_H

struct svn_wc_conflict_result_t;

#include "svnqt_global.h"
#include "pool.h"
#include <subversion-1/svn_types.h>

#include <qstring.h>

namespace svn {

class SVNQT_EXPORT ConflictResult
{
    public:
        enum ConflictChoice {
            //! let user make a call to resolve
            ChoosePostpone,
            ChooseBase,
            ChooseTheirsFull,
            ChooseMineFull,
            ChooseTheirsConflict,
            ChooseMineConflict,
            ChooseMerged
        };
        ConflictResult();
        //! Copy constructor
        /*! only useful wenn build with subversion 1.5 or newer
         */
        ConflictResult(const svn_wc_conflict_result_t*);

        const QString& mergedFile()const
        {
            return m_MergedFile;
        }
        void setMergedFile(const QString&aMergedfile);

        ConflictChoice choice()const
        {
            return m_choice;
        }
        void setChoice(ConflictChoice aValue);

        const svn_wc_conflict_result_t*result(const Pool&pool)const;
        void assignResult(svn_wc_conflict_result_t**aResult,const Pool&pool)const;

    protected:
        ConflictChoice m_choice;
        //! Merged file
        /*! will only used if m_choice is ChooseMerged
         */
        QString m_MergedFile;
};

}

#endif
