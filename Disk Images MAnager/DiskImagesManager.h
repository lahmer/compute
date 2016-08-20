//
// Created by lahmer on 8/20/16.
//

#ifndef CLIOTEST_DISKIMAGESMANAGER_H
#define CLIOTEST_DISKIMAGESMANAGER_H

#include"../common.h"
class Volume;
///This class will use the local hypervisor to establish communication
///with the sheep dog cluster and to retrieve the information about
///the images stored in the cluster
class DiskImagesManager {
public:
    ///This method will establish communication with the sheep dog server
    ///and retrieve all the information about the available images there
    //TODO::make this methode private so only Compute::init() can call it
    static void InitialiseDiskImageManager();
    ///This is the method responsible for creating new volume for virtual machines
    ///@param vol contains description about the volume properties
    ///@return  the result of the operation 1 if successeded 0 otherwise
    static bool CreateVolume(const Volume& vol);
private:
    ///This methode will create a string containig the
    ///xml description of the storagepool defined by the configuration file
    static std::string getStoragePoolXmlDesc();
private:
    static virConnectPtr m_LocalHypervisorConnection;
    static virStoragePoolPtr m_StoragePoolConnection;
};


#endif //CLIOTEST_DISKIMAGESMANAGER_H
