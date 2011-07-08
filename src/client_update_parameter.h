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
 
#ifndef CLIENT_UPDATE_PARAMETER_H
#define CLIENT_UPDATE_PARAMETER_H

#include "svnqt_global.h"
#include "svnqttypes.h"
#include "revision.h"
#include "targets.h"
#include "shared_pointer.h"

namespace svn{

    struct UpdateParameterData;

    class UpdateParameter
    {
        private:
            //! internal data
            SharedPointer<UpdateParameterData> _data;

        public:
            //! constructor
            UpdateParameter();
            //! non-virtual destructor
            ~UpdateParameter();

            //! returns the targets for update
            const Targets&targets()const;
            //! set the targets for update
            UpdateParameter&targets(const Targets&_target);

            //! returns the revision the update should work on
            const Revision&revision()const;
            //! set the revision the update should work on
            UpdateParameter&revision(const Revision&rev);

            //! return depth of update operation
            /*!
             * \sa svn::Depth
             */
            Depth depth()const;
            //! set depth of update operation
            /*!
             * \sa svn::Depth
             */
            UpdateParameter&depth(Depth depth);

            //! return if update should ignore external definitions
            bool ignore_externals()const;
            //! set if update should ignore external definitions
            UpdateParameter&ignore_externals(bool);

            bool allow_unversioned()const;
            UpdateParameter&allow_unversioned(bool);

            bool sticky_depth()const;
            UpdateParameter&sticky_depth(bool);

    };
}

#endif // CLIENT_UPDATE_PARAMETER_H
