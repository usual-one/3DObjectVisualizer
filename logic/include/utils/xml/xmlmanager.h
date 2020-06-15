#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include "logic/include/obj3d/figure/figure.h"
#include <string>

class XMLManager {
public:
    virtual obj3d::Figure fromDOMString(const std::string &DOM) = 0;

    virtual std::string toDOMString(obj3d::Figure &figure) = 0;

};

#endif // XMLMANAGER_H
