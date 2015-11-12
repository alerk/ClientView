#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QPainter>

#include "videoreceiver.h"
#include "common.h"

#define IMG_BUFFER_SIZE 928332

typedef enum parsing_state_t
{
    FLAG_F1= 0,
    FLAG_F2,
    FLAG_AA,
    FLAG_55,
    MSG_TYPE,//00: FireAlarm; 01: IntruderAlarm; 02: FireVideo
    MSG_VALUE,
    SOURCE_ID,
    COLS_1,
    COLS_2,
    ROWS_1,
    ROWS_2,
    DEPTH,
    IDX,
    TOTAL,
    SIZE,
    DATA
}parsing_state;

static parsing_state next_state = FLAG_F1;
static unsigned char img_buffer[IMG_BUFFER_SIZE];
static unsigned long img_idx=0;

VideoReceiver::VideoReceiver(QObject *parent) : QObject(parent)
{

}

VideoReceiver::~VideoReceiver()
{

}

void VideoReceiver::start()
{
    if( pthread_create(&receiverThread,NULL,VideoReceiver::run,(void*)this)!=0)
    {
        std::cout << "Fail to create receiverThread" << std::endl;
    }
    std::cout << "[VideoReceiver]Start" << std::endl;
}

void VideoReceiver::join()
{
//    pthread_join(receiverThread, NULL);
}

void VideoReceiver::addVideoViewer(VideoViewer *obj)
{
    videoViewer = obj;
}

void* VideoReceiver::run(void *arg)
{
    VideoReceiver* obj = (VideoReceiver*)arg;
    int counter = 0;
    char* recv_buf;
        recv_buf = (char*)malloc(SOCKET_BUFFER_SIZE);
    while(true)
    {
        try
        {
            std::cout << "\r" << std::flush;
            std::cout << "Trying to connect " << counter++ << std::endl;
            counter %= 10;
            ClientSocket clientSock("localhost",13579);
            std::cout << "Open connection" << std::endl;
            while(true)
            {
                int recv_size = clientSock.recv(recv_buf, SOCKET_BUFFER_SIZE);
                if(recv_size<=0)
                {
                    throw SocketException ( "Could not read from socket." );
                }
                else
                {
//                    std::cout << "Received " << recv_size << " bytes" << std::endl;
                }
                //decode recv_buf
                unsigned char output_type, output_value;
                QImage send(640,480,QImage::Format_RGB888);

                obj->decodeMessage(recv_size, (unsigned char*)recv_buf, output_type, output_value, send);
//                if(output_type == 2 && output_value == 6)
//                {
////                    emit obj->finishedDraw(send);
//                    obj->videoViewer->onFinishedDraw(send);
//                    std::cout << "Send image" << std::endl;
//                }
//                if(output_type == 0x02)
//                {
//                    if(output_value==5)
//                    {
//                        //emit obj->finishedDraw_0(send);
//                    }
//                    else
//                    {
//                        std::cout << "Error while receiving src_id" << std::endl;
//                    }
//                    switch(output_value)
//                    {
//                        case 0:
//                            emit obj->finishedDraw_0(send);
//                            break;
//                        case 1:
//                            emit obj->finishedDraw_1(send);
//                            break;
//                        case 2:
//                            emit obj->finishedDraw_2(send);
//                            break;
//                        case 3:
//                            emit obj->finishedDraw_3(send);
//                            break;
//                        default:
//                            std::cout << "Error while receiving src_id" << std::endl;
//                            break;
//                    }
//                }

                //obj->getVideoViewer(output_value).doFinishedDraw(send);
            }
        }
        catch(SocketException &e)
        {
            sleep(1);
            //cout << "Error " << e.description() << endl;
            //break;
        }

    }
}

void VideoReceiver::decodeMessage(unsigned int size, unsigned char *buffer, unsigned char &output_type, unsigned char &output_value, QImage &output)
{
    int i=0;
    unsigned char src_id;
    unsigned char col_1, col_2, row_1, row_2;
    unsigned int cols;
    unsigned int rows;
    unsigned char depth;
    unsigned char idx;
    unsigned char total;
    unsigned int img_size;

    unsigned char data;

    for (i=0;i<size;i++)
    {
        data = (unsigned char)buffer[i];
        switch (next_state)
        {
        case FLAG_F1:
            if(data==0xFF)
            {
                next_state = FLAG_F2;
            }
            else
            {
                next_state = FLAG_F1;
            }
            break;
        case FLAG_F2:
            if(data==0xFF)
            {
                next_state = FLAG_AA;
            }
            else
            {
                next_state = FLAG_F1;
            }
            break;
        case FLAG_AA:
            if(data==0xAA)
            {
                next_state = FLAG_55;
            }
            else
            {
                next_state = FLAG_F1;
            }
            break;
        case FLAG_55:
            if(data==0x55)
            {
                next_state = DATA;
            }
            else
            {
                next_state = FLAG_F1;
            }
            break;
        case DATA:
        {
            img_buffer[img_idx++] = data;
            if(img_idx == IMG_BUFFER_SIZE)
            {
                cv::Mat opencv_img(cv::Size(640,480),CV_8UC3,img_buffer);
                cv::Mat temp; // make the same cv::Mat
                cv::cvtColor(opencv_img, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
                QImage temp_output((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                temp_output.bits();
                QPainter pt(&output);
                pt.drawImage(0,0,temp_output);
                pt.end();
                output_type = 2;
                output_value = 6;
                next_state = FLAG_F1;
                img_idx = 0;
//                cv::imshow("Recv", temp);
//                cv::waitKey();
                emit finishedDraw(temp_output);
            }
        }
            break;
        default:
            break;
        }
    }
}

