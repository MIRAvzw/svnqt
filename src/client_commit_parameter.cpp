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
 
#include "client_commit_parameter.h"
#include "svnqttypes.h"
#include "stringarray.h"
#include "client_parameter_macros.h"

namespace svn
{
    struct CommitParameterData
    {
        CommitParameterData()
            :_targets(),_message(QString()),_depth(DepthInfinity),_changeList(StringArray()),
             _revProps(PropertiesMap()),_keepLocks(false),_keepChangeList(false)
        {}
        Targets _targets;
        QString _message;
        Depth _depth;
        StringArray _changeList;
        PropertiesMap _revProps;
        bool _keepLocks,_keepChangeList;
    };

    CommitParameter::CommitParameter()
    {
        _data = new CommitParameterData;
    }
    CommitParameter::~CommitParameter()
    {
        _data = 0;
    }
    GETSET(CommitParameter,Targets,_targets,targets)
    GETSET(CommitParameter,QString,_message,message)
    GETSET(CommitParameter,StringArray,_changeList,changeList)
    GETSET(CommitParameter,PropertiesMap,_revProps,revisionProperties)
    GETSETSI(CommitParameter,Depth,_depth,depth)
    GETSETSI(CommitParameter,bool,_keepLocks,keepLocks)
    GETSETSI(CommitParameter,bool,_keepChangeList,keepChangeList)
}
