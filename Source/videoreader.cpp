#include "videoreader.h"

#include <unistd.h>
#include <QImage>
#include <QThread>
#include <QPainter>
#include <iostream>

using namespace cv;



#define FPS 30

static int delay_uSecond;
void Mat2QImage(cv::Mat const& src, QImage& dest);
QImage* Mat2QImage(cv::Mat const& src);
QImage send;


VideoReader::VideoReader()
{
    capture = VideoCapture("../Resource/outdoor_daytime_10m_heptane_CCD_001.avi");
    delay_uSecond = 1000000/FPS;
    start();
}

VideoReader::VideoReader(std::string src)
{
    videoSrc = src;
    capture = VideoCapture(src);
    std::cout << "Open: " << src << std::endl;
    delay_uSecond = 1000000/FPS;
    window_name = "Window ";window_name.append(src);
    cv::namedWindow(window_name);
    start();
}

VideoReader::~VideoReader()
{

}

void VideoReader::setViewer(VideoViewer *viewer)
{
//    connect(this,SIGNAL(finishDraw(QImage*)),viewer, SLOT(onFinsihedDraw(QImage*)));
}

void VideoReader::start()
{
    pthread_create(&videoThread,NULL,VideoReader::run,this);
}

void* VideoReader::run(void *args)
{
    Mat img;

    VideoReader* reader = (VideoReader*)args;
    while(true)
    {
        //        if(reader->capture!=0)

        //(reader->capture) >> img;
        if(!(reader->capture).read(img))
        {
            std::cout << "Cannot read frame" << std::endl;
            reader->capture.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
        }
        else
        {
            //cv::resize(img, img, cv::Size(320,240));
            //std::cout << "Read frame from " << reader->videoSrc << std::endl;
            cv::imshow(reader->window_name, img);
            QImage temp;
            Mat2QImage(img, temp);
//            if(send.width()!=temp.width() || send.height()!= temp.height());
//            {
//                send = QImage(temp.width(), temp.height(), QImage::Format_RGBA8888);
//            }
//            QPainter painter(&send);
//            painter.drawImage(0,0,temp);
//            painter.end();
//            emit reader->finishDraw(send);
            emit reader->finishDraw(temp);
            //delete temp;
        }
//        char c = waitKey(30);
//        if(c=='q')
//        {
//            std::cout << "User quit!" << std::endl;
//        }
        usleep(delay_uSecond);
    }
}

void Mat2QImage(cv::Mat const& src, QImage& dest)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need     
//     memcpy(dest->bits(), (const uchar *) temp.data, temp.cols*temp.rows*temp.step*8);
     dest=QImage((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
//     return dest;
}

QImage* Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage* dest = new QImage((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest->bits(); // enforce deep copy, see documentation
     return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

