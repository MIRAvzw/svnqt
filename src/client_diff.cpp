/*
 * Port for usage with qt-framework and development for kdesvn
 * Copyright (C) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * http://kdesvn.alwins-world.de
 */
/*
 * ====================================================================
 * Copyright (c) 2002-2005 The RapidSvn Group.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA  02110-1301  USA
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#if defined( _MSC_VER) && _MSC_VER <= 1200
#pragma warning( disable: 4786 )// debug symbol truncated
#endif
// svncpp
#include "client_impl.h"

// Subversion api
#include <subversion-1/svn_client.h>
#include <subversion-1/svn_path.h>

#include "exception.h"
#include "pool.h"
#include "status.h"
#include "helper.h"
#include "diff_data.h"
#include "client_parameter.h"

#include <qfile.h>
#include <qstringlist.h>

#include <apr-1/apr_xlate.h>

namespace svn
{
  QByteArray
          Client_impl::diff_peg (const DiffParameter&options) throw (ClientException)
  {
    Pool pool;
    svn_error_t * error;
    const apr_array_header_t * _options;

    // svn_client_diff needs an options array, even if it is empty
    _options = options.extra().array(pool);
    DiffData ddata(options.tmpPath(),options.path1(),options.rev1(),options.path1(),options.rev2());

#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
    //qDebug("pegged diff4 call");
    error = svn_client_diff_peg4(
                _options,
                options.path1().cstr(),
                options.peg(),ddata.r1().revision(),ddata.r2().revision(),
                options.relativeTo().length()>0?options.relativeTo().cstr():QByteArray(/*0*/),
                internal::DepthToSvn(options.depth()),
                options.ignoreAncestry(),options.noDiffDeleted(),options.ignoreContentType(),
                APR_LOCALE_CHARSET,
                ddata.outFile(),ddata.errFile(),
                options.changeList().array(pool),
                *m_context,
                pool
            );
#else
    bool recurse = options.depth()==DepthInfinity;
    error = svn_client_diff_peg3(
                                 _options,
                                 options.path1().cstr(),
                                 options.peg(),ddata.r1().revision(),ddata.r2().revision(),
                                 recurse?1:0,options.ignoreAncestry(),options.noDiffDeleted(),options.ignoreContentType(),
                                 APR_LOCALE_CHARSET,
                                 ddata.outFile(),ddata.errFile(),
                                 *m_context,
                                 pool
                                );
#endif
    if (error != NULL)
    {
        throw ClientException (error);
    }
    return ddata.content();
  }

  QByteArray
  Client_impl::diff (const DiffParameter&options) throw (ClientException)
  {

    Pool pool;
    svn_error_t * error;
    const apr_array_header_t * _options;

    // svn_client_diff needs an options array, even if it is empty
    if(options.extra().isNull())
        _options = apr_array_make(pool, 0, 0);
    else
        _options = options.extra().array(pool);
    DiffData ddata(options.tmpPath(),options.path1(),options.rev1(),options.path2(),options.rev2());

#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
    error = svn_client_diff4(_options,
                             options.path1().cstr (), ddata.r1().revision (),
                             options.path2().cstr (), ddata.r2().revision (),
                             options.relativeTo().length()>0?options.relativeTo().cstr():QByteArray(/*0*/),
                             internal::DepthToSvn(options.depth()),
                             options.ignoreAncestry(),options.noDiffDeleted(),options.ignoreContentType(),
                             APR_LOCALE_CHARSET,
                             ddata.outFile(),ddata.errFile(),
                             options.changeList().array(pool),
                             *m_context,
                             pool);
#else
    bool recurse = options.depth()==DepthInfinity;
    // run diff
    error = svn_client_diff3 (_options,
                             options.path1().cstr (), ddata.r1().revision (),
                             options.path2().cstr (), ddata.r2().revision (),
                             recurse?1:0,options.ignoreAncestry(),options.noDiffDeleted(),options.ignoreContentType(),
                             APR_LOCALE_CHARSET,
                             ddata.outFile(),ddata.errFile(),
                             *m_context,
                             pool);
#endif
    if (error != NULL)
    {
        throw ClientException (error);
    }
    return ddata.content();

  }
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */