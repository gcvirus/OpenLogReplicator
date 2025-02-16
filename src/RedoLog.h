/* Header for RedoLog class
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

#include "types.h"
#include "RedoLogRecord.h"

#ifndef REDOLOG_H_
#define REDOLOG_H_

#define VECTOR_MAX_LENGTH 512
#define MAX_LWN_CHUNKS (512*2/MEMORY_CHUNK_SIZE_MB)

namespace OpenLogReplicator {
    class OracleAnalyzer;
    class OpCode;
    class Reader;

    struct LwnMember {
        uint64_t offset;
        uint64_t length;
        typeSCN scn;
        typeSubSCN subScn;
        typeBLK block;
    };

    class RedoLog {
    protected:
        OracleAnalyzer* oracleAnalyzer;
        OpCode* opCodes[VECTOR_MAX_LENGTH];
        RedoLogRecord zero;
        uint64_t vectors;
        uint64_t lwnConfirmedBlock;
        uint8_t* lwnChunks[MAX_LWN_CHUNKS];
        uint64_t lwnAllocated;
        uint64_t lwnAllocatedMax;
        typeTIME lwnTimestamp;
        typeSCN lwnScn;
        typeSCN lwnScnMax;
        LwnMember* lwnMembers[MAX_RECORDS_IN_LWN];
        uint64_t lwnRecords;
        uint64_t lwnCheckpointBlock;
        bool instrumentedShutdown;

        void printHeaderInfo(void) const;
        void freeLwn(void);
        void analyzeLwn(LwnMember* lwnMember);
        void appendToTransactionDDL(RedoLogRecord* redoLogRecord);
        void appendToTransactionUndo(RedoLogRecord* redoLogRecord);
        void appendToTransactionBegin(RedoLogRecord* redoLogRecord);
        void appendToTransactionCommit(RedoLogRecord* redoLogRecord);
        void appendToTransaction(RedoLogRecord* redoLogRecord1, RedoLogRecord* redoLogRecord2);
        void dumpRedoVector(uint8_t* data, uint64_t recordLength4) const;

    public:
        int64_t group;
        std::string path;
        typeSEQ sequence;
        typeSCN firstScn;
        typeSCN nextScn;
        Reader* reader;

        uint64_t processLog(void);
        RedoLog(OracleAnalyzer* oracleAnalyzer, int64_t group, std::string& path);
        virtual ~RedoLog(void);

        friend std::ostream& operator<<(std::ostream& os, const RedoLog& redoLog);
    };
}

#endif
