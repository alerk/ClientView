#include <iostream>

#include "videoreceiver.h"
#include "common.h"
#include "messageparser.h"


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
    pthread_join(receiverThread, NULL);
}

void VideoReceiver::addVideoViewer(VideoViewer* obj)
{
    //videoViewerTrunk.insert(obj.index, obj);
    videoViewerTrunk.push_back(obj);

}

VideoViewer* VideoReceiver::getVideoViewer(int index)
{
    return videoViewerTrunk.at(index);
}

void* VideoReceiver::run(void *arg)
{
    VideoReceiver* obj = (VideoReceiver*)arg;
    int counter = 0;
    unsigned char* recv_buf;
        recv_buf = (unsigned char*)malloc(SOCKET_BUFFER_SIZE+1);
    while(true)
    {
        try
        {
            std::cout << "\r" << std::flush;
            std::cout << "Trying to connect " << counter++ << std::endl;
            counter %= 10;
            ClientSocket clientSock("192.168.50.101",13579);
            std::cout << "Open connection" << std::endl;
            while(true)
            {
                int recv_size = clientSock.recv((char*)recv_buf, SOCKET_BUFFER_SIZE+1);
                if(recv_size<=0)
                {
                    throw SocketException ( "Could not read from socket." );
                }
                //decode recv_buf
                unsigned char output_type, output_value;
                QImage send;

                MessageParser::parseMessage(recv_size, recv_buf, output_type, output_value, send);
                if(output_type == 0x02)
                {
                    switch(output_value)
                    {
                        case 0:
                            emit obj->finishedDraw_0(send);
                            break;
                        case 1:
                            emit obj->finishedDraw_1(send);
                            break;
                        case 2:
                            emit obj->finishedDraw_2(send);
                            break;
                        case 3:
                            emit obj->finishedDraw_3(send);
                            break;
                        default:
                            std::cout << "Error while receiving src_id" << std::endl;
                            break;
                    }
                }

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

