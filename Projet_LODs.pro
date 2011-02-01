TEMPLATE = app

QT += opengl

INCLUDEPATH += .
win32:LIBS += -L. -L"GL/" -lglut32

HEADERS += \
    Mesh.h \
    Vec3.h \
    Vert.h \
    Edge.h \
    Face.h \
    Vec2.h

SOURCES += \
    main.cpp \
    Mesh.cpp \
    Vert.cpp \
    Edge.cpp \
    Face.cpp
