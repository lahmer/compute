//
// Created by lahmer on 8/16/16.
//

#ifndef CLIOTEST_COMPUTE_H
#define CLIOTEST_COMPUTE_H

#include "common.h"
class Compute {
public:
    ///This method must be called before starting the program it will initialise the
    ///compute daemon:
    ///         - initialise the logger library
    ///         - read the configuration file and parse it and set the daemon global variables
    ///         - if the parameters are'nt provided in configuration file or there was an error loading or finding the configuration file a default set of parameters will be used
    ///
    static void Init();

private:
    //TODO:: implement this method
    static void InitialiseDefaultParameters();
//**********************************************************************************************************************
//This section contains global variables used by all daemons
//**********************************************************************************************************************
public:
    static int g_RequestServerPortNumber;
    static int g_InitialRequestServerThreadPoolSize;
    static std::string g_RequestServerCertificateFilePath;
    static std::string g_RequestServerKeyFilePath;
    static std::string g_TmpDhFilePath;
    static std::string g_ClientCertificateFilePath;
    static std::string g_RequestServerCallbackPassword;
    static std::string g_SheepdogIpAddress;
    static int g_SheepdogPort;
    static std::string g_StoragePoolName;
 };


#endif //CLIOTEST_COMPUTE_H
