#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QtDeclarative>
#include <QObject>

#include "show.h"
#include "videoviewer.h"
#include "videoreader.h"
#include "videoreceiver.h"

#define RECEIVE_SOCKET 1


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtQuick1ApplicationViewer viewer;
#if RECEIVE_SOCKET
    VideoReceiver *receiver = new VideoReceiver();
    receiver->start();
    receiver->join();
#endif
    qmlRegisterType<VideoViewer>("videoViewer", 1, 0, "VideoViewer");//to register a type VideoView to qml


    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:/main.qml"));
    viewer.showExpanded();

    VideoViewer* video_viewer0 = viewer.rootObject()->findChild<VideoViewer*>("mainView");//to match video_viewer to obj mainView in qml file

#if RECEIVE_SOCKET
    receiver->addVideoViewer(video_viewer0);// receive from socket
    QObject::connect(receiver,SIGNAL(finishedDraw(QImage)), video_viewer0, SLOT(onFinishedDraw(QImage)));
#else
        VideoReader* video_reader0 = new VideoReader("../Resource/outdoor_daytime_10m_heptane_CCD_001.avi");
        QObject::connect(video_reader0,SIGNAL(finishDraw(QImage)), video_viewer0, SLOT(onFinishedDraw(QImage)));


    VideoViewer* video_viewer1 = viewer.rootObject()->findChild<VideoViewer*>("mainView1");//to match video_viewer to obj mainView in qml file
        VideoReader* video_reader1 = new VideoReader("../Resource/OP_8mkM3L34.mp4");
        QObject::connect(video_reader1,SIGNAL(finishDraw(QImage)), video_viewer1, SLOT(onFinishedDraw(QImage)));
//    receiver.addVideoViewer(video_viewer1);// receive from socket
//    QObject::connect(&receiver,SIGNAL(finishedDraw_1(QImage)), video_viewer0, SLOT(onFinsihedDraw(QImage)));

    VideoViewer* video_viewer2 = viewer.rootObject()->findChild<VideoViewer*>("mainView2");//to match video_viewer to obj mainView in qml file
        VideoReader* video_reader2 = new VideoReader("../Resource/usnMR6I_EAQ.mp4");
        QObject::connect(video_reader2,SIGNAL(finishDraw(QImage)), video_viewer2, SLOT(onFinishedDraw(QImage)));
//    receiver.addVideoViewer(video_viewer2);// receive from socket
//    QObject::connect(&receiver,SIGNAL(finishedDraw_2(QImage)), video_viewer2, SLOT(onFinsihedDraw(QImage)));


    VideoViewer* video_viewer3 = viewer.rootObject()->findChild<VideoViewer*>("mainView3");//to match video_viewer to obj mainView in qml file
        VideoReader* video_reader3 = new VideoReader("../Resource/qIkbBLz8QCQ.mp4");
        QObject::connect(video_reader3,SIGNAL(finishDraw(QImage)), video_viewer3, SLOT(onFinishedDraw(QImage)));
//    receiver.addVideoViewer(video_viewer3);// receive from socket
//    QObject::connect(&receiver,SIGNAL(finishedDraw_3(QImage)), video_viewer3, SLOT(onFinsihedDraw(QImage)));
#endif
    return app.exec();
}
