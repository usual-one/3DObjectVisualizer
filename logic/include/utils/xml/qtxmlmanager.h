#ifndef QTXMLMANAGER_H
#define QTXMLMANAGER_H

#include <QtXml/QDomDocument>

#include "logic/include/utils/xml/xmlmanager.h"

class QtXMLManager : public XMLManager {
public:
    obj3d::Figure fromDOMString(const std::string &DOM) override;

    std::string toDOMString(obj3d::Figure &figure) override;

private:
    obj3d::Figure toFigure(QDomDocument &element);

    obj3d::Vertex toVertex(QDomElement &element);

    obj3d::Point3D toPoint3D(QDomElement &element);

    obj3d::Edge toEdge(QDomElement &element);

    QDomElement toDOM(obj3d::Figure &figure);

    QDomElement toDOM(obj3d::Vertex &vertex);

    QDomElement toDOM(const obj3d::Edge &edge);

    QDomElement toDOM(obj3d::Point3D &pt);

    void appendChild(QDomNode &node, QDomNode &child);

    QDomElement createElement(const std::string &name);

    std::vector<QDomElement> elementsByTagName(QDomElement &element, const std::string name);

    QDomElement firstChildElement(QDomNode &node, const std::string &name);

    int getAttributeInt(QDomElement &element, const std::string &name);

    double getAttributeDouble(QDomElement &element, const std::string &name);

    void setAttribute(QDomElement &element, const std::string &name, double value);

    void setAttribute(QDomElement &element, const std::string &name, int value);

    void setAttribute(QDomElement &element, const std::string &name, size_t value);

    QDomDocument current_;

};

#endif // QTXMLMANAGER_H
