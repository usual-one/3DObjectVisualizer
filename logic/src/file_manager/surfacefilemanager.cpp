#include "logic/include/file_manager/surfacefilemanager.h"
#include "config.h"

std::shared_ptr<obj3d::Surface> SurfaceFileManager::read(const std::string &path) {
    path_ = path;
    std::vector<std::vector<double>> surface_values = csv_manager_.readIntoDouble(path, CSV_VALUE_SEPARATOR);
    return std::make_shared<obj3d::Surface>(surface_values);
}
