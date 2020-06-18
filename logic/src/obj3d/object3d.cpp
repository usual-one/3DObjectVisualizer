#include "logic/include/obj3d/object3d.h"

const std::string &obj3d::Object3D::getTag() const{
    return tag_;
}

void obj3d::Object3D::setTag(const std::string &tag) {
    tag_ = tag;
}
