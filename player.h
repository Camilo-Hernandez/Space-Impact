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
    int getHealth() const;
    void setHealth(int newHealth);
    QTimer *collision_timer;
private:
    int health=3;

private slots:
    void collidesWithEnemies();

signals:
    void healthChanged(int newHealth);
};

#endif // PLAYER_H
