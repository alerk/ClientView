# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    videoviewer.cpp \
    videowidget.cpp \
    videoreader.cpp \
    show.cpp \
    Socket/ClientSocket.cpp \
    Socket/ServerSocket.cpp \
    Socket/Socket.cpp \
    videoreceiver.cpp

RESOURCES += qml.qrc

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick1applicationviewer/qtquick1applicationviewer.pri)

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    videoviewer.h \
    videowidget.h \
    videoreader.h \
    show.h \
    Socket/ClientSocket.h \
    Socket/ServerSocket.h \
    Socket/Socket.h \
    Socket/SocketException.h \
    videoreceiver.h \
    common.h

#unix:!macx: LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui

unix:!macx: LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
