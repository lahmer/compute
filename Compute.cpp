//
// Created by lahmer on 8/16/16.
//

#include "Compute.h"
int Compute::g_RequestServerPortNumber;
std::string Compute::g_RequestServerCertificateFilePath;
std::string Compute::g_RequestServerKeyFilePath;
std::string Compute::g_TmpDhFilePath;
std::string Compute::g_ClientCertificateFilePath;
std::string Compute::g_RequestServerCallbackPassword;
int Compute::g_InitialRequestServerThreadPoolSize;
std::string Compute::g_SheepdogIpAddress;
int Compute::g_SheepdogPort;
std::string Compute::g_StoragePoolName;


 void Compute::Init() {
    plog::init(plog::debug, "ComputeLogFile.txt");
    libconfig::Config cnf;
    try{
        cnf.readFile("compute.conf");
    }catch (libconfig::FileIOException &e){
        LOGE<<"configuration file not founded Trying Default configuration:"<<e.what();
        InitialiseDefaultParameters();
        return;
    }catch (libconfig::ParseException& e){
        LOGE<<"Configuration file parse error "<<e.what();
        InitialiseDefaultParameters();
        return ;
    }
     //*****************************************************************************************************************
     //Here we start reading the configuration file and setting all the parameters
     //*****************************************************************************************************************
     try{
        int temp = cnf.lookup("request_server_port");
         g_RequestServerPortNumber = temp;
     }catch (libconfig::SettingNotFoundException){
         //TODO::fix this conversion warrning
        g_ClientCertificateFilePath = REQUEST_SERVER_DEFAULT_PORT;
         return;
     }
     try{
         std::string temp = cnf.lookup("server_certificate_path");
         g_RequestServerCertificateFilePath = temp;
     }catch (libconfig::SettingNotFoundException){
         g_RequestServerCertificateFilePath = "";
         return;
     }
     try{
         std::string temp = cnf.lookup("server_private_key_path");
         g_RequestServerKeyFilePath = temp;
     }catch (libconfig::SettingNotFoundException){
         g_RequestServerKeyFilePath = "";
         return;
     }
     try{
         std::string temp = cnf.lookup("tmp_dh_file_path");
         g_TmpDhFilePath = temp;
     }catch (libconfig::SettingNotFoundException){
         g_TmpDhFilePath = "";
         return;
     }
     try{
         std::string temp = cnf.lookup("client_certificate_path");
         g_ClientCertificateFilePath = temp;
     }catch (libconfig::SettingNotFoundException){
         g_ClientCertificateFilePath = "";
         return;
     }
     try{
         std::string temp = cnf.lookup("request_server_callback_password");
         g_RequestServerCallbackPassword = temp;
     }catch (libconfig::SettingNotFoundException){
         g_RequestServerCallbackPassword = "";
         return;
     }

     try{
         int temp = cnf.lookup("request_server_initial_thread_pool_size");
         g_InitialRequestServerThreadPoolSize = temp;
     }catch (libconfig::SettingNotFoundException){
         g_InitialRequestServerThreadPoolSize = 10;
         return;
     }

     try{
         std::string temp = cnf.lookup("disk_images_manager_sheepdog_ip_address");
         g_SheepdogIpAddress = temp;
     }catch (libconfig::SettingNotFoundException){
         g_SheepdogIpAddress = "192.168.1.104";
         return;
     }

     try{
         int temp = cnf.lookup("disk_images_manager_sheepdog_port");
         g_SheepdogPort = temp;
     }catch (libconfig::SettingNotFoundException){
         g_SheepdogPort = 7000;
         return;
     }

     try{
         std::string temp = cnf.lookup("disk_images_manager_default_storage_pool_name");
         g_StoragePoolName = temp;
     }catch (libconfig::SettingNotFoundException){
         g_StoragePoolName = "sheepdogstoragepool";
         return;
     }
//**********************************************************************************************************************
     // Initisalising the Request server
     //*****************************************************************************************************************
     ResquestServer::InitResquestServer();
     //*****************************************************************************************************************
     //Initialising the task queue engine
     //*****************************************************************************************************************
     TaskQueueManager::InitialiseTaskQueueManager();
     //*****************************************************************************************************************
     //initialising the temporary disk image manager
     //*****************************************************************************************************************
     DiskImagesManager::InitialiseDiskImageManager();
 }

void Compute::InitialiseDefaultParameters() {
    g_ClientCertificateFilePath = REQUEST_SERVER_DEFAULT_PORT;
}