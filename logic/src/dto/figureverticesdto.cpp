#include "logic/include/dto/figureverticesdto.h"

FigureVerticesDTO::FigureVerticesDTO(const std::vector<obj3d::Vertex> &vertices) :
    vertices_(vertices) {}

std::vector<obj3d::Vertex> &FigureVerticesDTO::getVertices() {
    return vertices_;
}

void FigureVerticesDTO::setVertices(const std::vector<obj3d::Vertex> &vertices) {
    vertices_ = vertices;
}
