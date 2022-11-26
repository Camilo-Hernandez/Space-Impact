#include "heart.h"
#include "player.h"
#include "qtimer.h"

Heart::Heart(QObject *parent)
    : QObject{parent}
{
    // Crear el corazón en una posición aleatoria en y() y 1100 en x()
    int posy = rand() % 500;
    setPos(1100, posy);
    setPixmap(QPixmap(":/images/images/playerHealth.png"));

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    QTimer *heartTimer = new QTimer();
    connect(heartTimer, SIGNAL(timeout()), this, SLOT(move()));
    heartTimer->start(40); // milisegundos que tarda en efectuar la función move()

    QTimer *heartTimer2 = new QTimer();
    connect(heartTimer2, SIGNAL(timeout()), this, SLOT(moveYSin()));
    heartTimer2->start(10); // milisegundos que tarda en efectuar la función move()

    // Timer para detectar colisiones con los enemigos
    collision_timer = new QTimer();
    connect(collision_timer, SIGNAL(timeout()), this, SLOT(collidesWithPlayer()));
    collision_timer->start(20);
}

Heart::~Heart(){}

void Heart::move(int velocity)
{
    setPos(x()-velocity, y());
    // eliminar el corazón cuando desaparece de la escena
    if (pos().x() < 0){
        // remover el corazón de la memoria
        this->~Heart();
    }
}

void Heart::collidesWithPlayer()
{
    // Si Heart colisiona con el jugador, desaparece
    foreach(QGraphicsItem *item, collidingItems()){
        if(dynamic_cast<Player*>(item)){ // hacer una transformación del item a tipo Heart
            // Enviar señal de aumentar la salud
            emit increaseHealth();
            this->~Heart();
        }
    }
}

void Heart::moveYSin()
{
    setPos(x(), y()+10*qSin(x()));
}
