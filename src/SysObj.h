/* Header for SysObj class
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

#include "RowId.h"

#ifndef SYSOBJ_H_
#define SYSOBJ_H_

#define SYSOBJ_ROWID_LENGTH             18
#define SYSOBJ_NAME_LENGTH              128

//11.2
#define SYSOBJ_TYPE_NEXT_OBJECT         0
#define SYSOBJ_TYPE_INDEX               1
#define SYSOBJ_TYPE_TABLE               2
#define SYSOBJ_TYPE_CLUSTER             3
#define SYSOBJ_TYPE_VIEW                4
#define SYSOBJ_TYPE_SYNONYM             5
#define SYSOBJ_TYPE_SEQUENCE            6
#define SYSOBJ_TYPE_PROCEDURE           7
#define SYSOBJ_TYPE_FUNCTION            8
#define SYSOBJ_TYPE_PACKAGE             9
#define SYSOBJ_TYPE_NON_EXISTENT        10
#define SYSOBJ_TYPE_PACKAGE_BODY        11
#define SYSOBJ_TYPE_TRIGGER             12
#define SYSOBJ_TYPE_TYPE                13
#define SYSOBJ_TYPE_TYPE_BODY           14
#define SYSOBJ_TYPE_LIBRARY             22
#define SYSOBJ_TYPE_JAVA_SOURCE         28
#define SYSOBJ_TYPE_JAVA_CLASS          29
#define SYSOBJ_TYPE_INDEXTYPE           32
#define SYSOBJ_TYPE_OPERATOR            33
#define SYSOBJ_TYPE_MATERIALIZED_VIEW   42
#define SYSOBJ_TYPE_DIMENSION           43
#define SYSOBJ_TYPE_RULE_SET            46
#define SYSOBJ_TYPE_XML_SCHEMA          55
#define SYSOBJ_TYPE_JAVA_DATA           56
#define SYSOBJ_TYPE_RULE                59
#define SYSOBJ_TYPE_EVALUATION_CONTXT   62
#define SYSOBJ_TYPE_ASSEMBLY            87
#define SYSOBJ_TYPE_CREDENTIAL          90
#define SYSOBJ_TYPE_CUBE_DIMENSION      92
#define SYSOBJ_TYPE_CUBE                93
#define SYSOBJ_TYPE_MEASURE_FOLDER      94
#define SYSOBJ_TYPE_CUBE_BUILD_PROCESS  95
//12.1
#define SYSOBJ_TYPE_DIRECTORY           23
#define SYSOBJ_TYPE_CREDENTIAL          90
//12.2
#define SYSOBJ_TYPE_HIERARCHY           150
#define SYSOBJ_TYPE_ATTRIBUTE_DIMENSION 151
#define SYSOBJ_TYPE_ANALYTIC_VIEW       152
//19.0
#define SYSOBJ_TYPE_QUEUE               24

namespace OpenLogReplicator {
    class SysObj {
    public:
        SysObj(RowId& rowId, typeUSER owner, typeOBJ obj, typeDATAOBJ dataObj, typeTYPE type, const char* name,
                uint64_t flags1, uint64_t flags2, bool single, bool touched);
        bool isTable(void);
        bool isTemporary(void);
        bool isDropped(void);

        RowId rowId;
        typeUSER owner;
        typeOBJ obj;
        typeDATAOBJ dataObj;        //NULL
        typeTYPE type;
        std::string name;
        uintX_t flags;             //NULL
        bool single;
        bool touched;
        bool saved;
    };
}

#endif
