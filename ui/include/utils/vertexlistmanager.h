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

    bool contains(const obj3d::Vertex3D &vertex);

    obj3d::Vertex3D getCurrent();

    obj3d::Vertex3D getVertex(size_t id);

    std::shared_ptr<std::vector<obj3d::Vertex3D>> getVertices();

    std::set<size_t> getVertexIDs();

    bool hasWidget();

    void removeCurrent();

    void setCurrentID(size_t id);

    void setVertices(const std::vector<obj3d::Vertex3D> &vertices);

    void setWidget(QListWidget *widget);

    static std::string toString(obj3d::Vertex3D &vertex);

    void updateCurrent();

    void updateCurrent(obj3d::Vertex3D &vertex);

    void updateVertices(const std::vector<obj3d::Vertex3D> &vertices);

private:
    bool contains(size_t id);

    int findVertex(size_t id);

    size_t generateFreeID();

    void updateWidget();

    void updateWidget(obj3d::Vertex3D &vertex);

    void updateWidget(const std::vector<obj3d::Vertex3D> &vertices);

    size_t current_id_;

    std::shared_ptr<std::vector<obj3d::Vertex3D>> vertices_;

    QListWidget *widget_;

};

#endif // VERTEXLISTMANAGER_H
