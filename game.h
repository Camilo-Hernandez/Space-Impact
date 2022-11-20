#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "qgraphicsscene.h"
#include "qlabel.h"
#include <QMovie>
#include <QGraphicsView>

#define WIDTH 1100
#define HEIGHT 700

namespace Ui {
class Game;
}

class Game : public QGraphicsView
    // Clase que controla aspectos globales del juego
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    QMovie *getBg_gif() const;
    void setBg_gif(QMovie *newBg_gif);
    QGraphicsScene *scene;
    Player *player;
    QTimer *enemies_timer;

public slots:
    void spawnEnemies();
    void changeHealth(int newHealth);

private:
    Ui::Game *ui;
    QMovie *bg_gif;
    QLabel *lbl_bg;
};

#endif // GAME_H
