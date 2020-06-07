#include "logic/include/file_manager/obj3dfilemanager.h"
#include "logic/include/file_manager/exception/fileopeningexception.h"
#include "config.h"

Scene Obj3DFileManager::read(const std::string &path) {
    path_ = path;

    Scene scene;
    if (isSurfacePath(path)) {
        std::shared_ptr<obj3d::Surface> surface = surface_manager_.read(path);
        scene.appendSurface(surface);
        scene.appendFigure(std::make_shared<obj3d::Figure>(*surface));
    } else if (isFigurePath(path)) {
        scene.appendFigure(figure_manager_.open(path));
    } else {
        throw FileOpeningException(UNKNOWN_FORMAT_MESSAGE);
    }
    return scene;
}

void Obj3DFileManager::saveFigure(std::shared_ptr<obj3d::Figure> figure) {
    figure_manager_.save(figure);
}

bool Obj3DFileManager::isFigureInside() {
    return isFigurePath(path_);
}

bool Obj3DFileManager::isSurfaceInside() {
    return isSurfacePath(path_);
}

bool Obj3DFileManager::isFigurePath(const std::string &path) {
    return std::equal(FIGURE_FILE_FORMAT.rbegin(), FIGURE_FILE_FORMAT.rend(), path.rbegin());
}

bool Obj3DFileManager::isSurfacePath(const std::string &path) {
    return std::equal(SURFACE_FILE_FORMAT.rbegin(), SURFACE_FILE_FORMAT.rend(), path.rbegin());
}
