TEMPLATE=app
TARGET=declarative-camera

QT += quick qml multimedia

SOURCES += qmlcamera.cpp \
    photorecognize.cpp
RESOURCES += declarative-camera.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/declarative-camera
INSTALLS += target

HEADERS += \
    photorecognize.h


INCLUDEPATH += G:/workspace/rabbit/include/
LIBS += -LG:/workspace/rabbit/libs/ -lPocoFoundationd
#LIBS += -lPocoFoundation
