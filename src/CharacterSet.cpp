/* Class to handle different character sets
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

#include "CharacterSet.h"

namespace OpenLogReplicator {
    CharacterSet::CharacterSet(const char* name) :
        name(name) {
    }

    CharacterSet::~CharacterSet() {
    }

    uint64_t CharacterSet::badChar(uint64_t byte1) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }

    uint64_t CharacterSet::badChar(uint64_t byte1, uint64_t byte2) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte2 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }

    uint64_t CharacterSet::badChar(uint64_t byte1, uint64_t byte2, uint64_t byte3) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte2 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte3 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }

    uint64_t CharacterSet::badChar(uint64_t byte1, uint64_t byte2, uint64_t byte3, uint64_t byte4) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte2 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte3 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte4 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }

    uint64_t CharacterSet::badChar(uint64_t byte1, uint64_t byte2, uint64_t byte3, uint64_t byte4, uint64_t byte5) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte2 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte3 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte4 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte5 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }

    uint64_t CharacterSet::badChar(uint64_t byte1, uint64_t byte2, uint64_t byte3, uint64_t byte4, uint64_t byte5, uint64_t byte6) const {
        ERROR("can't decode character: 0x" << std::setfill('0') << std::setw(2) << std::hex << byte1 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte2 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte3 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte4 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte5 <<
                ",0x" << std::setfill('0') << std::setw(2) << std::hex << byte6 << " in character set " << name);
        return UNICODE_UNKNOWN_CHARACTER;
    }
}
