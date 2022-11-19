#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();
    void keyPressEvent(QKeyEvent *event);

private:

signals:

};

#endif // PLAYER_H
