#ifndef MENU_H
#define MENU_H

#include "game.h"
#include <QWidget>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();
    void setBg_gif(QMovie *newBg_gif);
    QMovie *getBg_gif() const;


private slots:
    void on_btn_play_clicked();

    void on_btn_controls_clicked();

    void on_btn_quit_clicked();

private:
    Ui::Menu *ui;
    QMovie *bg_gif;
    Game *game;
};
#endif // MENU_H
