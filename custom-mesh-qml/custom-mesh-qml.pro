QT += 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras
CONFIG += c++11

SOURCES += \
    main.cpp \
    CustomMesh.cpp

OTHER_FILES += \
    main.qml

RESOURCES += \
    qml.qrc

HEADERS += \
    CustomMesh.h
