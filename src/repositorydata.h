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
 
#ifndef SVNREPOSITORYDATA_H
#define SVNREPOSITORYDATA_H

#include "svnqt_global.h"
#include "pool.h"
#include "revision.h"
#include <apr-1/apr_general.h>

#include <qstring.h>

#include <subversion-1/svn_repos.h>
#include <subversion-1/svn_error.h>

namespace svn {

namespace repository {

class Repository;
class RepositoryListener;
class CreateRepoParameter;
/**
	@author Rajko Albrecht <ral@alwins-world.de>
*/
class RepositoryData{
    friend class Repository;

public:
    RepositoryData(RepositoryListener*);

    virtual ~RepositoryData();
    void Close();
    svn_error_t * Open(const QString&);
    svn_error_t * CreateOpen(const CreateRepoParameter&params);

    void reposFsWarning(const QString&msg);
    svn_error_t* dump(const QString&output,const svn::Revision&start,const svn::Revision&end, bool incremental, bool use_deltas);
    svn_error_t* loaddump(const QString&dump,svn_repos_load_uuid uuida, const QString&parentFolder, bool usePre, bool usePost);
    static svn_error_t* hotcopy(const QString&src,const QString&dest,bool cleanlogs);

protected:
    Pool m_Pool;
    svn_repos_t*m_Repository;
    RepositoryListener*m_Listener;

private:
    static void warning_func(void *baton, svn_error_t *err);
    static svn_error_t*cancel_func(void*baton);
};

}

}

#endif
