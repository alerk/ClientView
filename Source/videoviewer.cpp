#include "videoviewer.h"
#include <iostream>
#include <QPainter>


VideoViewer::VideoViewer(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    mProxyWidget = new QGraphicsProxyWidget(this);

    //    GLWidget* openGL = new GLWidget(&helper);
    //    mProxyWidget->setWidget(openGL);
    //    QTimer* timer = new QTimer(this);
    //    connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));

    mWidget = new VideoWidget();
    mProxyWidget->setWidget(mWidget);

    l_img = QImage(640, 480, QImage::Format_RGB888);

//    connect(ImageProcessor::instance(), SIGNAL(finishDraw(QImage*)), this, SLOT(onFinsihedDraw(QImage*)));

//    VideoImage::getInstance()->start();
//    PlotImage::getInstance()->start();
//    PlotVideoImage::getInstance()->start();
//    ImageProcessor::instance()->start();
}

VideoViewer::~VideoViewer()
{

}

void VideoViewer::setSize(int w, int h)
{
    if (mProxyWidget)
        mProxyWidget->resize(w,h);
}

void VideoViewer::onFinishedDraw(QImage img)
{
//    doFinishedDraw(img);
    //mImage = img;
//    std::cout<< "Receive signal" << std::endl;
    l_img = img.copy(0,0,640,480);
//    QPainter painter(&l_img);
//    painter.drawImage(0, 0, img);
//    painter.end();
    mWidget->setImage(img);
}

