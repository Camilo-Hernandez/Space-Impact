#ifndef HEART_H
#define HEART_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Heart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Heart(QObject *parent = nullptr);
    ~Heart();
    QTimer *collision_timer;
    int angle;

signals:
    void increaseHealth();

public slots:
    void move(int velocity=12);
    void collidesWithPlayer();
    void moveYSin();
};

#endif // HEART_H
