//
// Created by lahmer on 8/22/16.
//

#include "Booter.h"

BiosBootloader::BiosBootloader() {
    m_BootType = BOOT_TYPE_HVM;
    m_BootMenu = false;
}
void BiosBootloader::addBootDevice(BootDevices BootDevice) {
    switch (BootDevice){
        case BOOT_DEVICE_CDROM:{
            m_BootDevices.push_back(BootDevice);
            break;
        }
        case BOOT_DEVICE_DISK:{
            m_BootDevices.push_back(BootDevice);
            break;
        }
        default:{
            LOGE<<"unrecognized boot device ";
            std::terminate();
        }
    }
}
void BiosBootloader::setBootMenu(const unsigned int &timeout) {
    m_BootMenu = true;
    m_BootMenuTimeOut = timeout;
}
void BiosBootloader::setBootType(BootType type) {
    if(type == BOOT_TYPE_HVM || type == BOOT_TYPE_LINUX)
        m_BootType = type;
    else{
        LOGE<<"trying to set undefined boot type";
        std::terminate();
    }
}
ticpp::Element BiosBootloader::getXml() {
    ticpp::Element os("os");
    //******************************************************************************************************************
    ticpp::Element *type;
    if (m_BootType == BOOT_TYPE_HVM)
        type = new ticpp::Element("type", "hvm");
    else if (m_BootType == BOOT_TYPE_LINUX)
        type = new ticpp::Element("type", "linux");
    os.InsertEndChild(*type);
    //******************************************************************************************************************
    for (auto it : m_BootDevices) {
        ticpp::Element bootdevice("boot");
        switch (it) {
            case BOOT_DEVICE_DISK: {
                bootdevice.SetAttribute("dev", "hd");
                break;
            }
            case BOOT_DEVICE_CDROM: {
                bootdevice.SetAttribute("dev", "cdrom");
                break;
            }
            default: {
                LOGE << "unknown bios device ";
                std::terminate();
            }
        }
    }
    //******************************************************************************************************************
    if (m_BootMenu) {
        ticpp::Element bootMenu("bootmenu");
        bootMenu.SetAttribute("enable", "yes");
        bootMenu.SetAttribute("timout", m_BootMenuTimeOut);
        os.InsertEndChild(bootMenu);
    }
    return os;
}
