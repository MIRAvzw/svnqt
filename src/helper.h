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
 
#ifndef SVNQT_HELPER_H
#define SVNQT_HELPER_H

#include "svnqt_global.h"
#include "svnqttypes.h"
#include "revision.h"
#include <subversion-1/svn_types.h>

#include <iostream>

namespace svn
{
    namespace internal
    {
        class DepthToSvn
        {
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
            protected:
                svn_depth_t _value;
            public:
                DepthToSvn(const svn::Depth&val):_value(svn_depth_unknown)
                {
                    switch (val) {
                        case DepthUnknown:
                            _value = svn_depth_unknown;
                            break;
                        case DepthExclude:
                            _value =  svn_depth_exclude;
                            break;
                        case DepthEmpty:
                            _value =  svn_depth_empty;
                            break;
                        case DepthFiles:
                            _value =  svn_depth_files;
                            break;
                        case DepthImmediates:
                            _value =  svn_depth_immediates;
                            break;
                        case DepthInfinity:
                        default:
                            _value =  svn_depth_infinity;
                            break;
                    }
                }

                operator svn_depth_t ()
                {
                    return _value;
                }
#endif
        };

        class RevisionRangesToHash
        {
#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
            protected:
                RevisionRanges m_ranges;
            public:
                RevisionRangesToHash(const RevisionRanges&_input):m_ranges(_input){}

                apr_array_header_t*array(const Pool&pool)
                {
                    apr_array_header_t*ranges=apr_array_make(pool,m_ranges.size(),sizeof(svn_opt_revision_range_t *));
                    svn_opt_revision_range_t *range;

                    for (long j=0;j<m_ranges.count();++j)
                    {
                        range = (svn_opt_revision_range_t *)apr_palloc(pool, sizeof(*range));
                        range->start= *m_ranges[j].first.revision();
                        range->end  = *m_ranges[j].second.revision();
                        APR_ARRAY_PUSH(ranges,svn_opt_revision_range_t *) = range;
                    }
                    return ranges;
                }
#endif
        };
    }
}
#endif
