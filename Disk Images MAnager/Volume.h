//
// Created by lahmer on 8/20/16.
//

#ifndef CLIOTEST_VOLUME_H
#define CLIOTEST_VOLUME_H

#include "../common.h"
///This class contains all the informations needed to manipulate volumes
class Volume {
    friend class DiskImagesManager;
public:
    ///This is the constructor of this class is called only to create a volume that does'nt exists otherwise
    ///if the volume already exists the application will terminate
    ///@param [in] name the name of the volume should be unique in the storagepool
    ///@param [in] how much we allocate in the physical drive in bytes
    ///@param [in] how much is the logical capacity of the disk
    Volume(const std::string& name , const unsigned long& allocation , const unsigned int& capacity);

    ///This method create an xml volume description that will be used with libvirt to create a volume
    ///@param [in] name the name of the volume should be unique in the storagepool
    ///@param [in] how much we allocate in the physical drive in bytes
    ///@param [in] how much is the logical capacity of the disk
    static std::string CreateVolumeXml(const std::string& name , const unsigned long& allocation , const unsigned int& capacity);
    ///
    Volume(const virStorageVolPtr& volumePtr);
private:
    virStorageVolPtr m_Volume;
};


#endif //CLIOTEST_VOLUME_H
