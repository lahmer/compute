//
// Created by lahmer on 8/22/16.
//

#include "VirtualMachine.h"
VirtualMachineDescriptor::VirtualMachineDescriptor() {
    m_Booter = NULL;
    m_DeviceFactory = (NULL);
}
ticpp::Element VirtualMachineDescriptor::getxmlDescription() {
    ticpp::Element domain("domain");
    domain.SetAttribute("type","qemu");
    //******************************************************************************************************************
    ticpp::Element domain_name("name", m_Name);
    domain.InsertEndChild(domain_name);
    //******************************************************************************************************************
    ticpp::Element domain_title("title",m_Title);
    domain.InsertEndChild(domain_title);
    //******************************************************************************************************************
    ticpp::Element domain_description("description",m_Descritption);
    domain.InsertEndChild(domain_description);
    //******************************************************************************************************************
    if(m_Booter.get() != NULL){
        ticpp::Element domain_boot = m_Booter.get()->getXml();
        domain.InsertEndChild(domain_boot);
    }
    //******************************************************************************************************************
    if(m_DeviceFactory.get() != NULL){
        ticpp::Element domain_devices = m_DeviceFactory.get()->getXml();
        domain.InsertEndChild(domain_devices);
    }
return domain;
}
std::shared_ptr<DeviceFactory> VirtualMachineDescriptor::getDeviceFactory() {
    if(m_DeviceFactory.get() == NULL)
        m_DeviceFactory.reset(new DeviceFactory());
    return m_DeviceFactory;
}
std::shared_ptr<BiosBootloader> VirtualMachineDescriptor::getBooter() {
    if(m_Booter.get() == NULL)
        m_Booter.reset(new BiosBootloader());
    return m_Booter;
}
void VirtualMachineDescriptor::setName(const std::string &name) {
    m_Name = name;
}
std::string VirtualMachineDescriptor::getName() {
    return m_Name;
}
void VirtualMachineDescriptor::setTitle(const std::string &title) {
    m_Title = title;
}
std::string VirtualMachineDescriptor::getTitle() {
    return m_Title;
}
std::string VirtualMachineDescriptor::GetDescritpion() {
    return m_Descritption;
}
void VirtualMachineDescriptor::setDescritpion(const std::string &Description) {
    m_Descritption = Description;
}