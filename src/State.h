/* Header for State class
   Copyright (C) 2018-2022 Adam Leszczynski (aleszczynski@bersler.com)

This file is part of OpenLogReplicator.

OpenLogReplicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

OpenLogReplicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenLogReplicator; see the file LICENSE;  If not see
<http://www.gnu.org/licenses/>.  */

#include <set>

#include <types.h>

#ifndef STATE_H_
#define STATE_H_

#define STATE_TYPE_DISK 0
#define STATE_TYPE_REDIS 1

namespace OpenLogReplicator {
    class State {
    public:
        State();
        virtual ~State();

        virtual void list(std::set<std::string>& namesList) = 0;
        virtual bool read(std::string& name, uint64_t maxSize, std::string& in, bool noFail) = 0;
        virtual void write(std::string& name, std::stringstream& out) = 0;
        virtual void drop(std::string& name) = 0;
    };
}

#endif
