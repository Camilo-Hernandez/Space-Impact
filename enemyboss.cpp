#include "enemyboss.h"
#include "menu.h"

extern Menu *menu;

EnemyBoss::EnemyBoss(QObject *parent)
    : Enemy{parent}
{
    // Crear el enemigo en una posición aleatoria en y() y 1100 en x()
    setPos(1100, 80);
    setImage(2);
    setScale(0.6);
    setHealth(7);
}

EnemyBoss::~EnemyBoss(){
    menu->showEndingMessage();
}
