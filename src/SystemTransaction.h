/* Header for SystemTransaction class
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

#include "types.h"
#include "RowId.h"

#ifndef SYSTEMTRANSACTION_H_
#define SYSTEMTRANSACTION_H_

namespace OpenLogReplicator {
    class OracleObject;
    class OracleAnalyzer;
    class OutputBuffer;
    class Schema;
    class SysCCol;
    class SysCDef;
    class SysCol;
    class SysDeferredStg;
    class SysECol;
    class SysObj;
    class SysTab;
    class SysTabComPart;
    class SysTabPart;
    class SysTabSubPart;
    class SysUser;

    class SystemTransaction {
    protected:
        OracleAnalyzer* oracleAnalyzer;
        OutputBuffer* outputBuffer;
        Schema* schema;
        SysCCol* sysCCol;
        SysCDef* sysCDef;
        SysCol* sysCol;
        SysDeferredStg* sysDeferredStg;
        SysECol* sysECol;
        SysObj* sysObj;
        SysTab* sysTab;
        SysTabComPart* sysTabComPart;
        SysTabPart* sysTabPart;
        SysTabSubPart* sysTabSubPart;
        SysUser* sysUser;

        bool updateNumber16(int16_t& val, int16_t defVal, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateNumber16u(uint16_t& val, uint16_t devVal, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateNumber32u(uint32_t& val, uint32_t defVal, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateNumber64(int64_t& val, int64_t defVal, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateNumber64u(uint64_t& val, uint64_t devVal, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateNumberXu(uintX_t& val, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateObj(typeOBJ& val, typeCOL column, OracleObject* object, RowId& rowId);
        bool updatePart(typeOBJ& val, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateUser(typeUSER& val, typeCOL column, OracleObject* object, RowId& rowId);
        bool updateString(std::string& val, uint64_t maxLength, typeCOL column, OracleObject* object, RowId& rowId);
        void toRemove(typeOBJ obj);
        void toAdd(typeOBJ obj);

    public:
        SystemTransaction(OracleAnalyzer* oracleAnalyzer, OutputBuffer* outputBuffer, Schema* schema);
        ~SystemTransaction();
        void processInsert(OracleObject* object, typeDATAOBJ dataObj, typeDBA bdba, typeSLOT slot, typeXID xid);
        void processUpdate(OracleObject* object, typeDATAOBJ dataObj, typeDBA bdba, typeSLOT slot, typeXID xid);
        void processDelete(OracleObject* object, typeDATAOBJ dataObj, typeDBA bdba, typeSLOT slot, typeXID xid);
        void commit(typeSCN scn);
    };
}

#endif
