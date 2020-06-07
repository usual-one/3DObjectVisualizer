#include "logic/include/file_manager/figurefilemanager.h"
#include "logic/include/utils/xml/qtxmlmanager.h"

FigureFileManager::FigureFileManager() :
    xml_manager_(std::make_unique<QtXMLManager>()),
    file_manager_(std::make_unique<FileManager>()) {}

std::shared_ptr<obj3d::Figure> FigureFileManager::open(const std::string &path)  {
    obj3d::Figure figure = xml_manager_->fromDOMString(file_manager_->read(path));
    figure.getMeta()->setPath(path);
    return std::make_shared<obj3d::Figure>(figure);
}

void FigureFileManager::save(const std::shared_ptr<obj3d::Figure> &figure) {
    file_manager_->writeTo(*figure->getMeta()->getPath(), xml_manager_->toDOMString(*figure));
}
