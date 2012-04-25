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
 
#if defined( _MSC_VER) && _MSC_VER <= 1550
#pragma warning( disable: 4786 )// debug symbol truncated
#endif

// svncpp
#include "client.h"
#include "client_impl.h"

#include <subversion-1/svn_opt.h>

#include <subversion-1/svn_cmdline.h>

#include <qstringlist.h>
#include <qdir.h>

namespace svn
{
    //! this namespace contains only internal stuff not for public use
    namespace internal {
    //! small helper class
    /*!
        There will be an static instance created for calling the constructor at program load.
     */
        class SvnInit
        {
            public:
        //! constructor calling initialize functions
                SvnInit();
                ~SvnInit(){};
        };

        SvnInit::SvnInit() {
            svn_cmdline_init("svnqt",0);
            //qDebug("svn_cmdline_init done");
            QString BasePath=QDir::homePath();
            QDir d;
            if (!d.exists(BasePath)) {
                d.mkdir(BasePath);
            }
            BasePath=BasePath+'/'+".svnqt";
            if (!d.exists(BasePath)) {
                d.mkdir(BasePath);
            }

        }
    }

  Client::Client()
  {
  }

  Client::~Client ()
  {
  }

  Client*Client::getobject(ContextP context,int subtype)
  {
      static internal::SvnInit sInit;
    switch(subtype) {
      case 0:
       return new Client_impl(context);
       break;
      default:
       break;
    }
    return 0L;
  }
}
