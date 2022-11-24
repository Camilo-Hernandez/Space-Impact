#include "enemybullet.h"
#include "qtimer.h"

EnemyBullet::EnemyBullet(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/images/enemyBullet.png"));
    setScale(0.5);

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    bullet_timer = new QTimer();
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(move()));
    bullet_timer->start(20); // milisegundos que tarda en efectuar la función move()
}

EnemyBullet::~EnemyBullet(){
    qDebug() << "Bala enemiga eliminada de memoria";
}

void EnemyBullet::move()
{
    // mover la bala a la derecha
    setPos(x()-10, y());
    // eliminar la bala de la memoria si pasa la frontera derecha de la escena
    if (pos().x()<0){
        this->~EnemyBullet();
    }
}

