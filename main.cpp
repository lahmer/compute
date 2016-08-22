//
// Created by lahmer on 8/16/16.
//
#include "common.h"

int main(){
     Compute::Init();

    DeviceFactory factory;
    factory.PushDevice(new HardDisk("ubuntu"));
    factory.PushDevice(new GraphicalDevice(GRAPHICAL_DEVICE_VNC));
    factory.PushDevice(new InputDevice(INPUT_DEVICE_MOUSE));

    ticpp::Document doc;
    ticpp::Node *root = doc.InsertEndChild(factory.getXml());

    doc.SaveFile("temp.xml");
    std::ifstream file("temp.xml") ;
    std::stringstream buff ;
    buff<<file.rdbuf();
    std::cout<<buff.str()<<std::endl;

     while(true);
     return 0;
}
