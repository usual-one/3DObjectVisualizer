#ifndef VERTEXLISTMANAGER_H
#define VERTEXLISTMANAGER_H

#include "logic/include/obj3d/figure/components/vertex.h"

#include <QListWidget>

class VertexListManager {
public:
    VertexListManager();

    size_t add();

    void add(obj3d::Vertex &vertex);

    void clear();

    bool contains(const obj3d::Vertex &vertex);

    obj3d::Vertex getCurrent();

    obj3d::Vertex getVertex(size_t id);

    std::shared_ptr<std::vector<obj3d::Vertex>> getVertices();

    std::set<size_t> getVertexIDs();

    bool hasSelected();

    bool hasWidget();

    void removeCurrent();

    void setCurrentID(size_t id);

    void setVertices(const std::vector<obj3d::Vertex> &vertices);

    void setWidget(QListWidget *widget);

    static std::string toString(obj3d::Vertex &vertex);

    void updateCurrent();

    void updateCurrent(obj3d::Vertex &vertex);

    void updateVertices(const std::vector<obj3d::Vertex> &vertices);

private:
    bool contains(size_t id);

    int findVertex(size_t id);

    size_t generateFreeID();

    void updateWidget();

    void updateWidget(obj3d::Vertex &vertex);

    void updateWidget(const std::vector<obj3d::Vertex> &vertices);

    size_t current_id_;

    std::shared_ptr<std::vector<obj3d::Vertex>> vertices_;

    QListWidget *widget_;

};

#endif // VERTEXLISTMANAGER_H
