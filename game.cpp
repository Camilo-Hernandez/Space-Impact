#include "game.h"
#include "enemy.h"
#include "qgraphicsscene.h"
#include "qtimer.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::Game)
{
    // --- configurar la ventana --- //
    ui->setupUi(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH, HEIGHT);

    // --- poner gif de fondo en el QLabel de la ui --- //
    /* para poner un gif como fondo de pantalla
     * es necesario poner un graphicsView en la ui transparente
     * encima del QLabel donde se pone el gif
     */
    setBg_gif(new QMovie(":/images/images/bg_game.gif"));
    ui->lbl_bg->setMovie(getBg_gif());
    getBg_gif()->start();

    // --- crear la escena donde añadir el jugador y los enemigos sobre el graphicsView de la ui --- //
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, WIDTH, HEIGHT);
    ui->graphicsView->setMaximumSize(WIDTH, HEIGHT);
    ui->graphicsView->setScene(scene);

    // --- crear el jugador --- //
    player = new Player();
    //move the player to the bottom center of the view
    player->setPos(100, 150);
    // make the item focusable to be able to respond to events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the item to the scene
    scene->addItem(player);

    // --- crear los enemigos periódicamente --- //
    enemies_timer = new QTimer();
    QObject::connect(enemies_timer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));
    enemies_timer->start(1500);
}

void Game::spawnEnemies(){
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
}

Game::~Game()
{
    delete ui;
}

QMovie *Game::getBg_gif() const
{
    return bg_gif;
}

void Game::setBg_gif(QMovie *newBg_gif)
{
    bg_gif = newBg_gif;
}
