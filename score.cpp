#include "score.h"
#include "menu.h"
#include "qfont.h"

extern Menu *menu;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
/* QGraphicsTextItem recibe el padre de QGraphicsItem
 * en el constructor para asignarle el padre al nuestra clase personalizada
 */
{
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText("Score: " + QString::number(score)); // Score = 0
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Sansation", 27));
}

void Score::changeScore(int change)
{
    score+=change;
    setPlainText("Score: " + QString::number(score));
}

int Score::getScore()
{
    return score;
}

Score::~Score()
{
    qDebug() << "Score eliminado de memoria";
}
