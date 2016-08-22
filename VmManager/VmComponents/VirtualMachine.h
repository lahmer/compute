//
// Created by lahmer on 8/22/16.
//

#ifndef CLIOTEST_VIRTUALMACHINE_H
#define CLIOTEST_VIRTUALMACHINE_H

#include "../../common.h"
#include "Booter.h"

class DeviceFactory;
class BiosBootloader;

class VirtualMachineDescriptor {
public:
    VirtualMachineDescriptor();
    ticpp::Element getxmlDescription();
    std::shared_ptr<DeviceFactory>  getDeviceFactory();
    std::shared_ptr<BiosBootloader> getBooter();
    void setName(const std::string& name);
    std::string  getName();
    void setTitle(const std::string& title);
    std::string  getTitle();
    void setDescritpion(const std::string& Description);
    std::string GetDescritpion();
private:
     std::shared_ptr<DeviceFactory> m_DeviceFactory;
     std::shared_ptr<BiosBootloader> m_Booter;
     std::string m_Name;
     std::string m_Title;
     std::string m_Descritption;
};


#endif //CLIOTEST_VIRTUALMACHINE_H
