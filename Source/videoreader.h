#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <pthread.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



#include "videoviewer.h"

class VideoReader : public QObject
{
    Q_OBJECT
public:
    VideoReader();
    VideoReader(std::string src);
    ~VideoReader();

    cv::VideoCapture capture;
    pthread_t videoThread;

    void setViewer(VideoViewer* viewer);
    static void* run(void* args);

    std::string videoSrc;
    std::string window_name;
signals:
    void finishDraw(QImage img);
public slots:

private:

    void start();
    void join();
};

#endif // VIDEOREADER_H
