#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QtGui>
#include <cmath>

struct panzer{
    QPoint position;
    int angle;
    int planeAngle;
    int force;
    int health;
};

class field : public QWidget
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = 0);

    static const double pi = 3.14159265358979;

    panzer tank;
    panzer enemy;

    bool Over;
    bool isWin;
    bool bulletLeaves;

    bool isBusy();
    void startPosition();

    void enemyMove(int count);
    void lose();
    void win();

private:
    void randomPlane();
    int  enemyMoveSteps;

protected:
    void paintEvent(QPaintEvent *);    

    void paintPanzer(QPainter &painter);
    void paintEnemyPanzer(QPainter &painter);

    void paintShot(QPainter &painter, QRect rect);

    void find_new_angle_and_force_for_enemy();

    QRect shotRect();
    QRect shotRect_Enemy();

    QRegion tankRegion();
    QRegion enemyRegion();

    bool isPanzerWounded(int x, int y);
    int isPlaneWounded(int x, int y);
    bool isEnemyWounded(int x, int y);

    int findCurrentPlane(int x);

    void updatePanzerPlane();
    void updateEnemyPanzerPlane();

signals:
    void tankWounded();
    void enemyWounded();
    void Window_Restart();
    void nextTurn();

public slots:
    void shoot();
    void shoot_Enemy();
    void enemyMove_SLOT();
    void startMovingLeft();
    void stopMovingLeft();
    void startMovingRight();
    void stopMovingRight();
    void restart();

private slots:
    void moveShot();
    void moveShot_Enemy();
    void moveLeft();
    void moveRight();

private:
    int timerCount;
    QTimer *autoShootTimer;
    QTimer *autoShootTimer_Enemy;
    QTimer *panzerMoveTimerRight;
    QTimer *panzerMoveTimerLeft;
    QTimer *enemyMoveTimer;
};

#endif // FIELD_H
