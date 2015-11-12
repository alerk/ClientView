#ifndef VIDEORECEIVER_H
#define VIDEORECEIVER_H

/**
  * Class:      VideoReceiver
  * Function:   - Receive the data through Socket or sth
  *             - Navigate them to correct destination (VideoViewer)
  *             - Collect and control all VideoViewer.
  */


#include <QObject>
#include <vector>
#include <pthread.h>

#include "Socket/ClientSocket.h"
#include "Socket/SocketException.h"

#include "videoviewer.h"

class VideoReceiver : public QObject
{
    Q_OBJECT    
public:
    explicit VideoReceiver(QObject *parent = 0);
    ~VideoReceiver();

    void start();
    void join();

    VideoViewer* videoViewer;
    void addVideoViewer(VideoViewer* obj);
    pthread_t receiverThread;
    static void* run(void* arg);

    void decodeMessage(unsigned int size, unsigned char* buffer, unsigned char &output_type, unsigned char &output_value, QImage& output);
signals:
    void finishedDraw(QImage img);

public slots:


};

#endif // VIDEORECEIVER_H
