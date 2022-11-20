#include "playerbullet.h"
#include "enemy.h"
#include "enemybullet.h"
#include "player.h"
#include "qgraphicsscene.h"
#include <QTimer>

PlayerBullet::PlayerBullet(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/images/playerBullet.png"));
    setScale(0.35);
    //qDebug() << "Bala creada";

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    QTimer *bullet_timer = new QTimer();
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(collidesWithEnemies()));
    bullet_timer->start(20); // milisegundos que tarda en efectuar la función move()
}

PlayerBullet::~PlayerBullet(){
    qDebug() << "Bala eliminada de memoria";
}

void PlayerBullet::move()
{
    // mover la bala a la derecha
    setPos(x()+10, y());
    // eliminar la bala de la memoria si pasa la frontera derecha de la escena
    if (pos().x()>1100){
        this->~PlayerBullet();
    }
}

void PlayerBullet::collidesWithEnemies(){
    // if bullet collides with enemy, destroy both
    foreach(QGraphicsItem *item, collidingItems()){
        if(dynamic_cast<Enemy*>(item)){
            // si colisiona con tipo Enemy, baja una vida al enemigo TODO
            qDebug() << "Colisión con enemigo";
            // TODO
        }
        else if(dynamic_cast<EnemyBullet*>(item)){
            // si colisiona con tipo EnemyBullet, elimina los dos
            qDebug() << "Colisión con bala enemiga";
            this->~PlayerBullet();
            delete item;
        }
    };
}
