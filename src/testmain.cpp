/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA 02110-1301 USA
 */
 
#include "client.h"
#include "repository.h"
#include "context.h"
#include "datetime.h"
#include "client_parameter.h"

#include <qdatastream.h>

int main(int,char**)
{
    svn::Client::getobject(0,0);
    svn::repository::Repository rep(0L);
    svn::ContextP myContext = new svn::Context();

    QByteArray tout;
    svn::Client*m_Svnclient = svn::Client::getobject(0,0);
    svn::ContextP m_CurrentContext = new svn::Context();
    m_Svnclient->setContext(m_CurrentContext);
    bool gotit = true;
    svn::LogEntriesMap m_OldHistory;
    svn::LogParameter params;

    try {
        m_Svnclient->log(params.targets("http://www.alwins-world.de/repos/kdesvn/trunk").revisionRange(svn::Revision::HEAD,20).peg(svn::Revision::UNDEFINED).discoverChangedPathes(true).
        strictNodeHistory(false).limit(0),m_OldHistory);
    } catch (svn::ClientException ce) {
        gotit = false;
    }
  return 1;
}
