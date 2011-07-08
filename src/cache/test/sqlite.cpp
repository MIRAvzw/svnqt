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
 
#include <qsql.h>
#include <qsqldatabase.h>
#include <qstringlist.h>
#include <iostream>
#include <qapplication.h>
#include <qtextstream.h>

#include "client.h"
#include "svnqttypes.h"
#include "log_entry.h"

#include "cache/LogCache.h"
#include "cache/ReposLog.h"
#include "cache/ReposConfig.h"
#include "cache/test/testconfig.h"
#include "cache/DatabaseException.h"

#include <QSqlQuery>
#include <QSqlError>

int main(int argc,char**argv)
{
    QApplication app(argc,argv);

    svn::ContextP m_CurrentContext;
    svn::Client* m_Svnclient;
    m_Svnclient=svn::Client::getobject(0,0);
    m_CurrentContext = new svn::Context();

    m_Svnclient->setContext(m_CurrentContext);

    QStringList list;
    QStringList::Iterator it;
    // goes into "self" of logcache
    new svn::cache::LogCache(TESTDBPATH);
    list = QSqlDatabase::drivers();
    it = list.begin();
    while( it != list.end() ) {
        std::cout << (*it).toUtf8().data() << std::endl;
        ++it;
    }
    svn::cache::ReposLog rl(m_Svnclient,"http://www.alwins-world.de/repos/kdesvn");
    QSqlDatabase db = rl.Database();
    if (!db.isValid()) {
        std::cerr << "No database object."<<std::endl;
        exit(-1);
    }
    list = db.tables();
    it = list.begin();
    while( it != list.end() ) {
        std::cout << "Table: "<<( *it ).toUtf8().data() << std::endl;
        ++it;
    }
    svn::LogEntriesMap lm;
    try {
        rl.simpleLog(lm,100,svn::Revision::HEAD);
    }
    catch (const svn::cache::DatabaseException&cl)
    {
        std::cerr << cl.msg().toUtf8().data() <<std::endl;
    }
    catch (const svn::Exception&ce)
    {
        std::cerr << "Exception: " << ce.msg().toUtf8().data() <<std::endl;
    }
    svn::LogEntriesMap::ConstIterator lit = lm.begin();
    std::cout<<"Count: "<<lm.count()<<std::endl;

    svn::Revision r("{2006-09-27}");
    std::cout << r.toString().toUtf8().data() << " -> " << rl.date2numberRev(r).toString().toUtf8().data()<<std::endl;
    r = svn::Revision::HEAD;
    std::cout << rl.date2numberRev(r).toString().toUtf8().data()<<std::endl;
    try {
        rl.insertLogEntry(lm[100]);
    }
    catch (const svn::cache::DatabaseException&cl)
    {
        std::cerr << cl.msg().toUtf8().data() << std::endl;
    }
    QSqlQuery q("insert into logentries(revision,date,author,message) values ('100','1122591406','alwin','copy and moving works now in basic form')",db);
    q.exec();
    std::cerr << "\nSelf: \n" << q.lastError().text().toUtf8().data()<<std::endl;


    db=QSqlDatabase();
    try {
        rl.log("/trunk/src/svnqt",1,1000,svn::Revision::UNDEFINED,lm,false,-1);
    }
    catch (const svn::cache::DatabaseException&cl)
    {
        std::cerr << cl.msg().toUtf8().data() <<std::endl;
    }
    catch (const svn::Exception&ce)
    {
        std::cerr << "Exception: " << ce.msg().toUtf8().data() <<std::endl;
    }
    std::cout<<"Count: "<<lm.count()<<std::endl;

    QStringList s; s << "a" << "b" << "c";

    svn::cache::ReposConfig::self()->setValue("http://www.alwins-world.de/repos/kdesvn","bommel",s);
    list = svn::cache::ReposConfig::self()->readEntry("http://www.alwins-world.de/repos/kdesvn","bommel",QStringList());
    std::cout<<"Value: ";
    foreach(const QString &entry, list) {
        std::cout << entry.toUtf8().data()<<",";
    }
    std::cout << std::endl;
    return 0;
}
