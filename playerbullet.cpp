#include "playerbullet.h"
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
