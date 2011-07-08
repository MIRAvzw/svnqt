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
 
#ifndef DATABASE_EXCEPTION_H
#define DATABASE_EXCEPTION_H

#include "svnqt_global.h"
#include "exception.h"

namespace svn
{
namespace cache
{

class SVNQT_EXPORT DatabaseException:public svn::Exception
{
    private:
        DatabaseException()throw();
        int m_number;

    public:
        DatabaseException(const QString&msg)throw()
            : Exception(msg),m_number(-1)
        {}

        DatabaseException(const DatabaseException&src)throw()
            : Exception(src.msg()),m_number(src.number())
        {}
        DatabaseException(const QString&msg,int aNumber)throw();
        virtual ~DatabaseException()throw(){}
        int number() const
        {
            return m_number;
        }
};

}
}
#endif
