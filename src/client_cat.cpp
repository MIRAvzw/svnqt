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
 
#if defined( _MSC_VER) && _MSC_VER <= 1200
#pragma warning( disable: 4786 )// debug symbol truncated
#endif
// svncpp
#include "client_impl.h"

// Subversion api
#include <subversion-1/svn_client.h>
//#include <subversion-1/svn_io.h>

#include "exception.h"
#include "pool.h"
#include "status.h"
#include "svnstream.h"
#include "svnfilestream.h"

namespace svn
{
  QByteArray
  Client_impl::cat(const Path & path,
                const Revision & revision,
                const Revision & peg_revision) throw (ClientException)
  {
    svn::stream::SvnByteStream buffer(*m_context);
    svn_error_t * error = internal_cat(path,revision,peg_revision,buffer);
    if (error != 0)
      throw ClientException (error);

    return buffer.content();
  }

  void
  Client_impl::cat(svn::stream::SvnStream&buffer,
                const Path & path,
                const Revision & revision,
                const Revision & peg_revision) throw (ClientException)
  {
    svn_error_t * error = internal_cat(path,revision,peg_revision,buffer);
    if (error != 0)
      throw ClientException (error);
  }

  void
  Client_impl::get (const Path & path,
        const QString  & target,
        const Revision & revision,
        const Revision & peg_revision) throw (ClientException)
  {
    svn::stream::SvnFileOStream buffer(target,*m_context);
    svn_error_t * error = internal_cat(path,revision,peg_revision,buffer);
    if (error != 0)
      throw ClientException (error);
  }

  svn_error_t * Client_impl::internal_cat(const Path & path,
            const Revision & revision,
            const Revision & peg_revision,
            svn::stream::SvnStream&buffer)
  {
    Pool pool;
    return svn_client_cat2 (buffer,
                             path.path().toUtf8(),
                             peg_revision.revision (),
                             revision.revision (),
                             *m_context,
                             pool);
  }

}
