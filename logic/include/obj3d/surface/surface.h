#ifndef SURFACE_H
#define SURFACE_H

#include <memory>
#include <vector>

#include "logic/include/obj3d/object3d.h"
#include "logic/include/obj3d/surface/surfaceparameters.h"
#include "logic/include/obj3d/figure/components/vertex.h"

namespace obj3d {
    class Surface;
}

class obj3d::Surface : public obj3d::Object3D {
public:
    Surface(const std::vector<std::vector<double>> &values);

    std::set<std::shared_ptr<obj3d::Vertex>> toVertices() const;

    std::shared_ptr<obj3d::SurfaceParameters> getParameters();

    void setParameters(std::shared_ptr<obj3d::SurfaceParameters> params);

    std::vector<std::vector<double>> &getValues();

private:
    std::shared_ptr<obj3d::SurfaceParameters> calculateParameters() const;

    std::vector<std::vector<double>> normalizeValues() const;

    std::vector<std::vector<obj3d::Point3D>> toPoints3D() const;

    void setConnections(std::vector<std::vector<std::shared_ptr<obj3d::Vertex>>> &vertices) const;

    static size_t count_;

    std::vector<std::vector<double>> values_;

    std::shared_ptr<obj3d::SurfaceParameters> params_;

};

#endif // SURFACE_H
