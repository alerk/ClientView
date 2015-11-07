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

#include "videoviewer.h"
#include "Socket/ClientSocket.h"
#include "Socket/SocketException.h"

class VideoReceiver : public QObject
{
    Q_OBJECT

    std::vector<VideoViewer*> videoViewerTrunk;
    pthread_t receiverThread;

public:
    explicit VideoReceiver(QObject *parent = 0);
    ~VideoReceiver();

    void start();
    void join();
    void addVideoViewer(VideoViewer* obj);
    VideoViewer* getVideoViewer(int index);


    static void* run(void* arg);


signals:
    void finishedDraw_0(QImage img);
    void finishedDraw_1(QImage img);
    void finishedDraw_2(QImage img);
    void finishedDraw_3(QImage img);


public slots:
};

#endif // VIDEORECEIVER_H
