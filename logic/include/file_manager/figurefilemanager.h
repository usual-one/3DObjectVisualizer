#ifndef FIGUREFILEMANAGER_H
#define FIGUREFILEMANAGER_H

#include <memory>

#include "logic/include/obj3d/figure/figure.h"
#include "logic/include/utils/xml/xmlmanager.h"
#include "logic/include/file_manager/filemanager.h"

class FigureFileManager{
public:
    FigureFileManager();

    std::shared_ptr<obj3d::Figure> open(const std::string &path);

    void save(const std::shared_ptr<obj3d::Figure> &figure);

private:
    std::unique_ptr<XMLManager> xml_manager_;

    std::unique_ptr<FileManager> file_manager_;

};

#endif // FIGUREFILEMANAGER_H
