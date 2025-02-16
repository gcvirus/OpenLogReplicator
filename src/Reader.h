/* Header for Reader class
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

#include <atomic>
#include <vector>
#include "Thread.h"

#ifndef READER_H_
#define READER_H_

#define READER_STATUS_SLEEPING  0

#define READER_STATUS_CHECK     1
#define READER_STATUS_UPDATE    2
#define READER_STATUS_READ      3

#define REDO_VERSION_12_1       0x0C100000
#define REDO_VERSION_12_2       0x0C200000
#define REDO_VERSION_19_0       0x13000000

#define REDO_END                0x0008
#define REDO_ASYNC              0x0100
#define REDO_NODATALOSS         0x0200
#define REDO_RESYNC             0x0800
#define REDO_CLOSEDTHREAD       0x1000
#define REDO_MAXPERFORMANCE     0x2000

#define REDO_OK                 0
#define REDO_OVERWRITTEN        1
#define REDO_FINISHED           2
#define REDO_STOPPED            3
#define REDO_EMPTY              4
#define REDO_ERROR_READ         5
#define REDO_ERROR_WRITE        6
#define REDO_ERROR_SEQUENCE     7
#define REDO_ERROR_CRC          8
#define REDO_ERROR_BLOCK        9
#define REDO_ERROR_BAD_DATA    10
#define REDO_ERROR             11

#define REDO_PAGE_SIZE_MAX      4096
#define REDO_BAD_CDC_MAX_CNT    20
#define REDO_BUFFER_FULL_SLEEP  1000
#define REDO_READ_VERIFY_MAX_BLOCKS (MEMORY_CHUNK_SIZE/blockSize)

namespace OpenLogReplicator {
    class OracleAnalyzer;

    class Reader : public Thread {
    protected:
        OracleAnalyzer* oracleAnalyzer;
        bool hintDisplayed;
        int64_t fileCopyDes;
        typeSEQ fileCopySequence;

        virtual void redoClose(void) = 0;
        virtual uint64_t redoOpen(void) = 0;
        virtual int64_t redoRead(uint8_t* buf, uint64_t offset, uint64_t size) = 0;
        virtual uint64_t readSize(uint64_t lastRead);
        virtual uint64_t reloadHeaderRead(void);

        uint64_t checkBlockHeader(uint8_t* buffer, typeBLK blockNumber, bool checkSum, bool showHint);
        uint64_t reloadHeader(void);

    public:
        static char* REDO_CODE[13];
        uint8_t** redoBufferList;
        uint8_t* headerBuffer;
        int64_t group;
        typeSEQ sequence;
        std::vector<std::string> paths;
        std::string fileName;
        std::string fileNameWrite;
        uint64_t blockSize;
        uint32_t compatVsn;
        typeBLK numBlocksHeader;
        typeBLK numBlocks;
        typeRESETLOGS resetlogsHeader;
        typeACTIVATION activationHeader;
        typeTIME firstTimeHeader;
        typeSCN firstScnHeader;
        typeSCN firstScn;
        typeSCN nextScnHeader;
        typeSCN nextScn;
        uint64_t sumRead;
        uint64_t sumTime;

        uint64_t fileSize;
        std::atomic<uint64_t> status;
        std::atomic<uint64_t> ret;
        std::atomic<uint64_t> bufferStart;
        std::atomic<uint64_t> bufferEnd;
        std::atomic<uint64_t> buffersFree;
        uint64_t bufferSizeMax;
        uint64_t buffersMaxUsed;

        Reader(const char* alias, OracleAnalyzer* oracleAnalyzer, int64_t group);
        virtual ~Reader();

        void initialize(void);
        void* run(void);
        void bufferAllocate(uint64_t num);
        void bufferFree(uint64_t num);
        typeSUM calcChSum(uint8_t* buffer, uint64_t size) const;
    };
}

#endif
