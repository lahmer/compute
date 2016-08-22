//
// Created by lahmer on 8/22/16.
//

#ifndef CLIOTEST_ABSTRACTVMFACTORY_H
#define CLIOTEST_ABSTRACTVMFACTORY_H

#include "../../common.h"

class AbstractVmFactory {
public:
    virtual ticpp::Element getXml() = 0 ;
};


#endif //CLIOTEST_ABSTRACTVMFACTORY_H
