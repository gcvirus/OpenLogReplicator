/* Oracle Redo OpCode: 11.2
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

#include "OpCode0B02.h"
#include "OracleAnalyzer.h"
#include "RedoLogRecord.h"

namespace OpenLogReplicator {
    OpCode0B02::OpCode0B02(OracleAnalyzer* oracleAnalyzer, RedoLogRecord* redoLogRecord) :
        OpCode(oracleAnalyzer, redoLogRecord) {
    }

    OpCode0B02::~OpCode0B02() {
    }

    void OpCode0B02::process(void) {
        OpCode::process();
        uint64_t fieldPos = 0;
        typeFIELD fieldNum = 0;
        uint16_t fieldLength = 0;

        oracleAnalyzer->nextField(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x0B0201);
        //field: 1
        ktbRedo(fieldPos, fieldLength);

        if (!oracleAnalyzer->nextFieldOpt(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x0B0202))
            return;
        //field: 2
        kdoOpCode(fieldPos, fieldLength);
        redoLogRecord->nullsDelta = fieldPos + 45;
        uint8_t* nulls = redoLogRecord->data + redoLogRecord->nullsDelta;

        redoLogRecord->rowData = fieldNum + 1;
        uint8_t bits = 1;

        //fields: 3 + cc ... 3 + cc - 1
        if (oracleAnalyzer->dumpRedoLog >= 1)
            for (uint64_t i = 0; i < redoLogRecord->cc; ++i) {
                if (fieldNum >= redoLogRecord->fieldCnt)
                    break;
                oracleAnalyzer->nextField(redoLogRecord, fieldNum, fieldPos, fieldLength, 0x0B0204);

                dumpCols(redoLogRecord->data + fieldPos, i, fieldLength, *nulls & bits);
                bits <<= 1;
                if (bits == 0) {
                    bits = 1;
                    ++nulls;
                }
            }
    }
}
