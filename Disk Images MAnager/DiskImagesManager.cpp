//
// Created by lahmer on 8/20/16.
//

#include "DiskImagesManager.h"

virConnectPtr DiskImagesManager::m_LocalHypervisorConnection;
virStoragePoolPtr  DiskImagesManager::m_StoragePoolConnection;


void DiskImagesManager::InitialiseDiskImageManager() {
    //establishing communication with local hypervisor
    m_LocalHypervisorConnection = virConnectOpen("qemu:///system");
    if(m_LocalHypervisorConnection == NULL){
        LOGE<<"can't establish communication with the local hypervisor at :"<<"qemu:///system";
        std::terminate();
    }
    //create the sheepdog storage pool this pool is not persistent at the restart of the host it will be deleted
    //first we check if its already exists and update its parameters otherwise we create it from scratch
    virStoragePoolPtr** storage_pool ;
    int n = virConnectListAllStoragePools(m_LocalHypervisorConnection,storage_pool,
    VIR_CONNECT_LIST_STORAGE_POOLS_ACTIVE|VIR_CONNECT_LIST_STORAGE_POOLS_INACTIVE);

    bool exists = false;
    for(int i = 0 ;  i  < n ; ++i){
        std::cout<<virStoragePoolGetName(**storage_pool)<<"  "<<Compute::g_StoragePoolName.c_str()<<std::endl;
         if(!strcmp(virStoragePoolGetName(**storage_pool),Compute::g_StoragePoolName.c_str())){
            exists = true;
            break;
        }
        (*storage_pool)++;
     }
    /**
     * if the storage pool exists we check if its active and activate it if it is not
     * then we check for the parameters if they are consistent with the configuration file
     * and update them if any problem
     */


    if(exists){
        //we first get the pointer to the storage pool
        m_StoragePoolConnection = virStoragePoolLookupByName(m_LocalHypervisorConnection,Compute::g_StoragePoolName.c_str());
        if(m_StoragePoolConnection == NULL){
            LOGE<<"can't establish connection to the storage pool "<<Compute::g_StoragePoolName;
            std::terminate();
        }
        //check if the storage pool is active
        if(!virStoragePoolIsActive(m_StoragePoolConnection)){
            //TODO::fix the problem of the inability to activate the pool
            //we activate the pool
            int code = virStoragePoolBuild(m_StoragePoolConnection,VIR_STORAGE_POOL_BUILD_NO_OVERWRITE);
            if(code != 0){
                LOGE<<"can't activate the storage pool ";
                std::terminate();
            }
            if(!virStoragePoolIsActive(m_StoragePoolConnection)){
                LOGE<<"error this pool should be active by now ";
                std::terminate();
            }
        }
        //check the parameters of the storage pool
        //char* xml = virStoragePoolGetXMLDesc(m_StoragePoolConnection,VIR_STORAGE_XML_INACTIVE);
        //std::cout<<xml<<std::endl;
    }else{
        /**
         * This is the case of the storage pool not defined
         *      -we create a non persistent storage pool that connect to the sheepdog cluster
         */
        std::string xml = getStoragePoolXmlDesc();
        m_StoragePoolConnection = virStoragePoolCreateXML(m_LocalHypervisorConnection,xml.c_str(),0);
        if(m_StoragePoolConnection == NULL){
            LOGE<<"error when creating the storage pool ";
            std::terminate();
        }
        virStoragePoolFree(m_StoragePoolConnection);
     }
}

std::string DiskImagesManager::getStoragePoolXmlDesc() {
    ticpp::Document doc;
    ticpp::Node *root = doc.InsertEndChild(ticpp::Element("pool"));
    root->ToElement()->SetAttribute("type","sheepdog");
    //******************************************************************************************************************
    ticpp::Element name("name",Compute::g_StoragePoolName);
    root->InsertEndChild(name);
    //******************************************************************************************************************
    ticpp::Element source("source");
    ticpp::Element source_name("name","mysheeppool");
    ticpp::Element host("host");
    host.SetAttribute("name",Compute::g_SheepdogIpAddress);
    host.SetAttribute("port",std::to_string(Compute::g_SheepdogPort));
    source.InsertEndChild(source_name);
    source.InsertEndChild(host);
    root->InsertEndChild(source);



    doc.SaveFile("temp.xml");
    std::ifstream file("temp.xml") ;
    std::stringstream buff ;
    buff<<file.rdbuf();
    std::cout<<buff.str()<<std::endl;
    return  buff.str();
}

bool DiskImagesManager::CreateVolume(const Volume &vol) {

}