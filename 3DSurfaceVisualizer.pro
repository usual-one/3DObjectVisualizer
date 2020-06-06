QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    logic/src/obj3d/figure/components/edge.cpp \
    logic/src/obj3d/figure/components/meta/figuremeta.cpp \
    logic/src/obj3d/figure/components/vertex3d.cpp \
    logic/src/obj3d/math/basis3d.cpp \
    logic/src/obj3d/math/exception/mathexception.cpp \
    logic/src/obj3d/math/matrix.cpp \
    logic/src/obj3d/math/plane.cpp \
    logic/src/obj3d/math/rectangle2d.cpp \
    logic/src/obj3d/math/transformmatrixbuilder.cpp \
    logic/src/obj3d/math/vector2d.cpp \
    logic/src/obj3d/math/vector3d.cpp \
    logic/src/scene/scene.cpp \
    logic/src/scene/scenemanager.cpp \
    logic/src/scene/searchparameters.cpp \
    logic/src/scene/constructor/camera.cpp \
    logic/src/scene/constructor/figure/canvasedge.cpp \
    logic/src/scene/constructor/figure/canvasfigure.cpp \
    logic/src/scene/constructor/figure/canvasvertex.cpp \
    logic/src/scene/constructor/sceneconstructor.cpp \
    logic/src/scene/drawer/canvas.cpp \
    logic/src/scene/drawer/scenedrawer.cpp \
    logic/src/scene/exception/sceneexception.cpp \
    logic/src/facade.cpp \
    logic/src/file_manager/figurefilemanager.cpp \
    logic/src/obj3d/figure/figure.cpp \
    logic/src/obj3d/figure/components/meta/location.cpp \
    logic/src/file_manager/csvfilemanager.cpp \
    logic/src/file_manager/fileexception.cpp \
    logic/src/file_manager/filemanager.cpp \
    logic/src/file_manager/obj3dfilemanager.cpp \
    logic/src/file_manager/surfacefilemanager.cpp \
    logic/src/obj3d/math/point.cpp \
    logic/src/obj3d/math/point2d.cpp \
    logic/src/obj3d/math/point3d.cpp \
    logic/src/obj3d/object3d.cpp \
    logic/src/obj3d/surface/surface.cpp \
    logic/src/obj3d/surface/surfaceparameters.cpp \
    logic/src/utils/exception/matrixcalculatorexception.cpp \
    logic/src/utils/exception/stringsplitterexception.cpp \
    logic/src/utils/mathcalculator.cpp \
    logic/src/utils/matrixcalculator.cpp \
    logic/src/utils/qtdtconverter.cpp \
    logic/src/utils/stringseparator.cpp \
    main.cpp \
    ui/src/utils/tagsmanager.cpp \
    ui/src/windows/connectionadditiondialog.cpp \
    ui/src/windows/figureconfigurationdialog.cpp \
    ui/src/windows/exitdialog.cpp \
    ui/src/windows/controlsdialog.cpp \
    ui/src/windows/mainwindow.cpp \
    ui/src/windows/surfaceconfigurationdialog.cpp \
    ui/src/windows/surfaceviewdialog.cpp \
    ui/src/utils/qcomboboxcontroller.cpp

HEADERS += \
    logic/include/obj3d/figure/figure3d.h \
    logic/include/obj3d/figure/components/vertex3d.h \
    logic/include/obj3d/math/basis3d.h \
    logic/include/obj3d/math/exception/basisexception.h \
    logic/include/obj3d/math/exception/mathexception.h \
    logic/include/obj3d/math/exception/matrixexception.h \
    logic/include/obj3d/math/exception/pointexception.h \
    logic/include/obj3d/math/matrix.h \
    logic/include/obj3d/math/plane.h \
    logic/include/obj3d/math/rectangle2d.h \
    logic/include/obj3d/math/transformmatrixbuilder.h \
    logic/include/obj3d/math/vector2d.h \
    logic/include/obj3d/math/vector3d.h \
    logic/include/scene/scene.h \
    logic/include/scene/scenemanager.h \
    logic/include/scene/drawer/basescenedrawer.h \
    logic/include/scene/drawer/canvas.h \
    logic/include/scene/drawer/scenedrawer.h \
    logic/include/scene/constructor/camera.h \
    logic/include/scene/constructor/figure/canvasedge.h \
    logic/include/scene/constructor/figure/canvasfigure.h \
    logic/include/scene/constructor/figure/canvasvertex.h \
    logic/include/scene/constructor/sceneconstructor.h \
    logic/include/scene/exception/sceneexception.h \
    logic/include/scene/exception/unknowntagexception.h \
    logic/include/scene/searchparameters.h \
    config.h \
    logic/include/obj3d/figure/components/meta/location.h \
    logic/include/obj3d/figure/components/meta/figuremeta.h \
    logic/include/utils/mathcalculator.h \
    logic/include/utils/qtdtconverter.h \
    ui/include/utils/qcomboboxcontroller.h \
    ui/include/windows/mainwindow.h \
    ui/include/windows/connectionadditiondialog.h \
    ui/include/windows/figureconfigurationdialog.h \
    ui/include/windows/surfaceconfigurationdialog.h \
    ui/include/windows/surfaceviewdialog.h \
    ui/include/windows/exitdialog.h \
    ui/include/windows/controlsdialog.h \
    logic/include/facade.h \
    logic/include/obj3d/figure/components/edge.h \
    logic/include/file_manager/baseobj3dfilemanager.h \
    logic/include/file_manager/csvfilemanager.h \
    logic/include/file_manager/exception/fileexception.h \
    logic/include/file_manager/exception/fileopeningexception.h \
    logic/include/file_manager/exception/filewritingexception.h \
    logic/include/file_manager/figurefilemanager.h \
    logic/include/file_manager/filemanager.h \
    logic/include/file_manager/obj3dfilemanager.h \
    logic/include/file_manager/surfacefilemanager.h \
    logic/include/obj3d/math/point.h \
    logic/include/obj3d/math/point2d.h \
    logic/include/obj3d/math/point3d.h \
    logic/include/obj3d/object3d.h \
    logic/include/obj3d/surface/surface.h \
    logic/include/obj3d/surface/surfaceparameters.h \
    logic/include/utils/exception/matrixcalculatorexception.h \
    logic/include/utils/exception/stringsplitterexception.h \
    logic/include/utils/matrixcalculator.h \
    logic/include/utils/stringsplitter.h \
    ui/include/utils/tagsmanager.h

FORMS += \
    forms/controlsdialog.ui \
    forms/exitdialog.ui \
    forms/connectionadditiondialog.ui \
    forms/figureconfigurationdialog.ui \
    forms/mainwindow.ui \
    forms/surfaceconfigurationdialog.ui \
    forms/surfaceviewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
