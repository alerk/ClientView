#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QtDeclarative>
#include <QObject>

#include "show.h"
#include "videoviewer.h"
#include "videoreader.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtQuick1ApplicationViewer viewer;

    qmlRegisterType<VideoViewer>("videoViewer", 1, 0, "VideoViewer");//to register a type VideoView to qml


    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:/main.qml"));
    viewer.showExpanded();

    VideoViewer* video_viewer = viewer.rootObject()->findChild<VideoViewer*>("mainView");//to match video_viewer to obj mainView in qml file
//    mQmlViewer.rootObject()->findChild<QObject*>("mapviewer");
    VideoReader* video_reader = new VideoReader("../Resource/outdoor_daytime_10m_heptane_CCD_001.avi");
    QObject::connect(video_reader,SIGNAL(finishDraw(QImage)), video_viewer, SLOT(onFinsihedDraw(QImage)));


    VideoViewer* video_viewer1 = viewer.rootObject()->findChild<VideoViewer*>("mainView1");//to match video_viewer to obj mainView in qml file
//    mQmlViewer.rootObject()->findChild<QObject*>("mapviewer");
    VideoReader* video_reader1 = new VideoReader("../Resource/OP_8mkM3L34.mp4");
    QObject::connect(video_reader1,SIGNAL(finishDraw(QImage)), video_viewer1, SLOT(onFinsihedDraw(QImage)));

    VideoViewer* video_viewer2 = viewer.rootObject()->findChild<VideoViewer*>("mainView2");//to match video_viewer to obj mainView in qml file
//    mQmlViewer.rootObject()->findChild<QObject*>("mapviewer");
    VideoReader* video_reader2 = new VideoReader("../Resource/usnMR6I_EAQ.mp4");
    QObject::connect(video_reader2,SIGNAL(finishDraw(QImage)), video_viewer2, SLOT(onFinsihedDraw(QImage)));

    VideoViewer* video_viewer3 = viewer.rootObject()->findChild<VideoViewer*>("mainView3");//to match video_viewer to obj mainView in qml file
//    mQmlViewer.rootObject()->findChild<QObject*>("mapviewer");
    VideoReader* video_reader3 = new VideoReader("../Resource/qIkbBLz8QCQ.mp4");
    QObject::connect(video_reader3,SIGNAL(finishDraw(QImage)), video_viewer3, SLOT(onFinsihedDraw(QImage)));

    return app.exec();
}
