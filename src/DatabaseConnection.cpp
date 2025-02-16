/* Class to handle database connection
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

#include "DatabaseConnection.h"
#include "DatabaseEnvironment.h"

namespace OpenLogReplicator {
    DatabaseConnection::DatabaseConnection(DatabaseEnvironment* env, const char* user, const char* password, const char* connectString, bool sysASM) :
        user(user),
        password(password),
        connectString(connectString),
        sysASM(sysASM),
        connected(false),
        env(env),
        errhp(nullptr),
        srvhp(nullptr),
        svchp(nullptr),
        authp(nullptr) {
    }

    void DatabaseConnection::connect(void) {
        disconnect();

        OCIHandleAlloc((dvoid*) env->envhp, (dvoid**) &errhp, OCI_HTYPE_ERROR, 0, nullptr);
        OCIHandleAlloc((dvoid*) env->envhp, (dvoid**) &srvhp, OCI_HTYPE_SERVER, 0, nullptr);
        OCIHandleAlloc((dvoid*) env->envhp, (dvoid**) &svchp, OCI_HTYPE_SVCCTX, 0, nullptr);
        OCIHandleAlloc((dvoid*) env->envhp, (dvoid**) &authp, OCI_HTYPE_SESSION, 0, nullptr);

        env->checkErr(errhp, OCIServerAttach(srvhp, errhp, (const OraText*) connectString.c_str(), connectString.length(), OCI_DEFAULT));
        env->checkErr(errhp, OCIAttrSet((dvoid*) svchp, OCI_HTYPE_SVCCTX, srvhp, 0, OCI_ATTR_SERVER, (OCIError*) errhp));
        env->checkErr(errhp, OCIAttrSet((dvoid*) authp, OCI_HTYPE_SESSION, (dvoid*) user.c_str(), user.length(), OCI_ATTR_USERNAME, (OCIError*) errhp));
        env->checkErr(errhp, OCIAttrSet((dvoid*) authp, OCI_HTYPE_SESSION, (dvoid*) password.c_str(), password.length(), OCI_ATTR_PASSWORD, (OCIError*) errhp));

        if (sysASM)
            env->checkErr(errhp, OCISessionBegin(svchp, errhp, authp, OCI_CRED_RDBMS, OCI_SYSASM));
        else
            env->checkErr(errhp, OCISessionBegin(svchp, errhp, authp, OCI_CRED_RDBMS, OCI_DEFAULT));

        env->checkErr(errhp, OCIAttrSet((dvoid*) svchp, OCI_HTYPE_SVCCTX, (dvoid*) authp, 0, OCI_ATTR_SESSION, errhp));

        connected = true;
    }

    void DatabaseConnection::disconnect(void) {
        if (svchp != nullptr && errhp != nullptr)
            OCISessionEnd(svchp, errhp, nullptr, OCI_DEFAULT);

        if (svchp != nullptr && errhp != nullptr)
            OCIServerDetach(srvhp, errhp, OCI_DEFAULT);

        if (authp != nullptr) {
            OCIHandleFree((dvoid*) authp, OCI_HTYPE_SESSION);
            authp = nullptr;
        }

        if (errhp != nullptr) {
            OCIServerDetach(srvhp, errhp, OCI_DEFAULT);
            errhp = nullptr;
        }

        if (svchp != nullptr) {
            OCIHandleFree((dvoid*) svchp, OCI_HTYPE_SVCCTX);
            svchp = nullptr;
        }

        if (authp != nullptr) {
            OCIHandleFree((dvoid*) authp, OCI_HTYPE_SERVER);
            authp = nullptr;
        }

        if (errhp != nullptr) {
            OCIHandleFree((dvoid*) errhp, OCI_HTYPE_ERROR);
            errhp = nullptr;
        }

        connected = false;
    }

    DatabaseConnection::~DatabaseConnection() {
        if (connected)
            disconnect();
    }
}
