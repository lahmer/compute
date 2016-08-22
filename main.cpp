//
// Created by lahmer on 8/16/16.
//
#include "common.h"

int main(){
     Compute::Init();


    VirtualMachineDescriptor vd;
    vd.setName("machine name");
    vd.setTitle("vm title");
    vd.setDescritpion("this is the vm description");
    //*****************************************************************************
    vd.getBooter().get()->addBootDevice(BOOT_DEVICE_DISK);
    vd.getBooter().get()->addBootDevice(BOOT_DEVICE_CDROM);
    vd.getBooter().get()->setBootMenu(3600);
    vd.getBooter().get()->setBootType(BOOT_TYPE_HVM);
    //******************************************************************************
    vd.getDeviceFactory().get()->PushDevice(new HardDisk("ubuntu"));
    vd.getDeviceFactory().get()->PushDevice(new GraphicalDevice(GRAPHICAL_DEVICE_VNC));
    vd.getDeviceFactory().get()->PushDevice(new InputDevice(INPUT_DEVICE_MOUSE));
    //******************************************************************************




    ticpp::Document doc;
    ticpp::Node *root = doc.InsertEndChild(vd.getxmlDescription());

    doc.SaveFile("temp.xml");
    std::ifstream file("temp.xml") ;
    std::stringstream buff ;
    buff<<file.rdbuf();
    std::cout<<buff.str()<<std::endl;

     while(true);
     return 0;
}
