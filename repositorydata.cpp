/***************************************************************************
 *   Copyright (C) 2006 by Rajko Albrecht                                  *
 *   ral@alwins-world.de                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/
#include "repositorydata.hpp"
#include "svncpp_defines.hpp"
#include "exception.hpp"
#include "repositorylistener.hpp"

#include <svn_fs.h>
#include <svn_path.h>
#include <svn_config.h>

namespace svn {

RepositoryData::RepositoryData(RepositoryListener*aListener)
{
    m_Repository = 0;
    m_Listener = aListener;
}


RepositoryData::~RepositoryData()
{
}

void RepositoryData::warning_func(void *baton, svn_error_t *err)
{
    RepositoryData*_r = (RepositoryData*)baton;

    if (_r) {
        QString msg = svn::Exception::error2msg(err);
        svn_error_clear(err);
        _r->reposFsWarning(msg);
    }
}

void RepositoryData::reposFsWarning(const QString&msg)
{
    if (m_Listener) {
        m_Listener->sendWarning(msg);
    }
}

}

/*!
    \fn svn::RepositoryData::close()
 */
void svn::RepositoryData::Close()
{
    m_Pool.renew();
    m_Repository = 0;
}


/*!
    \fn svn::RepositoryData::Open(const QString&)
 */
svn_error_t * svn::RepositoryData::Open(const QString&path)
{
    Close();
    svn_error_t * error = svn_repos_open(&m_Repository,path.TOUTF8(),m_Pool);
    if (error!=0L) {
        m_Repository=0;
        return error;
    }
    svn_fs_set_warning_func(svn_repos_fs(m_Repository), svn::RepositoryData::warning_func, this);
    return SVN_NO_ERROR;
}


/*!
    \fn svn::RepositoryData::CreateOpen(const QString&path, const QString&fstype, bool _bdbnosync = false, bool _bdbautologremove = true, bool nosvn1diff=false)
 */
svn_error_t * svn::RepositoryData::CreateOpen(const QString&path, const QString&fstype, bool _bdbnosync, bool _bdbautologremove, bool _nosvn1diff)
{
    Close();
    QString _type;
    if (fstype.lower()=="bdb") {
        _type="bdb";
    } else {
        _type="fsfs";
    }
    apr_hash_t *config;
    apr_hash_t *fs_config = apr_hash_make(m_Pool);

    apr_hash_set(fs_config, SVN_FS_CONFIG_BDB_TXN_NOSYNC,
                APR_HASH_KEY_STRING,
                (_bdbnosync ? "1" : "0"));
    apr_hash_set(fs_config, SVN_FS_CONFIG_BDB_LOG_AUTOREMOVE,
                APR_HASH_KEY_STRING,
                (_bdbautologremove ? "1" : "0"));
    apr_hash_set(fs_config, SVN_FS_CONFIG_FS_TYPE,
                 APR_HASH_KEY_STRING,
                 _type.TOUTF8());

    /// @todo comes with 1.4!
    if (_nosvn1diff) {
#if (SVN_VER_MAJOR >= 1) && (SVN_VER_MINOR >= 4)
        apr_hash_set(fs_config, SVN_FS_CONFIG_NO_SVNDIFF1,
            APR_HASH_KEY_STRING,"1");
#endif
    }
    /// @todo config as extra paramter? Meanwhile default config only
    /// (see svn::ContextData)
    SVN_ERR(svn_config_get_config(&config, 0, m_Pool));
    const char*repository_path = path.TOUTF8();
    repository_path = svn_path_internal_style(repository_path, m_Pool);

    if (svn_path_is_url(repository_path)) {
        return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
            "'%s' is an URL when it should be a path",repository_path);
    }

    SVN_ERR(svn_repos_create(&m_Repository, repository_path,
            NULL, NULL,config, fs_config,m_Pool));

    svn_fs_set_warning_func(svn_repos_fs(m_Repository), svn::RepositoryData::warning_func, this);

    return SVN_NO_ERROR;
}