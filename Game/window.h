
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include "field.h"

#include <phonon/AudioOutput>
#include <phonon/MediaObject>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

    QTextEdit *infoLabel;
    QPushButton* button0;
    QGroupBox *group1;
    QGroupBox *group2;
    QSpinBox *angleSpin;
    QSpinBox *forceSpin;

    QLabel *condition;

    QProgressBar *yourHealth;
    QProgressBar *enemyHealth;

    void startWindow();
    void battleWindow();

    void playMusic();

protected:
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
    Phonon::MediaObject *mediaObject;    
    field *mainField;

    int numSong;

signals:
    
public slots:
    void infoDialog();
    void backToHell();
    void newGame();
    void mainMenu();
    void nextSong();
    void prevSong();
    void tankWounded();
    void enemyWounded();
    void angleChanged(int value);
    void forceChanged(int value);

    void Window_Restart();
    void nextTurn();

};

#endif // WINDOW_H
