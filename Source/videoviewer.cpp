#include "videoviewer.h"

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

void VideoViewer::onFinsihedDraw(QImage img)
{
//    doFinishedDraw(img);
    //mImage = img;
    mWidget->setImage(img);
}

