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
 
#ifndef SVN_STREAMSVNFILESTREAM_HPP
#define SVN_STREAMSVNFILESTREAM_HPP

#include "svnqt_global.h"
#include "svnstream.h"

namespace svn {

namespace stream {

class SvnFileStream_private;

/**
	@author Rajko Albrecht <ral@alwins-world.de>
    @short Writeonly filestream
*/
class SVNQT_EXPORT SvnFileOStream : public SvnStream
{
public:
    explicit SvnFileOStream(const QString&fn,svn_client_ctx_t*ctx=0);

    virtual ~SvnFileOStream();

    virtual bool isOk() const;
    virtual long write(const char* data, const unsigned long max);
private:
    SvnFileStream_private*m_FileData;
};

/**
    @author Rajko Albrecht <ral@alwins-world.de>
    @short Readonly filestream
*/
class SVNQT_EXPORT SvnFileIStream : public SvnStream
{
public:
    explicit SvnFileIStream(const QString&fn,svn_client_ctx_t*ctx=0);

    virtual ~SvnFileIStream();
    virtual bool isOk() const;
    virtual long read(char* data, const unsigned long max);

private:
    SvnFileStream_private*m_FileData;
};

}

}

#endif
