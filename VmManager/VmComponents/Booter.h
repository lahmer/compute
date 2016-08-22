//
// Created by lahmer on 8/22/16.
//

#ifndef CLIOTEST_BOOTER_H
#define CLIOTEST_BOOTER_H

#include "../../common.h"

class AbstractBooter {
public:
    ticpp::Element getXml();
};

enum BootDevices{BOOT_DEVICE_CDROM,BOOT_DEVICE_DISK};
enum BootType{BOOT_TYPE_HVM,BOOT_TYPE_LINUX};
class BiosBootloader : public AbstractBooter{
public:
    BiosBootloader();
    ticpp::Element getXml();
    void addBootDevice(BootDevices BootDevice);
    void setBootType(BootType type);
    void setBootMenu(const unsigned int& timeout);
private:
    std::vector<BootDevices> m_BootDevices;
    BootType  m_BootType;
    bool m_BootMenu;
    unsigned int m_BootMenuTimeOut;
};


#endif //CLIOTEST_BOOTER_H
