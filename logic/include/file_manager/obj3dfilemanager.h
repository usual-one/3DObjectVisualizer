#ifndef OBJ3DFILEMANAGER_H
#define OBJ3DFILEMANAGER_H

#include "logic/include/file_manager/baseobj3dfilemanager.h"
#include "logic/include/file_manager/surfacefilemanager.h"
#include "logic/include/file_manager/figurefilemanager.h"
#include "logic/include/scene/scene.h"

class Obj3DFileManager : public BaseObj3DFileManager {
public:
    Scene read(const std::string &path) override;

    void saveFigure(std::shared_ptr<obj3d::Figure> figure) override;

    bool isFigureInside();

    bool isSurfaceInside();

private:
    bool isFigurePath(const std::string &path);

    bool isSurfacePath(const std::string &path);

    FigureFileManager figure_manager_;

    SurfaceFileManager surface_manager_;

};

#endif // OBJ3DFILEMANAGER_H
