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
 
#ifndef SVNQT_DIFF_DATA_H
#define SVNQT_DIFF_DATA_H

#include "pool.h"
#include "path.h"
#include "revision.h"
#include "svnqt_global.h"

#include <QByteArray>

struct apr_file_t;

namespace svn
{
    class Path;

    class DiffData
    {
        protected:
            Pool m_Pool;
            Path m_tmpPath;
            apr_file_t*m_outFile;
            apr_file_t*m_errFile;
            const char*m_outFileName;
            const char*m_errFileName;

            Path m_p1,m_p2;
            Revision m_r1,m_r2;

            bool m_working_copy_present,m_url_is_present;

            void init();
            void clean();
            void close();

        public:
            DiffData(const Path&aTmpPath,const Path&,const Revision&,const Path&,const Revision&);
            virtual ~DiffData();

            apr_file_t*outFile(){return m_outFile;}
            apr_file_t*errFile(){return m_errFile;}
            const Revision& r1()const{return m_r1;}
            const Revision& r2()const{return m_r2;}

            QByteArray content();
    };
}

#endif
