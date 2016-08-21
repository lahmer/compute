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
///This is for test only purposes and it is limited and this should be done in the test process only and nothing else
///it will only allows for the creation and deletion of disk images and nothing more
///This is going to be used only to test the compute module functionalities

class DiskImagesManager {
    friend class Volume;
    friend class Compute;
public:
    ///This method will establish communication with the sheep dog server
    ///and retrieve all the information about the available images there
    static void InitialiseDiskImageManager();
    ///This metod will create a volume
    ///@param [in] name the name of the volume should be unique in the storagepool
    ///@param [in] how much we allocate in the physical drive in bytes
    ///@param [in] how much is the logical capacity of the disk
    static bool CreateVolume(const std::string& name , const unsigned long& capacity);
    ///This metod will delete a volume
    ///@param [in] name the name of the volume should be unique in the storagepool
    static bool DeleteVolume(const std::string& name);
private:
    ///This methode will create a string containig the
    ///xml description of the storagepool defined by the configuration file
    static std::string getStoragePoolXmlDesc();

    static void RefreshStocragePool();
private:
    static virConnectPtr m_LocalHypervisorConnection;
    static virStoragePoolPtr m_StoragePoolConnection;
    static std::map<std::string , std::shared_ptr<Volume>> m_VolumeList;
};


#endif //CLIOTEST_DISKIMAGESMANAGER_H
