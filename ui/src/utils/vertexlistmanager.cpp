#include "config.h"
#include "ui/include/utils/vertexlistmanager.h"
#include "ui/include/utils/exceptions/vertexlistexception.h"

VertexListManager::VertexListManager() :
    vertices_(std::make_shared<std::vector<obj3d::Vertex3D>>()),
    widget_(nullptr) {}

size_t VertexListManager::add() {
    size_t id = generateFreeID();
    obj3d::Vertex3D vertex(obj3d::Vector3D(), id);
    add(vertex);
    return id;
}

void VertexListManager::add(obj3d::Vertex3D &vertex) {
    if (!isInside(vertex)) {
        vertices_->push_back(vertex);
    }
    updateWidget(vertex);
}

void VertexListManager::clear() {
    vertices_->clear();
    if (hasWidget()) {
        widget_->clear();
    }
}

obj3d::Vertex3D VertexListManager::getCurrent() {
    return getVertex(current_id_);
}

obj3d::Vertex3D VertexListManager::getVertex(size_t id) {
    for (auto vertex : *vertices_) {
        if (vertex.getID() == id) {
            return vertex;
        }
    }
    throw VertexListException(VERTEX_NOT_FOUND_MESSAGE);
}

std::shared_ptr<std::vector<obj3d::Vertex3D> > VertexListManager::getVertices() {
    return vertices_;
}

bool VertexListManager::hasWidget() {
    return widget_ != nullptr;
}

void VertexListManager::removeCurrent() {
    for (auto it = vertices_->begin(); it < vertices_->end(); it++) {
        if (it->getID() == current_id_) {
            vertices_->erase(it);
            break;
        }
    }
    widget_->clear();
    updateWidget();
}

void VertexListManager::setCurrentID(size_t id) {
    if (!isInside(id)) {
        return;
    }
    widget_->setCurrentRow(findVertex(id));
    current_id_ = id;
}

void VertexListManager::setVertices(const std::vector<obj3d::Vertex3D> &vertices) {
    clear();
    vertices_->insert(vertices_->begin(), vertices.begin(), vertices.end());
    updateWidget();
}

void VertexListManager::setWidget(QListWidget *widget) {
    widget_ = widget;
    updateWidget();
}

void VertexListManager::updateCurrent() {
    current_id_ = vertices_->at(widget_->currentRow()).getID();
}

void VertexListManager::updateCurrent(obj3d::Vertex3D &vertex) {
    vertices_->at(findVertex(current_id_)).setPosition(*vertex.getPosition());
    QListWidgetItem *item = widget_->currentItem();
    item->setText(QString::fromStdString(toString(vertex)));
}

void VertexListManager::updateVertices(const std::vector<obj3d::Vertex3D> &vertices) {
    for (auto vertex : vertices) {
        add(vertex);
    }
}

int VertexListManager::findVertex(size_t id) {
    for (size_t i = 0; i < vertices_->size(); i++) {
        if (vertices_->at(i).getID() == id) {
            return i;
        }
    }
    return -1;
}

size_t VertexListManager::generateFreeID() {
    size_t free_id = 1;
    while (true) {
        if (findVertex(free_id) == -1) {
            break;
        }
        free_id++;
    }
    return free_id;
}

bool VertexListManager::isInside(size_t id) {
    for (auto vertex : *vertices_) {
        if (vertex.getID() == id) {
            return true;
        }
    }
    return false;
}

bool VertexListManager::isInside(const obj3d::Vertex3D &vertex) {
    return isInside(vertex.getID());
}

std::string VertexListManager::toString(obj3d::Vertex3D &vertex) {
    obj3d::Vector3D pos = *vertex.getPosition();
    return std::to_string(vertex.getID()) +
            " (" + std::to_string(pos.getX()) +
            ", " + std::to_string(pos.getY()) +
            ", " + std::to_string(pos.getZ()) + ")";
}

void VertexListManager::updateWidget() {
    updateWidget(*vertices_);
}

void VertexListManager::updateWidget(obj3d::Vertex3D &vertex) {
    QString vertex_str = QString::fromStdString(toString(vertex));
    widget_->addItem(vertex_str);
}

void VertexListManager::updateWidget(const std::vector<obj3d::Vertex3D> &vertices) {
    for (auto vertex : vertices) {
        updateWidget(vertex);
    }
}
