#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <memory>
#include <string>

namespace obj3d {
    class Object3D;
}

class obj3d::Object3D {
public:
    const std::string &getTag() const;

    void setTag(const std::string &tag);

protected:
    std::string tag_;

};

#endif // OBJECT3D_H
