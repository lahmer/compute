//
// Created by lahmer on 8/20/16.
//

#include "Volume.h"

Volume::Volume(const std::string &name, const unsigned long &allocation, const unsigned int &capacity) {
    //first we check if the volume already exists
    virStorageVolPtr** volumes;
    int n = virStoragePoolListAllVolumes(DiskImagesManager::m_StoragePoolConnection,volumes ,0);
    for (int i = 0; i < n; ++i) {
        if(!strcmp(virStorageVolGetName(*((*(volumes))++)),name.c_str())){
            LOGE<<"Trying to add a volume that already exists"<<name;
            std::terminate();
        }
    }
    //here we are okay we can create the image
    std::string VolumeXmlDescription = CreateVolumeXml(name,allocation,capacity);
    m_Volume = virStorageVolCreateXML(DiskImagesManager::m_StoragePoolConnection,VolumeXmlDescription.c_str(),
                                      VIR_STORAGE_VOL_CREATE_PREALLOC_METADATA);
    if(m_Volume == NULL){
        LOGE<<"could'nt create the volume "<<name;
        std::terminate();
    }
}

std::string Volume::CreateVolumeXml(const std::string &name, const unsigned long &allocation,
                                    const unsigned int &capacity) {

    ticpp::Document doc;
    ticpp::Node *root = doc.InsertEndChild(ticpp::Element("volume"));
    //******************************************************************************************************************
    ticpp::Element volume_name(name);
    root->InsertEndChild(volume_name);
    //******************************************************************************************************************
    ticpp::Element volume_key("sheep/"+name);
    root->InsertEndChild(volume_key);
    //******************************************************************************************************************
    ticpp::Element volume_capacity("capacity",capacity);
    root->InsertEndChild(volume_capacity);
    //******************************************************************************************************************
    ticpp::Element volume_allocation("allocation",allocation);
    root->InsertEndChild(volume_allocation);
    //******************************************************************************************************************
    ticpp::Element volume_target("target");
    ticpp::Element volume_path("path","sheepdog:"+name);
        volume_target.InsertEndChild(volume_path);
    root->InsertEndChild(volume_target);

    doc.SaveFile("temp.xml");
    std::ifstream file("temp.xml") ;
    std::stringstream buff ;
    buff<<file.rdbuf();
    std::cout<<buff.str()<<std::endl;
    return  buff.str();
}