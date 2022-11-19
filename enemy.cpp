#include "enemy.h"
#include "enemybullet.h"
#include "qgraphicsscene.h"
#include "qtimer.h"

Enemy::Enemy(QObject *parent, int posy, QTimer *enemyTimer, QTimer *shootingTimer)
    : QObject{parent}
{
    // Crear el enemigo en una posición aleatoria en y() y 1100 en x()
    setPos(1100, posy);
    setPixmap(QPixmap(":/images/images/basicEnemy.png"));
    setScale(0.35);

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));
    enemyTimer->start(40); // milisegundos que tarda en efectuar la función move()
    connect(shootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    shootingTimer->start(1500);
}

Enemy::~Enemy(){
    //qDebug() << "Enemigo eliminado de memoria";
}

void Enemy::move(int velocity)
    // mover el enemigo a la izquierda
{
    setPos(x()-velocity, y());
    // eliminar el enemigo cuando desaparece de la escena
    if (pos().x() < 0){
        // decrementar el puntaje cuando el enemigo detecta colisión con el jugador
        //game -> health -> decreaseHealth();

        // remover el enemigo de memoria
        this->~Enemy();
    }
}

void Enemy::shoot()
{
    // Crear una bala enemiga
    EnemyBullet *enemyBullet = new EnemyBullet();
    enemyBullet ->setPos(x()-50,y()+48); // posición de la bala respecto de la esquina superior izquierda del Enemy
    scene()->addItem(enemyBullet); // cada item tiene un puntero a la escena a la que será añadido
}
