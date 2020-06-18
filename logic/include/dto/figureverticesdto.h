#ifndef FIGUREVERTICESDTO_H
#define FIGUREVERTICESDTO_H

#include "logic/include/obj3d/figure/components/vertex.h"

class FigureVerticesDTO {
public:
    FigureVerticesDTO(const std::vector<obj3d::Vertex> &vertices);

    std::vector<obj3d::Vertex> &getVertices();

    void setVertices(const std::vector<obj3d::Vertex> &vertices);

private:
    std::vector<obj3d::Vertex> vertices_;

};

#endif // FIGUREVERTICESDTO_H
