#ifndef SURFACEFILEMANAGER_H
#define SURFACEFILEMANAGER_H

#include <memory>
#include <vector>

#include "logic/include/file_manager/csvfilemanager.h"
#include "logic/include/obj3d/surface/surface.h"

class SurfaceFileManager{
public:
    std::shared_ptr<obj3d::Surface> read(const std::string &path);

    void save(const std::vector<std::shared_ptr<obj3d::Surface>> &surfaces);

    void save_as(const std::string &path, const std::vector<std::shared_ptr<obj3d::Surface>> &surfaces);

private:
    CSVFileManager csv_manager_;

    std::string path_;

};

#endif // SURFACEFILEMANAGER_H
