//
// Created by lahmer on 8/22/16.
//

#ifndef CLIOTEST_DEVICEFACTORY_H
#define CLIOTEST_DEVICEFACTORY_H

#include "../../common.h"
class Device{
public:
    Device(){};
        virtual ticpp::Element getDeviceXml() = 0 ;
};

class HardDisk : public Device{
public :
    HardDisk(const std::string& name  );
    ticpp::Element getDeviceXml();
private:
    std::string m_DiskName;
};
enum InputDeviceType{INPUT_DEVICE_MOUSE,
                    INPUT_DEVICE_KEYBOARD
                    };
class InputDevice : public Device{
public:
    InputDevice(const unsigned int& deviceType);
    ticpp::Element getDeviceXml();
private:
    unsigned int m_DeviceType;
};

enum GraphicalDeviceType{GRAPHICAL_DEVICE_VNC};

class GraphicalDevice : public Device{
public:
    GraphicalDevice(const unsigned int& GraphicalDeviceType);
    ticpp::Element getDeviceXml();
private:
    unsigned int m_GraphicalDeviceType;
};

class DeviceFactory : public AbstractVmFactory{
public:
    DeviceFactory();
    ticpp::Element getXml();
    void PushDevice( Device* device);
private:
    std::vector<Device*> m_DeviceList;
};

#endif //CLIOTEST_DEVICEFACTORY_H
