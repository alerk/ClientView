#ifndef SHOW_H
#define SHOW_H

#include <QObject>

class QtQuick1ApplicationViewer;

class Show : public QObject
{
    Q_OBJECT
public:
    explicit Show(QObject *parent = 0);
    ~Show();

    void start(QtQuick1ApplicationViewer viewer);

signals:

public slots:
};

#endif // SHOW_H
