#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <memory>
#include <string>

namespace obj3d {
    class Object3D;
}

class obj3d::Object3D {
public:
    std::shared_ptr<std::string> getTag();

    void setTag(const std::string &tag);

protected:
    std::shared_ptr<std::string> tag_;

};

#endif // OBJECT3D_H
