#ifndef VERTEXLISTMANAGER_H
#define VERTEXLISTMANAGER_H

#include "logic/include/obj3d/figure/components/vertex3d.h"

#include <QListWidget>

class VertexListManager {
public:
    VertexListManager();

    size_t add();

    void add(obj3d::Vertex3D &vertex);

    void clear();

    obj3d::Vertex3D getCurrent();

    obj3d::Vertex3D getVertex(size_t id);

    std::shared_ptr<std::vector<obj3d::Vertex3D>> getVertices();

    bool hasWidget();

    void removeCurrent();

    void setCurrentID(size_t id);

    void setVertices(const std::vector<obj3d::Vertex3D> &vertices);

    void setWidget(QListWidget *widget);

    void updateCurrent();

    void updateCurrent(obj3d::Vertex3D &vertex);

    void updateVertices(const std::vector<obj3d::Vertex3D> &vertices);

private:
    int findVertex(size_t id);

    size_t generateFreeID();

    bool isInside(size_t id);

    bool isInside(const obj3d::Vertex3D &vertex);

    std::string toString(obj3d::Vertex3D &vertex);

    void updateWidget();

    void updateWidget(obj3d::Vertex3D &vertex);

    void updateWidget(const std::vector<obj3d::Vertex3D> &vertices);

    size_t current_id_;

    std::shared_ptr<std::vector<obj3d::Vertex3D>> vertices_;

    QListWidget *widget_;

};

#endif // VERTEXLISTMANAGER_H
