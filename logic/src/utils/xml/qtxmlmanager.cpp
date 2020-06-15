#include "config.h"
#include "logic/include/utils/xml/qtxmlmanager.h"

obj3d::Figure QtXMLManager::fromDOMString(const std::string &DOM) {
    current_.clear();
    current_.setContent(QString::fromStdString(DOM));
    return toFigure(current_);
}

std::string QtXMLManager::toDOMString(obj3d::Figure &figure) {
    current_.clear();
    QDomElement figure_DOM = toDOM(figure);
    appendChild(current_, figure_DOM);
    return current_.toString().toStdString();
}

obj3d::Figure QtXMLManager::toFigure(QDomDocument &element) {
    obj3d::Figure figure;
    QDomElement figure_DOM = firstChildElement(element, XML_TAG_FIGURE);

    QDomElement vertices_DOM = firstChildElement(figure_DOM, XML_TAG_VERTICES);
    for (auto vertex_element : elementsByTagName(vertices_DOM, XML_TAG_VERTEX)) {
        figure.addVertex(std::make_shared<obj3d::Vertex>(toVertex(vertex_element)));
    }

    QDomElement edges_DOM = firstChildElement(figure_DOM, XML_TAG_EDGES);
    for (auto edge_element : elementsByTagName(edges_DOM, XML_TAG_EDGE)) {
        figure.addEdge(std::make_shared<obj3d::Edge>(toEdge(edge_element)));
    }

    return figure;
}

obj3d::Vertex QtXMLManager::toVertex(QDomElement &element) {
    obj3d::Point3D pos = toPoint3D(elementsByTagName(element, XML_TAG_POSITION)[0]);
    return obj3d::Vertex(pos, getAttributeInt(element, XML_ATTRIBUTE_ID));
}

obj3d::Point3D QtXMLManager::toPoint3D(QDomElement &element) {
    return obj3d::Point3D(getAttributeDouble(element, XML_ATTRIBUTE_X),
                          getAttributeDouble(element, XML_ATTRIBUTE_Y),
                          getAttributeDouble(element, XML_ATTRIBUTE_Z));
}

obj3d::Edge QtXMLManager::toEdge(QDomElement &element) {
    return obj3d::Edge(getAttributeInt(element, XML_ATTRIBUTE_BEGIN),
                       getAttributeInt(element, XML_ATTRIBUTE_END));
}

QDomElement QtXMLManager::toDOM(obj3d::Figure &figure) {
    QDomElement figure_DOM = createElement(XML_TAG_FIGURE);

    QDomElement vertices_DOM = createElement(XML_TAG_VERTICES);
    for (auto vertex : figure.getVertices()) {
        QDomElement vertex_DOM = toDOM(*vertex);
        appendChild(vertices_DOM, vertex_DOM);
    }
    appendChild(figure_DOM, vertices_DOM);

    QDomElement edges_DOM = createElement(XML_TAG_EDGES);
    for (auto edge : figure.getEdges()) {
        QDomElement edge_DOM = toDOM(*edge);
        appendChild(edges_DOM, edge_DOM);
    }
    appendChild(figure_DOM, edges_DOM);

    return figure_DOM;
}

QDomElement QtXMLManager::toDOM(obj3d::Vertex &vertex) {
    QDomElement vertex_DOM = createElement(XML_TAG_VERTEX);

    setAttribute(vertex_DOM, XML_ATTRIBUTE_ID, vertex.getID());

    QDomElement position_DOM = toDOM(*vertex.getPosition());
    position_DOM.setTagName(QString::fromStdString(XML_TAG_POSITION));
    appendChild(vertex_DOM, position_DOM);

    return vertex_DOM;
}

QDomElement QtXMLManager::toDOM(const obj3d::Edge &edge) {
    QDomElement edge_DOM = createElement(XML_TAG_EDGE);
    setAttribute(edge_DOM, XML_ATTRIBUTE_BEGIN, edge.getBegin());
    setAttribute(edge_DOM, XML_ATTRIBUTE_END, edge.getEnd());
    return edge_DOM;
}

QDomElement QtXMLManager::toDOM(obj3d::Point3D &pt) {
    QDomElement pt_DOM = createElement(XML_TAG_POINT);
    setAttribute(pt_DOM, XML_ATTRIBUTE_X, pt.getX());
    setAttribute(pt_DOM, XML_ATTRIBUTE_Y, pt.getY());
    setAttribute(pt_DOM, XML_ATTRIBUTE_Z, pt.getZ());
    return pt_DOM;
}

void QtXMLManager::appendChild(QDomNode &node, QDomNode &child) {
    node.appendChild(child);
}

QDomElement QtXMLManager::createElement(const std::string &name) {
    return current_.createElement(QString::fromStdString(name));
}

std::vector<QDomElement> QtXMLManager::elementsByTagName(QDomElement &element, const std::string name) {
    QDomNodeList list = element.elementsByTagName(QString::fromStdString(name));
    std::vector<QDomElement> elements;

    for (int i = 0; i < list.size(); i++) {
        QDomNode node = list.at(i);
        if (node.isElement()) {
            elements.push_back(node.toElement());
        }
    }

    return elements;
}

QDomElement QtXMLManager::firstChildElement(QDomNode &node, const std::string &name) {
    return node.firstChildElement(QString::fromStdString(name));
}

int QtXMLManager::getAttributeInt(QDomElement &element, const std::string &name) {
    return element.attribute(QString::fromStdString(name)).toInt();
}

double QtXMLManager::getAttributeDouble(QDomElement &element, const std::string &name) {
    return element.attribute(QString::fromStdString(name)).toDouble();
}

void QtXMLManager::setAttribute(QDomElement &element, const std::string &name, double value) {
    element.setAttribute(QString::fromStdString(name), value);
}

void QtXMLManager::setAttribute(QDomElement &element, const std::string &name, int value) {
    element.setAttribute(QString::fromStdString(name), value);
}

void QtXMLManager::setAttribute(QDomElement &element, const std::string &name, size_t value) {
    setAttribute(element, name, (int) value);
}
