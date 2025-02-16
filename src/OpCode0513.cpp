/* Oracle Redo OpCode: 5.13
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

#include "OpCode0513.h"
#include "OracleAnalyzer.h"
#include "Reader.h"
#include "RedoLogRecord.h"

namespace OpenLogReplicator {
    OpCode0513::OpCode0513(OracleAnalyzer* oracleAnalyzer, RedoLogRecord* redoLogRecord) :
        OpCode(oracleAnalyzer, redoLogRecord) {
    }

    OpCode0513::~OpCode0513() {
    }

    void OpCode0513::process(void) {
        OpCode::process();
        uint64_t fieldPos = 0;
        typeFIELD fieldNum = 0;
        uint16_t fieldLength = 0;

        oracleAnalyzer->nextField(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051301);
        //field: 1
        dumpMsgSessionSerial(fieldPos, fieldLength);

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051302))
            return;
        //field: 2
        dumpVal(fieldPos, fieldLength, "current username = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051303))
            return;
        //field: 3
        dumpVal(fieldPos, fieldLength, "login   username = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051304))
            return;
        //field: 4
        dumpVal(fieldPos, fieldLength, "client info      = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051305))
            return;
        //field: 5
        dumpVal(fieldPos, fieldLength, "OS username      = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051306))
            return;
        //field: 6
        dumpVal(fieldPos, fieldLength, "Machine name     = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051307))
            return;
        //field: 7
        dumpVal(fieldPos, fieldLength, "OS terminal      = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051308))
            return;
        //field: 8
        dumpVal(fieldPos, fieldLength, "OS process id    = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x051309))
            return;
        //field: 9
        dumpVal(fieldPos, fieldLength, "OS program name  = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x05130A))
            return;
        //field: 10
        dumpVal(fieldPos, fieldLength, "transaction name = ");

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x05130B))
            return;
        //field: 11
        dumpMsgFlags(fieldPos, fieldLength);

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x05130C))
            return;
        //field: 12
        dumpMsgVersion(fieldPos, fieldLength);

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x05130D))
            return;
        //field: 13
        dumpMsgAuditSessionid(fieldPos, fieldLength);

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x05130E))
            return;
        //field: 14
        dumpVal(fieldPos, fieldLength, "Client Id  = ");
    }

    void OpCode0513::dumpMsgFlags(uint64_t fieldPos, uint64_t fieldLength) const {
        uint16_t flags = oracleAnalyzer->read16(redoLogRecord->data + fieldPos + 0);
        if ((flags & 0x0001) != 0) oracleAnalyzer->dumpStream << "DDL transaction" << std::endl;
        if ((flags & 0x0002) != 0) oracleAnalyzer->dumpStream << "Space Management transaction" << std::endl;
        if ((flags & 0x0004) != 0) oracleAnalyzer->dumpStream << "Recursive transaction" << std::endl;
        if ((flags & 0x0008) != 0) oracleAnalyzer->dumpStream << "Logmnr Internal transaction" << std::endl;
        if ((flags & 0x0010) != 0) oracleAnalyzer->dumpStream << "DB Open in Migrate Mode" << std::endl;
        if ((flags & 0x0020) != 0) oracleAnalyzer->dumpStream << "LSBY ignore" << std::endl;
        if ((flags & 0x0040) != 0) oracleAnalyzer->dumpStream << "LogMiner no tx chunking" << std::endl;
        if ((flags & 0x0080) != 0) oracleAnalyzer->dumpStream << "LogMiner Stealth transaction" << std::endl;
        if ((flags & 0x0100) != 0) oracleAnalyzer->dumpStream << "LSBY preserve" << std::endl;
        if ((flags & 0x0200) != 0) oracleAnalyzer->dumpStream << "LogMiner Marker transaction" << std::endl;
        if ((flags & 0x0400) != 0) oracleAnalyzer->dumpStream << "Transaction in pragama'ed plsql" << std::endl;
        if ((flags & 0x0800) != 0) oracleAnalyzer->dumpStream << "Tx audit CV flags undefined" << std::endl;
    }

    void OpCode0513::dumpMsgSessionSerial(uint64_t fieldPos, uint64_t fieldLength) const {
        if (oracleAnalyzer->dumpRedoLog >= 1) {
            if (fieldLength < 4) {
                WARNING("too short session number: " << std::dec << fieldLength);
                return;
            }

            uint16_t serialNumber = oracleAnalyzer->read16(redoLogRecord->data + fieldPos + 2);
            uint32_t sessionNumber;
            if (oracleAnalyzer->version < REDO_VERSION_19_0)
                sessionNumber = oracleAnalyzer->read16(redoLogRecord->data + fieldPos + 0);
            else {
                if (fieldLength < 8) {
                    WARNING("too short session number: " << std::dec << fieldLength);
                    return;
                }
                sessionNumber = oracleAnalyzer->read32(redoLogRecord->data + fieldPos + 4);
            }

            oracleAnalyzer->dumpStream <<
                    "session number   = " << std::dec << sessionNumber << std::endl <<
                    "serial  number   = " << std::dec << serialNumber << std::endl;
        }
    }

    void OpCode0513::dumpMsgVersion(uint64_t fieldPos, uint64_t fieldLength) const {
        if (oracleAnalyzer->dumpRedoLog >= 1) {
            uint32_t version = oracleAnalyzer->read32(redoLogRecord->data + fieldPos + 0);
            oracleAnalyzer->dumpStream << "version " << std::dec << version << std::endl;
        }
    }

    void OpCode0513::dumpMsgAuditSessionid(uint64_t fieldPos, uint64_t fieldLength) const {
        if (oracleAnalyzer->dumpRedoLog >= 1) {
            uint32_t auditSessionid = oracleAnalyzer->read32(redoLogRecord->data + fieldPos + 0);
            oracleAnalyzer->dumpStream << "audit sessionid " << auditSessionid << std::endl;
        }
    }
}
