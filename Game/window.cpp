#include "window.h"
#include <iostream>


Window::Window(QWidget *parent) :
    QWidget(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int screenX=QApplication::desktop()->screenGeometry().width();
    int screenY=QApplication::desktop()->screenGeometry().height();

    if (screenX<1000 || screenY<550)
    {
        QMessageBox::critical(0,"Critical", "Screen Resolution is too small");
        exit(0);
    }

    numSong = 0;
    playMusic();

 //   setWindowFlags(Qt::FramelessWindowHint);
 //   setWindowFlags( Qt::WindowStaysOnTopHint);

   QPalette palette;
    palette.setBrush(this->backgroundRole(),
                     QBrush(QPixmap(":/images/background.jpg").scaled(1000, 600,Qt::IgnoreAspectRatio, Qt::FastTransformation)));
    setPalette(palette);

    setCursor(QCursor(QPixmap(":/images/cursor3.png")));
    setStyleSheet("QPushButton { background-color: rgba(120, 120, 200, 50); border: 2px solid #8f8f91;  border-radius: 6px; color:white; font: bold 12px;}"                  
                  "QLabel      { padding: 2px; color:white; border-radius: 6px; font: bold 12px;}"
                  "QTextEdit   { background-color:rgba(120, 120, 200, 150); border: 2px solid #8f8f91; border-radius: 6px; color: white;}"
                  "QProgressBar{ border: 2px solid grey;    border-radius: 5px; text-align: center;}"
                  "QProgressBar::chunk { background-color: #05B8CC; width: 20px; }"
                  "QMessageBox {color: red; background-color: black;}");
    startWindow();
    battleWindow();

    setFixedSize(1000, 550);
}
//---------------------------------------------------------------------------------------------------
void Window::startWindow()
{
    group1 = new QGroupBox(this);
    group1->setGeometry(0,0, 1000, 550);
    group1->setVisible(true);

    button0 = new QPushButton("Continue", group1);
    QPushButton* button1 = new QPushButton("New Game", group1);
    QPushButton* button2 = new QPushButton("Settings", group1);
    QPushButton* button3 = new QPushButton("Info", group1);
    QPushButton* button4 = new QPushButton("Exit", group1);

    infoLabel = new QTextEdit(group1);
    infoLabel->setVisible(false);
    infoLabel->setGeometry(400, 50, 500, 450);
    infoLabel->setReadOnly(true);

    QFile file("./Readme.txt");
    file.open(QIODevice::ReadOnly);
    if (!file.exists())
        infoLabel->setText("File Readme.txt not Found.");
    else
    {
        QTextStream in(&file);
        QString tmp;
        char t;
        while (!in.atEnd()){
            in>>t;
            tmp+=t;
        }
        infoLabel->setText(tmp);
    }
    file.close();

    button0->setVisible(false);
    button2->setVisible(false);

    button0->setGeometry(100, 300, 200, 40);
    button1->setGeometry(100, 350, 200, 40);
    button2->setGeometry(100, 350, 200, 40);
    button3->setGeometry(100, 400, 200, 40);
    button4->setGeometry(100, 450, 200, 40);

    connect(button0, SIGNAL(clicked()), this, SLOT(backToHell()));
    connect(button1, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(button2, SIGNAL(clicked()), this, SLOT(infoDialog()));
    connect(button3, SIGNAL(clicked()), this, SLOT(infoDialog()));
    connect(button4, SIGNAL(clicked()), this, SLOT(close()));
}
//---------------------------------------------------------------------------------------------------
void Window::battleWindow()
{
    group2=new QGroupBox(this);
    group2->setGeometry(0,0, 1000, 550);
    group2->setVisible(false);
    group2->setFocusPolicy(Qt::NoFocus);

    mainField = new field(group2);
    mainField->setGeometry(100, 100, 850, 400 );
    mainField->setFocus();
    mainField->grabKeyboard();

    QPushButton *retn = new QPushButton("Return to Main Menu", group2);
    retn->setGeometry(20, 30, 150, 40);
    connect(retn, SIGNAL(clicked()), this, SLOT(mainMenu()));

    QPushButton *restart = new QPushButton("Restart", group2);
    restart->setGeometry(200, 30, 100, 40);
    connect(restart, SIGNAL(clicked()), mainField, SLOT(restart()));

    QLabel *label1 = new QLabel("You HP", group2);
    label1->setGeometry(350, 30, 100, 20);
    QLabel *label2 = new QLabel("Enemy HP",group2);
    label2->setGeometry(350, 60, 100, 20);

    yourHealth = new QProgressBar(group2);
    yourHealth->setGeometry(450, 30, 150, 20);
    yourHealth->setValue(100);

    enemyHealth = new QProgressBar(group2);
    enemyHealth->setGeometry(450, 60, 150, 20);
    enemyHealth->setValue(100);

    connect(mainField, SIGNAL(tankWounded()), this, SLOT(tankWounded()));
    connect(mainField, SIGNAL(enemyWounded()), this, SLOT(enemyWounded()));
    connect(mainField, SIGNAL(Window_Restart()), this, SLOT(Window_Restart()));
    connect(mainField, SIGNAL(nextTurn()), this, SLOT(nextTurn()));

    condition = new QLabel("Your Turn", group2);
    condition->setGeometry(650, 30, 250, 40);
    condition->setStyleSheet("font: bold 12px; color:red; text-align:center;");

    QPushButton *left = new QPushButton("Left", group2);
    left->setGeometry(20, 100, 60, 40);
    connect(left, SIGNAL(pressed()), mainField, SLOT(startMovingLeft()));
    connect(left, SIGNAL(released()), mainField, SLOT(stopMovingLeft()));

    QPushButton *right = new QPushButton("Right", group2);
    right->setGeometry(20, 150, 60, 40);
    connect(right, SIGNAL(pressed()), mainField, SLOT(startMovingRight()));
    connect(right, SIGNAL(released()), mainField, SLOT(stopMovingRight()));

    QLabel *angleLabel = new QLabel("Angle", group2);
    angleLabel->setGeometry(20, 200, 60, 40);

    angleSpin = new QSpinBox(group2);
    angleSpin->setRange(10, 90);
    angleSpin->setSingleStep(1);
    angleSpin->setValue(45);
    angleSpin->setGeometry(20, 250, 50, 50);
    connect(angleSpin, SIGNAL(valueChanged(int)), this, SLOT(angleChanged(int)));

    QLabel *forceLabel = new QLabel("Power", group2);
    forceLabel->setGeometry(20, 300, 60, 40);

    forceSpin = new QSpinBox(group2);
    forceSpin->setRange(20, 90);
    forceSpin->setSingleStep(1);
    forceSpin->setValue(50);
    forceSpin->setGeometry(20, 350, 50, 50);
    connect(forceSpin, SIGNAL(valueChanged(int)), this, SLOT(forceChanged(int)));

    QPushButton *shoot = new QPushButton("Shoot", group2);
    connect(shoot, SIGNAL(clicked()), mainField, SLOT(shoot()));
    shoot->setGeometry(20, 450, 60, 40);

}
//---------------------------------------------------------------------------------------------------
void Window::mainMenu()
{
    if (!mainField->isBusy())
        return;
    Window::group1->setVisible(true);
    Window::group2->setVisible(false);
}
//---------------------------------------------------------------------------------------------------
void Window::infoDialog()
{
    //Window::settingBox->setVisible(false);
    Window::infoLabel->setVisible(!Window::infoLabel->isVisible());
}
//---------------------------------------------------------------------------------------------------
void Window::newGame()
{
    Window::button0->setVisible(true);
    mainField->startPosition();
    Window::group1->setVisible(false);
    Window::group2->setVisible(true);
}
//---------------------------------------------------------------------------------------------------
void Window::backToHell()
{
    Window::group1->setVisible(false);
    Window::group2->setVisible(true);
}
//---------------------------------------------------------------------------------------------------
void Window::tankWounded()
{
    mainField->tank.health--;
    yourHealth->setValue(mainField->tank.health*25);
    if (mainField->tank.health<=0)
    {
        mainField->Over=true;
        mainField->lose();
    }
}
//---------------------------------------------------------------------------------------------------
void Window::enemyWounded()
{
    mainField->enemy.health--;
    enemyHealth->setValue(mainField->enemy.health*25);
    if (mainField->enemy.health<=0)
    {
        mainField->Over=true;
        mainField->win();
    }
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
void Window::playMusic()
{
    if (!QDir(".//music").exists())
        return;
    QStringList files =  QDir(".//music//").entryList(QStringList("*.mp3"), QDir::Files);
    if (files.empty())
        return;

    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);

    mediaObject->setCurrentSource(Phonon::MediaSource(".//music//"+files.at(numSong%files.size())));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(nextSong()));

    mediaObject->play();
}
//---------------------------------------------------------------------------------------------------
void Window::nextSong()
{
    if (!QDir(".//music").exists())
        return;
    mediaObject->stop();
    numSong++;
    playMusic();
}
//---------------------------------------------------------------------------------------------------
void Window::prevSong()
{
    if (!QDir(".//music").exists())
        return;
    mediaObject->stop();
    numSong--;
    playMusic();
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
void Window::keyPressEvent(QKeyEvent *keyEvent)
{
    bool foo = group2->isVisible();
    switch (keyEvent->key())
    {
        case Qt::Key_7:
                QMessageBox::warning(0,"Warning", "Dont ever hit this button, bastard");
                break;                
        //-----------------------------------
        case Qt::Key_D:
              if (foo)  mainField->startMovingRight();
                break;
        case 1042:
          if (foo)  mainField->startMovingRight();
            break;
        case Qt::Key_Right:
              if (foo)  mainField->startMovingRight();
                break;
         //-----------------------------------
        case Qt::Key_A:
               if (foo) mainField->startMovingLeft();
                break;
        case 1060:
               if (foo) mainField->startMovingLeft();
                break;
        case Qt::Key_Left:
               if (foo) mainField->startMovingLeft();
                break;
        //-----------------------------------------------
        case Qt::Key_W:
               if (foo) angleSpin->setValue(angleSpin->value()+1);
                break;                
        case 1062:
               if (foo) angleSpin->setValue(angleSpin->value()+1);
                break;
        case Qt::Key_Up:
               if (foo) angleSpin->setValue(angleSpin->value()+1);
                break;
        //-----------------------------------------------
        case Qt::Key_E:
              if (foo)  forceSpin->setValue(forceSpin->value()+1);
                break;
        case 1059:
              if (foo)  forceSpin->setValue(forceSpin->value()+1);
                break;
        case Qt::Key_Plus:
             if (foo)   forceSpin->setValue(forceSpin->value()+1);
                break;

        //-----------------------------------------------
        case Qt::Key_Minus:
              if (foo)  forceSpin->setValue(forceSpin->value()-1);
                break;
        case Qt::Key_Q:
              if (foo)  forceSpin->setValue(forceSpin->value()-1);
                break;
        case 1049:
              if (foo)  forceSpin->setValue(forceSpin->value()-1);
                break;
        //------------------------------------------------
        case Qt::Key_S:
             if (foo)   angleSpin->setValue(angleSpin->value()-1);
                break;
        case 1067:
             if (foo)   angleSpin->setValue(angleSpin->value()-1);
                break;
        case Qt::Key_Down:
             if (foo)  angleSpin->setValue(angleSpin->value()-1);
                break;
        //-----------------------------------------------
        case Qt::Key_F:
             if (foo)   mainField->shoot();
                break;
        case 1040:
             if (foo)   mainField->shoot();
                break;
        case Qt::Key_Return:
           if (foo) mainField->shoot();
            break;
        //-----------------------------------------------
        case Qt::Key_N:
                nextSong();
                break;
        case 1048:
                nextSong();
                break;
        case 1058:
                prevSong();
                break;
        //-----------------------------------------------
        case Qt::Key_Escape:
                close();
                break;
        //-----------------------------------------------
    }
}
//---------------------------------------------------------------------------------------------------
void Window::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (!group2->isVisible())
        return ;
    switch (keyEvent->key())
    {
        case Qt::Key_D:
            mainField->stopMovingRight();
            break;
        case 1042:
            mainField->stopMovingRight();
            break;
        case Qt::Key_Right:
                mainField->stopMovingRight();
                break;
        //-----------------------------------
        case Qt::Key_A:
             mainField->stopMovingLeft();
             break;
        case 1060:
             mainField->stopMovingLeft();
             break;
        case Qt::Key_Left:
             mainField->stopMovingLeft();
             break;
    }
}
//---------------------------------------------------------------------------------------------------
void Window::angleChanged(int value)
{
    if (!mainField->isBusy() || mainField->Over)
    {
        angleSpin->setValue(mainField->tank.angle);
        return;
    }
    mainField->tank.angle=value;
    mainField->update();
}
//---------------------------------------------------------------------------------------------------
void Window::forceChanged(int value)
{
    if (!mainField->isBusy() || mainField->Over)
    {
        forceSpin->setValue(mainField->tank.force);
        return;
    }
    mainField->tank.force=value;
}
//---------------------------------------------------------------------------------------------------
void Window::Window_Restart()
{
   yourHealth->setValue(100);
   enemyHealth->setValue(100);

   condition->setText("Your Turn");

   angleSpin->setValue(45);
   forceSpin->setValue(50);
}
//---------------------------------------------------------------------------------------------------
void Window::nextTurn()
{
    if (mainField->Over){
        condition->setText("Cake is a lie.");
        return ;
    }
    if (condition->text()=="Your Turn")
    {
        condition->setText("Enemy Turn");   
        mainField->enemyMove(qrand()%200 - 100);
    }
    else
        condition->setText("Your Turn");
}
