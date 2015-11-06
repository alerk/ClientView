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

void VideoReceiver::addVideoViewer(VideoViewer &obj)
{
    //videoViewerTrunk.insert(obj.index, obj);
    videoViewerTrunk.push_back(obj);
}

VideoViewer& VideoReceiver::getVideoViewer(int index)
{
    return videoViewerTrunk.at(index);
}

void* VideoReceiver::run(void *arg)
{
    VideoReceiver* obj = (VideoReceiver*)arg;
    int counter = 0;
    char* recv_buf;
        recv_buf = (char*)malloc(15);
    while(true)
    {
        try
        {
            std::cout << "\r" << std::flush;
            std::cout << "Trying to connect " << counter++ << std::endl;
            counter %= 10;
            ClientSocket clientSock("192.168.50.101",12345);
            std::cout << "Open connection" << std::endl;
            while(true)
            {
                int recv_size = clientSock.recv(recv_buf, SOCKET_BUFFER_SIZE+1);
                if(recv_size<=0)
                {
                    throw SocketException ( "Could not read from socket." );
                }
                //decode recv_buf
                unsigned char output_type, output_value;
                QImage send;
                MessageParser.parseMessage(recv_size, recv_buff, output_type, output_value, send);
                obj->getVideoViewer(output_value).onFinsihedDraw(send);
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

