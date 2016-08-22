//
// Created by lahmer on 8/22/16.
//

#include "DeviceFactory.h"

HardDisk::HardDisk(const std::string &name) {
    m_DiskName = name;
}
ticpp::Element HardDisk::getDeviceXml() {
    ticpp::Element disk("disk");
    disk.SetAttribute("type","network");
    //******************************************************************************************************************
    ticpp::Element source("source");
    source.SetAttribute("protocol","sheepdog");
    source.SetAttribute("name",m_DiskName);
    ticpp::Element host("host");
    host.SetAttribute("name",Compute::g_SheepdogIpAddress);
    host.SetAttribute("port",Compute::g_SheepdogPort);
    source.InsertEndChild(host);
        disk.InsertEndChild(source);
    //******************************************************************************************************************
    ticpp::Element target("target");
    target.SetAttribute("dev","hda");
    target.SetAttribute("bus","ide");
    disk.InsertEndChild(target);
    return disk;
}

InputDevice::InputDevice(const unsigned int &deviceType):m_DeviceType(deviceType) {};
ticpp::Element InputDevice::getDeviceXml() {
    std::string type;
    std::string bus = "usb";
    switch (m_DeviceType){
        case INPUT_DEVICE_KEYBOARD:{
            type = "keyboard";
            break;
        }
        case INPUT_DEVICE_MOUSE:{
            type = "mouse";
            break;
        }
        default:{
            LOGE<<"getting wrong device number";
            std::terminate();
        }
    }
    ticpp::Element input("input");
    input.SetAttribute("type",type);
    input.SetAttribute("bus",bus);
    return input;

}

GraphicalDevice::GraphicalDevice(const unsigned int& GraphicalDeviceType): m_GraphicalDeviceType(GraphicalDeviceType) {};

ticpp::Element GraphicalDevice::getDeviceXml() {
    ticpp::Element graphics("graphics");
    switch (m_GraphicalDeviceType){
        case GRAPHICAL_DEVICE_VNC:{
            graphics.SetAttribute("type","vnc");
            graphics.SetAttribute("port",-1);
            graphics.SetAttribute("autoport","yse");
            return graphics;
        }
        default:{
            LOGE<<"This is not an valid Graphical Device id";
            std::terminate();
        }
    }
}

void DeviceFactory::PushDevice(Device* device) {
    m_DeviceList.push_back(device);
}

ticpp::Element DeviceFactory::getXml() {
    ticpp::Element devices("devices");
    for (int i = 0; i < m_DeviceList.size(); ++i) {
        devices.InsertEndChild(m_DeviceList.at(i)->getDeviceXml());
    }
    return devices;
}
