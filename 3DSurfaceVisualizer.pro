QT += core \
      gui \
      xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    logic/src/dto/figuremetadto.cpp \
    logic/src/dto/figuresessionstatedto.cpp \
    logic/src/dto/figurestatedto.cpp \
    logic/src/dto/figureverticesdto.cpp \
    logic/src/dto/surfaceparametersdto.cpp \
    logic/src/facade.cpp \
    logic/src/file_manager/csvfilemanager.cpp \
    logic/src/file_manager/exception/fileexception.cpp \
    logic/src/file_manager/figurefilemanager.cpp \
    logic/src/file_manager/filemanager.cpp \
    logic/src/file_manager/obj3dfilemanager.cpp \
    logic/src/file_manager/surfacefilemanager.cpp \
    logic/src/obj3d/figure/components/figuresessionstate.cpp \
    logic/src/obj3d/figure/components/state.cpp \
    logic/src/obj3d/figure/components/vertex.cpp \
    logic/src/obj3d/figure/components/edge.cpp \
    logic/src/obj3d/figure/components/figuremeta.cpp \
    logic/src/obj3d/figure/figure.cpp \
    logic/src/obj3d/math/basis3d.cpp \
    logic/src/obj3d/math/exception/mathexception.cpp \
    logic/src/obj3d/math/matrix.cpp \
    logic/src/obj3d/math/plane.cpp \
    logic/src/obj3d/math/rectangle2d.cpp \
    logic/src/obj3d/math/transformmatrixbuilder.cpp \
    logic/src/obj3d/math/vector2d.cpp \
    logic/src/obj3d/math/vector3d.cpp \
    logic/src/obj3d/math/point.cpp \
    logic/src/obj3d/math/point2d.cpp \
    logic/src/obj3d/math/point3d.cpp \
    logic/src/obj3d/object3d.cpp \
    logic/src/obj3d/surface/surface.cpp \
    logic/src/obj3d/surface/surfaceparameters.cpp \
    logic/src/scene/scene.cpp \
    logic/src/scene/constructor/camera.cpp \
    logic/src/scene/constructor/figure/canvasedge.cpp \
    logic/src/scene/constructor/figure/canvasfigure.cpp \
    logic/src/scene/constructor/figure/canvasvertex.cpp \
    logic/src/scene/constructor/sceneconstructor.cpp \
    logic/src/scene/drawer/canvas.cpp \
    logic/src/scene/drawer/scenedrawer.cpp \
    logic/src/scene/exception/sceneexception.cpp \
    logic/src/scene/scenemanager.cpp \
    logic/src/utils/exception/matrixcalculatorexception.cpp \
    logic/src/utils/exception/stringsplitterexception.cpp \
    logic/src/utils/mathcalculator.cpp \
    logic/src/utils/matrixcalculator.cpp \
    logic/src/utils/stringseparator.cpp \
    logic/src/utils/qtdtconverter.cpp \
    logic/src/utils/xml/qtxmlmanager.cpp \
    main.cpp \
    ui/src/utils/dialmanager.cpp \
    ui/src/utils/exception/vertexlistexception.cpp \
    ui/src/utils/slidermanager.cpp \
    ui/src/utils/tagsmanager.cpp \
    ui/src/utils/vertexlistmanager.cpp \
    ui/src/utils/qcomboboxcontroller.cpp \
    ui/src/windows/basetagselectingdialog.cpp \
    ui/src/windows/connectionadditiondialog.cpp \
    ui/src/windows/controlsdialog.cpp \
    ui/src/windows/exitdialog.cpp \
    ui/src/windows/exportdialog.cpp \
    ui/src/windows/figureconfigurationdialog.cpp \
    ui/src/windows/mainwindow.cpp \
    ui/src/windows/surfaceconfigurationdialog.cpp \
    ui/src/windows/surfaceviewdialog.cpp

HEADERS += \
    config.h \
    logic/include/dto/figuremetadto.h \
    logic/include/dto/figurestatedto.h \
    logic/include/dto/figureverticesdto.h \
    logic/include/dto/sessionstatedto.h \
    logic/include/dto/surfaceparametersdto.h \
    logic/include/dto/surfacevaluesdto.h \
    logic/include/facade.h \
    logic/include/file_manager/baseobj3dfilemanager.h \
    logic/include/file_manager/csvfilemanager.h \
    logic/include/file_manager/exception/fileexception.h \
    logic/include/file_manager/exception/fileopeningexception.h \
    logic/include/file_manager/exception/filewritingexception.h \
    logic/include/file_manager/figurefilemanager.h \
    logic/include/file_manager/filemanager.h \
    logic/include/file_manager/obj3dfilemanager.h \
    logic/include/file_manager/surfacefilemanager.h \
    logic/include/obj3d/figure/components/edge.h \
    logic/include/obj3d/figure/components/figuremeta.h \
    logic/include/obj3d/figure/components/figuresessionstate.h \
    logic/include/obj3d/figure/components/state.h \
    logic/include/obj3d/figure/components/vertex.h \
    logic/include/obj3d/figure/figure.h \
    logic/include/obj3d/math/basis3d.h \
    logic/include/obj3d/math/exception/basisexception.h \
    logic/include/obj3d/math/exception/mathexception.h \
    logic/include/obj3d/math/exception/matrixexception.h \
    logic/include/obj3d/math/exception/pointexception.h \
    logic/include/obj3d/math/matrix.h \
    logic/include/obj3d/math/plane.h \
    logic/include/obj3d/math/point.h \
    logic/include/obj3d/math/point2d.h \
    logic/include/obj3d/math/point3d.h \
    logic/include/obj3d/math/rectangle2d.h \
    logic/include/obj3d/math/transformmatrixbuilder.h \
    logic/include/obj3d/math/vector2d.h \
    logic/include/obj3d/math/vector3d.h \
    logic/include/obj3d/object3d.h \
    logic/include/obj3d/surface/surface.h \
    logic/include/obj3d/surface/surfaceparameters.h \
    logic/include/scene/constructor/camera.h \
    logic/include/scene/constructor/figure/canvasedge.h \
    logic/include/scene/constructor/figure/canvasfigure.h \
    logic/include/scene/constructor/figure/canvasvertex.h \
    logic/include/scene/constructor/sceneconstructor.h \
    logic/include/scene/drawer/basescenedrawer.h \
    logic/include/scene/drawer/canvas.h \
    logic/include/scene/drawer/scenedrawer.h \
    logic/include/scene/exception/sceneexception.h \
    logic/include/scene/exception/unknowntagexception.h \
    logic/include/scene/scene.h \
    logic/include/scene/scenemanager.h \
    logic/include/utils/exception/matrixcalculatorexception.h \
    logic/include/utils/exception/stringsplitterexception.h \
    logic/include/utils/mathcalculator.h \
    logic/include/utils/matrixcalculator.h \
    logic/include/utils/stringsplitter.h \
    logic/include/utils/qtdtconverter.h \
    logic/include/utils/xml/qtxmlmanager.h \
    logic/include/utils/xml/xmlmanager.h \
    ui/include/utils/dialmanager.h \
    ui/include/utils/exceptions/vertexlistexception.h \
    ui/include/utils/slidermanager.h \
    ui/include/utils/tagsmanager.h \
    ui/include/utils/vertexlistmanager.h \
    ui/include/utils/qcomboboxcontroller.h \
    ui/include/windows/basetagselectingdialog.h \
    ui/include/windows/connectionadditiondialog.h \
    ui/include/windows/controlsdialog.h \
    ui/include/windows/exitdialog.h \
    ui/include/windows/exportdialog.h \
    ui/include/windows/figureconfigurationdialog.h \
    ui/include/windows/mainwindow.h \
    ui/include/windows/surfaceconfigurationdialog.h \
    ui/include/windows/surfaceviewdialog.h


FORMS += \
    forms/connectionadditiondialog.ui \
    forms/controlsdialog.ui \
    forms/exitdialog.ui \
    forms/exportdialog.ui \
    forms/figureconfigurationdialog.ui \
    forms/mainwindow.ui \
    forms/surfaceconfigurationdialog.ui \
    forms/surfaceviewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
