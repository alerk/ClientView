#include "videowidget.h"
#include <QTimer>
#include <QPainter>



VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent)
{
    elapsed = 0;
    setFixedSize(1920,1080);
    setAutoFillBackground(false);
    setStyleSheet("background:transparent");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    mImage = QImage(320,240,QImage::Format_RGBA8888);
    mImage.fill(Qt::black);
}

VideoWidget::~VideoWidget()
{

}

void VideoWidget::setImage(QImage img)
{
//    if(mImage.width()==0)
//    {
//        mImage = new QImage(*img);
//    }
//    else
    if(mImage.width()!=img.width() || mImage.height()!= img.height())
    {
        QPainter painter(&mImage);
        painter.drawImage(0,0,(img.scaled(mImage.width(), mImage.height())));
        painter.end();
    }
//    else
//    {
//        QPainter painter(mImage);
//        painter.drawImage(0,0,*img);
//        painter.end();
//    }
    this->update();
}

void VideoWidget::changeScale(double factor)
{
    mImageScaleFactor *= factor;
//    qDebug() << "--------------------factor: " << factor;
//    qDebug() << "--------------------image factor: " << mImageScaleFactor;
}

void VideoWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    //if (!mImage)
    //    return;
    QPainter painter;
    painter.begin(this);

//    double x = MapSetting::STATION_LONGITUDE, y = MapSetting::STATION_LATITUDE;
//    mMapCanvas->getCoordinateTransform()->transformInPlace(x,y);
    //QPointF stationLocation(x,y);
    //painter->translate(stationLocation);

    int width = mImage.width();
    int height = mImage.height();

    QImage scaledImg = mImage.scaled((double)width / mImageScaleFactor, (double)height / mImageScaleFactor,
                                     Qt::KeepAspectRatio, Qt::FastTransformation);

//    painter.drawImage(x - scaledImg.width() / 2, y - scaledImg.height() / 2, scaledImg );
    painter.drawImage(0, 0, scaledImg );

    //painter.drawImage(x - mImage->width() / 2, y - mImage->height() / 2, *mImage );


    painter.end();
}
