//
// Created by lahmer on 8/20/16.
//

#include "Volume.h"

Volume::Volume(const std::string &name, const unsigned long &allocation, const unsigned int &capacity) {
    //here we are okay we can create the image
    std::string VolumeXmlDescription = CreateVolumeXml(name,allocation,capacity);
    m_Volume = virStorageVolCreateXML(DiskImagesManager::m_StoragePoolConnection,VolumeXmlDescription.c_str(),
                                      0);
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
    ticpp::Element volume_name("name",name);
    root->InsertEndChild(volume_name);
    //******************************************************************************************************************
    ticpp::Element volume_key("key","sheep/"+name);
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
    //std::cout<<buff.str()<<std::endl;
    return  buff.str();
}

Volume::Volume(const virStorageVolPtr &volumePtr) {
    m_Volume = volumePtr;
}

std::string Volume::GetVolumeName(const virStorageVolPtr &ptr) {
    const char* name = virStorageVolGetName(ptr);
    if (name == NULL){
        LOGE<<"ERROR when fetching the volume name ";
        std::terminate();
    }
    std::string result = name ;
    return  result;
}

std::string Volume::GetVolumePath(const virStorageVolPtr &ptr) {
    const char* name = virStorageVolGetPath(ptr);
    if (name == NULL){
        LOGE<<"ERROR when fetching the volume name ";
        std::terminate();
    }
    std::string result = name ;
    return  result;
}