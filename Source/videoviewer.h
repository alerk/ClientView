#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QDeclarativeItem>
#include <QGraphicsProxyWidget>
#include "videowidget.h"

class VideoViewer : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit VideoViewer(QDeclarativeItem *parent = 0);
    void setSize(int w, int h);
    ~VideoViewer();

signals:

public slots:
    void onFinsihedDraw(QImage img);

private:
    QGraphicsProxyWidget* mProxyWidget;
    QImage mImage;
    VideoWidget* mWidget;
};

#endif // VIDEOVIEWER_H
