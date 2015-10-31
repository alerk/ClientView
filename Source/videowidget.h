#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);
    void setImage(QImage img);
    void changeScale(double factor);
    ~VideoWidget();
signals:

public slots:
    void animate();

protected:    
    void paintEvent(QPaintEvent *);

private:
    //Helper* helper;
    int elapsed;
    QImage mImage;
    double mImageScaleFactor = 1;
};

#endif // VIDEOWIDGET_H
