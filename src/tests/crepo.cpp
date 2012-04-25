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
#include "tests/testconfig.h"
#include "repository.h"
#include "repositorylistener.h"
#include "repoparameter.h"
#include "targets.h"
#include "client_parameter.h"

#include "testlistener.h"

#include <iostream>
#include <unistd.h>
#include <qstringlist.h>

class Listener:public svn::repository::RepositoryListener
{
    public:
        Listener(){}
        virtual ~Listener(){}
        virtual void sendWarning(const QString&msg)
        {
            std::cout << msg.toAscii().data() << std::endl;
        }
        virtual void sendError(const QString&msg)
        {
            std::cout << msg.toAscii().data() << std::endl;
        }
        virtual bool isCanceld(){return false;}
};

int main(int,char**)
{
    QString p = TESTREPOPATH;
    Listener ls;
    svn::repository::Repository rp(&ls);
    try {
        rp.CreateOpen(svn::repository::CreateRepoParameter().path(p).fstype("fsfs"));
    } catch (svn::ClientException e) {
        QString ex = e.msg();
        std::cout << ex.toUtf8().data() << std::endl;
        return -1;
    }

    svn::ContextP m_CurrentContext;
    svn::Client* m_Svnclient;
    m_Svnclient=svn::Client::getobject(0,0);
    TestListener tl;
    m_CurrentContext = new svn::Context();
    m_CurrentContext->setListener(&tl);
    p = "file://"+p;

    m_Svnclient->setContext(m_CurrentContext);
    QStringList s; s.append(p+"/trunk"); s.append(p+"/branches"); s.append(p+"/tags");
    svn::CheckoutParameter cparams;
    cparams.moduleName(p).destination(TESTCOPATH).revision(svn::Revision::HEAD).peg(svn::Revision::HEAD).depth(svn::DepthInfinity);

    try {
        m_Svnclient->mkdir(svn::Targets(s),"Test mkdir");
        m_Svnclient->checkout(cparams);
    } catch (svn::ClientException e) {
        QString ex = e.msg();
        std::cout << ex.toUtf8().data() << std::endl;
        return -1;
    }
    return 0;
}
