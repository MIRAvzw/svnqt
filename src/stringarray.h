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
 
#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "svnqt_global.h"
#include "svnqttypes.h"

#include <QStringList>

// apr api
#include <apr-1/apr_tables.h>

namespace svn
{
    // forward declarations
    class Pool;

    /** Handle array of const char * in a c++ like way */
    class SVNQT_EXPORT StringArray
    {
        protected:
            QStringList m_content;
            bool m_isNull;

        public:
            StringArray();
            StringArray(const QStringList&);
            StringArray(const apr_array_header_t * apr_targets);
            QStringList::size_type size()const;
            const QString& operator[](QStringList::size_type which)const;
            QString& operator[](QStringList::size_type which);
            /**
             * Returns an apr array containing char*.
             *
             * @param pool Pool used for conversion
             */
            apr_array_header_t * array (const Pool & pool) const;
            /** content of array
             * @return const reference to data, may used for searches.
             */
            const QStringList& data() const {return m_content;}

            /** if array should return 0 instead of empty array */
            bool isNull()const;
            void setNull(bool _n);
    };
}

#endif
