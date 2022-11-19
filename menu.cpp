#include "menu.h"
#include "ui_menu.h"
#include <QFont>
#include <QFontDatabase>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    // poner gif de fondo de pantalla
    setBg_gif(new QMovie(":/images/images/bg_menu.gif"));
    ui->lbl_bg->setMovie(getBg_gif());
    getBg_gif()->start();

}

Menu::~Menu()
{
    delete ui;
}

void Menu::setBg_gif(QMovie *_bg_gif)
{
    bg_gif = _bg_gif;
}

QMovie *Menu::getBg_gif() const
{
    return bg_gif;
}


void Menu::on_btn_play_clicked()
{
    game = new Game;
    game->show();
}


void Menu::on_btn_controls_clicked()
{

}


void Menu::on_btn_quit_clicked()
{
    close();
}

