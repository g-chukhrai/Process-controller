# -------------------------------------------------
# Project created by QtCreator 2010-04-17T18:21:19
# -------------------------------------------------
TARGET = Controller
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    vertex.cpp \
    graphscene.cpp \
    graph.cpp \
    edge.cpp \
    matrixwindow.cpp \
    resultwindow.cpp \
    infowindow.cpp
HEADERS += mainwindow.h \
    vertex.h \
    graphscene.h \
    graph.h \
    edge.h \
    matrixwindow.h \
    resultwindow.h \
    infowindow.h
FORMS += mainwindow.ui \
    matrixwindow.ui \
    resultwindow.ui \
    infowindow.ui
RESOURCES += resource.qrc
RC_FILE = icon.rc
QMAKE_CFLAGS_RELEASE += -O0
QMAKE_CXXFLAGS_RELEASE += -O0
QMAKE_OBJECTIVE_CFLAGS_RELEASE += -O0\
