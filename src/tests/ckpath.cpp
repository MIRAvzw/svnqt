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
 
#include "path.h"
#include <qstring.h>
#include <iostream>

int main(int,char**)
{
    svn::Path pa("/test/foo/bar/");
    if (pa.path()!=QString("/test/foo/bar")) {
        std::cout << "No cleanup of components" << std::endl;
        return -1;
    }
    pa.removeLast();
    if (pa.path()!=QString("/test/foo")) {
        std::cout<<"removeLast didn't work." << std::endl;
        return -1;
    }
    unsigned j = 0;
    while (pa.length()>0) {
        std::cout << pa.path().toAscii().data() << std::endl;
        pa.removeLast();
        ++j;
    }
    return 0;
}

