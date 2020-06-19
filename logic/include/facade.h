#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include <string>

#include "logic/include/file_manager/baseobj3dfilemanager.h"
#include "logic/include/scene/scenemanager.h"
#include "logic/include/obj3d/surface/surfaceparameters.h"

class Facade {
public:
    Facade();

    Facade(std::unique_ptr<BaseObj3DFileManager> file_manager,
           std::unique_ptr<SceneManager> scene_manager);

    const std::string &addNewFigure();

    void deleteSurface(const std::string &tag);

    void deleteFigure(const std::string &tag);

    void drawScene();

    bool hasFigures();

    bool hasSurfaces();

    bool hasUnsaved();

    void hideFigure(const std::string &tag, bool hidden);

    void hideSurface(const std::string &tag, bool hidden);

    bool isValid();

    Scene loadScene(const std::string &path);

    std::vector<std::string> getSurfacesTags();

    std::shared_ptr<obj3d::Surface> getSurface(const std::string &tag);

    std::vector<std::string> getFiguresTags();

    std::shared_ptr<obj3d::Figure> getFigure(const std::string &tag);

    void recalculateSurface(const std::string &surface_tag);

    void redrawScene();

    void saveFigure(const std::string &tag, const std::string &path);

    void updateFigureVertices(const std::string &tag, std::shared_ptr<FigureVerticesDTO> vertices);

    void updateFigureSessionState(const std::string &tag, std::shared_ptr<SessionStateDTO> state);

    void updateFigureState(const std::string tag, std::shared_ptr<FigureStateDTO> state);

private:
    std::unique_ptr<BaseObj3DFileManager> file_manager_;

    std::unique_ptr<SceneManager> scene_manager_;

    bool has_changes_;

};

#endif // FACADE_H
