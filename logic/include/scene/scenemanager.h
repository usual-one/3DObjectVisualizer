#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>

#include "logic/include/scene/scene.h"
#include "logic/include/scene/drawer/basescenedrawer.h"
#include "logic/include/scene/constructor/sceneconstructor.h"

class SceneManager {
public:
    SceneManager();

    SceneManager(std::unique_ptr<BaseSceneDrawer> drawer);

    void drawScene();

    std::shared_ptr<Scene> getScene();

    bool hasDrawer();

    void redrawScene();

    void setDrawer(std::unique_ptr<BaseSceneDrawer> drawer);

    void updateScene(const Scene &other);

private:
    std::vector<std::shared_ptr<CanvasFigure>> createCanvasFigures();

    std::unique_ptr<SceneConstructor> constructor_;

    std::unique_ptr<BaseSceneDrawer> drawer_;

    std::shared_ptr<Scene> scene_;

};

#endif // SCENEMANAGER_H
