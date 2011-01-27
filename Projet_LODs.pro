TEMPLATE = app

QT += opengl

INCLUDEPATH += .
win32:LIBS += -L. -lglut32

HEADERS += \
    Mesh.h \
    Vec3.h

SOURCES += \
    main.cpp \
    Mesh.cpp
