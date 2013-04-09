#include "field.h"

QPoint mas[20];
int numPlane;

//---------------------------------------------------------------------------------------------------
field::field(QWidget *parent) :
    QWidget(parent)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    panzerMoveTimerRight = new QTimer(this);
    panzerMoveTimerLeft = new QTimer(this);

    autoShootTimer = new QTimer(this);
    autoShootTimer_Enemy = new QTimer(this);

    enemyMoveTimer = new QTimer(this);

    connect(enemyMoveTimer, SIGNAL(timeout()), this, SLOT(enemyMove_SLOT()));

    connect(autoShootTimer, SIGNAL(timeout()), this, SLOT(moveShot()));
    connect(autoShootTimer_Enemy, SIGNAL(timeout()), this, SLOT(moveShot_Enemy()));

    connect(panzerMoveTimerRight, SIGNAL(timeout()), this, SLOT(moveRight()));
    connect(panzerMoveTimerLeft, SIGNAL(timeout()), this, SLOT(moveLeft()));
    startPosition();
}
//---------------------------------------------------------------------------------------------------
void field::randomPlane()
{
    const int Number_Planes_In_File=5;
    QFile file(":plane");
    file.open(QIODevice::ReadOnly);
    if (!file.exists()){
        QMessageBox::critical(0,"Plane is everywhere", "File plane not found ERROR!");
        exit(0);
    }
    else
    {
        QTextStream in(&file);
        int t =qrand()%Number_Planes_In_File;      
        QString st;

        for (int j=0; j<t; j++)
            st=file.readLine();

        in>>numPlane;
        int p1, p2;
        in>>p1>>p2;
        mas[0]=QPoint(p1, p2);
        in>>p1>>p2;
        mas[1]=QPoint(p1, p2);
        for (int i=0; i<numPlane; i++)
        {
            in>>p1>>p2;
            mas[i+2]=QPoint(p1, p2);
        }
    }
    file.close();
}
//---------------------------------------------------------------------------------------------------
void field::startPosition()
{

    randomPlane();

    setPalette(QPalette(QColor(127, 129, 255)));
    setAutoFillBackground(true);

    autoShootTimer->stop();
    autoShootTimer_Enemy->stop();

    panzerMoveTimerLeft->stop();
    panzerMoveTimerRight->stop();

    tank.position = mas[0];
    enemy.position = mas[1];

    tank.angle=45;
    enemy.angle=45;

    tank.force=50;
    enemy.force=50;

    tank.health=4;
    enemy.health=4;

    timerCount = 0;
    Over = false;

    emit(Window_Restart());
    updatePanzerPlane();
    updateEnemyPanzerPlane();
    update();
}
//---------------------------------------------------------------------------------------------------
void field::paintEvent(QPaintEvent * /* event */)
{
    if (Over)
        return;
    QPainter painter(this);

    painter.setPen( QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(0,0, 850, 400);

    painter.setPen( QPen(Qt::black, 4, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i=1; i<numPlane; ++i)
        painter.drawLine(mas[i+1], mas[i+2]);

    paintPanzer(painter);
    paintEnemyPanzer(painter);

    if (autoShootTimer->isActive())
        paintShot(painter, shotRect());
    if (autoShootTimer_Enemy->isActive())
        paintShot(painter, shotRect_Enemy());
}
//---------------------------------------------------------------------------------------------------
void field::startMovingLeft()
{
    if (!isBusy() || Over)
      return;    
    panzerMoveTimerLeft->start(15);
    update(tankRegion());
}
//---------------------------------------------------------------------------------------------------
void field::stopMovingLeft()
{
    panzerMoveTimerLeft->stop();
    update(tankRegion());
}
//---------------------------------------------------------------------------------------------------
void field::moveLeft()
{
    if (tank.position.x()<30)
        return;

    int currentPlane = findCurrentPlane(tank.position.x()-10);

    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();

    tank.planeAngle = -atan(deltaY/deltaX)*180/pi;
    tank.position.setX(tank.position.x() - 1);
    tank.position.setY(tank.position.x()*K + B - 9);
    update(tankRegion());
}
//---------------------------------------------------------------------------------------------------
void field::startMovingRight()
{   
    if (!isBusy() || Over)
      return;
    panzerMoveTimerRight->start(15);
    update();
}
//---------------------------------------------------------------------------------------------------
void field::stopMovingRight()
{
    panzerMoveTimerRight->stop();
    update();
}
//---------------------------------------------------------------------------------------------------
void field::moveRight()
{    
    if (tank.position.x()>=820 || tank.position.x()+20>=enemy.position.x())
        return;
    int currentPlane = findCurrentPlane(tank.position.x()+10);

    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();

    tank.planeAngle = -atan(deltaY/deltaX)*180/pi;
    tank.position.setX(tank.position.x() + 1);
    tank.position.setY(tank.position.x()*K + B - 9);
    update(tankRegion());
}
//---------------------------------------------------------------------------------------------------
void field::paintPanzer(QPainter &painter)
{    
    painter.save();
    int x=tank.position.x(), y=tank.position.y();
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::red);
    painter.translate(x, y);
    painter.rotate(-tank.planeAngle);

    painter.drawEllipse(QPoint(0, 0), 20, 6);
    painter.drawLine(-20, -8, +20, -8);
    painter.drawLine(-20, -8, -25, -4);
    painter.drawLine(+20, -8, +25, -4);

    painter.drawPie(QRect(-22, -22, 28, 28), 0, 90*16);
    painter.translate(-10, -10);
    painter.rotate(-tank.angle);
    painter.drawRect(QRect(2, 2, 28, 2));
    painter.restore();
}
//---------------------------------------------------------------------------------------------------
void field::paintEnemyPanzer(QPainter &painter)
{
    painter.save();
    int x=enemy.position.x(), y=enemy.position.y();
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::blue);

    painter.translate(x, y);
    painter.rotate(-enemy.planeAngle);

    painter.drawEllipse(QPoint(0, 0), 20, 6);
    painter.drawLine(-20, -8, +20, -8);
    painter.drawLine(-20, -8, -25, -4);
    painter.drawLine(+20, -8, +25, -4);

    painter.drawPie(QRect(-2, -22, 28, 28), 90*16, 90*16);
    painter.translate(10, -10);
    painter.rotate(-180+enemy.angle);
    painter.drawRect(QRect(2, 2, 28, 2));
    painter.restore();
}
//---------------------------------------------------------------------------------------------------
void field::shoot()
{
    if (!isBusy() || Over)
        return;
    timerCount = 0;
    bulletLeaves = false;
    autoShootTimer->start(17);
}
//---------------------------------------------------------------------------------------------------
void field::paintShot(QPainter &painter, QRect rect)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(rect);
}
//---------------------------------------------------------------------------------------------------
QRect field::shotRect()
 {
     const double gravity = 4;

     double time = timerCount / 20.0;
     double velocity = tank.force;
     double radians = (tank.angle+tank.planeAngle) * 3.14159265 / 180;
     double rad = tank.planeAngle * 3.14159265 / 180;

     double velx = velocity * cos(radians);
     double vely = velocity * sin(radians);
     double x0 = (tank.position.x() - 14*sin(rad));// * cos(radians);
     double y0 = (tank.position.y() - 14*cos(rad));// * sin(radians);

     double x = x0 + velx * time;
     double y = y0 - vely * time + 0.5 * gravity * time * time;

     QRect result(0, 0, 6, 6);
     result.moveCenter(QPoint(qRound(x), qRound(y)));
     return result;
 }
//---------------------------------------------------------------------------------------------------
void field::moveShot()
 {
     QRegion region = shotRect();
     ++timerCount;

     QRect shotR = shotRect();
     int tmp =abs(isPlaneWounded(shotR.x(), shotR.y()));
     if (shotR.x()>width() || shotR.x()<0 || shotR.y()>height() || tmp<=3)
     {
         autoShootTimer->stop();
         emit(nextTurn());
     } else {
         region = region.unite(shotR);
     }
     if (isEnemyWounded(shotR.x(), shotR.y()))
     {
         emit(enemyWounded());
         autoShootTimer->stop();
         emit(nextTurn());
     }
     if (bulletLeaves && isPanzerWounded(shotR.x(), shotR.y()))
     {
         emit(tankWounded());
         autoShootTimer->stop();
         emit(nextTurn());
     }

     if (!isPanzerWounded(shotR.x(), shotR.y()))
         bulletLeaves = true;

     update(region);
 }
//--------------------------------------------------------------------------------------------------
QRegion field::tankRegion()
{
    return QRegion(tank.position.x()-100, tank.position.y()-100,
                   tank.position.x()+100, tank.position.y()+100);
}
//--------------------------------------------------------------------------------------------------
QRegion field::enemyRegion()
{
    return QRegion(enemy.position.x()-100, enemy.position.y()-100,
                   enemy.position.x()+100, enemy.position.y()+100);
}
//---------------------------------------------------------------------------------------------------
bool field::isBusy()
{
    return !(autoShootTimer->isActive() ||
             autoShootTimer_Enemy->isActive() ||
             panzerMoveTimerRight->isActive() ||
             panzerMoveTimerLeft->isActive() ||
             enemyMoveTimer->isActive());
}
//---------------------------------------------------------------------------------------------------
int field::findCurrentPlane(int x)
{
    int currentPlane = 1;
    for (int i=0; i<numPlane; ++i)
       if (mas[i+2].x()<=x && x<=mas[i+3].x())
       {
            currentPlane=i+2;
            break;
        }
    return currentPlane;
}
//---------------------------------------------------------------------------------------------------
bool field::isPanzerWounded(int x, int y)
{
    if (abs(tank.position.x()-x)<=23 && abs(tank.position.y()-y)<= 23)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------------------------------
bool field::isEnemyWounded(int x, int y)
{
    if (abs(enemy.position.x()-x)<=23 && abs(enemy.position.y()-y)<= 23     )
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------------------------------
void field::lose()
{
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
                     QBrush(QPixmap(":/images/lose.jpg").scaled(850, 400, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
    setPalette(palette);    
    QMessageBox::information(0,"Unfortunately", "You were killed. Try once more");
}
//---------------------------------------------------------------------------------------------------
void field::win()
{
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
                     QBrush(QPixmap(":/images/win.jpg").scaled(850, 400, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
    setPalette(palette);    
    QMessageBox::information(0,"Surprise", "Congratulations. The war is over");
}
//---------------------------------------------------------------------------------------------------
int field::isPlaneWounded(int x, int y)
{
    int currentPlane = findCurrentPlane(x);
    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();
    return y-K*x-B;
}
//---------------------------------------------------------------------------------------------------
void field::restart()
{
    if (!isBusy())
        return;
    int ret = QMessageBox::question(this, tr("Restart?"),
                                    tr("Do you want to restart this game?"),
                                     QMessageBox::Cancel | QMessageBox::Ok );
    switch (ret){
        case QMessageBox::Ok:
            startPosition();            
            break;
    case QMessageBox::Cancel:

            break;
    }
}
//---------------------------------------------------------------------------------------------------
void field::updatePanzerPlane()
{
    int currentPlane = findCurrentPlane(tank.position.x());

    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();

    tank.planeAngle = -atan(deltaY/deltaX)*180/pi;
    tank.position.setY(tank.position.x()*K + B - 9);
}
//---------------------------------------------------------------------------------------------------
void field::updateEnemyPanzerPlane()
{
    int currentPlane = findCurrentPlane(enemy.position.x());

    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();

    enemy.planeAngle = -atan(deltaY/deltaX)*180/pi;
    enemy.position.setY(enemy.position.x()*K + B - 9);
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
void field::shoot_Enemy()
{
    if (!isBusy() || Over)
        return;
    find_new_angle_and_force_for_enemy();
    timerCount = 0;
    bulletLeaves = false;
    autoShootTimer_Enemy->start(17);
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
QRect field::shotRect_Enemy()
 {
     const double gravity = 4;

     double time = timerCount / 20.0;
     double velocity = enemy.force;
     double radians = (enemy.angle-enemy.planeAngle) * 3.14159265 / 180;
     double rad = enemy.planeAngle * 3.14159265 / 180;

     double velx = velocity * cos(radians);
     double vely = velocity * sin(radians);
     double x0 = (enemy.position.x() - 14*sin(rad));// * cos(radians);
     double y0 = (enemy.position.y() - 14*cos(rad));// * sin(radians);

     double x = x0 - velx * time;
     double y = y0 - vely * time + 0.5 * gravity * time * time;

     QRect result(0, 0, 6, 6);
     result.moveCenter(QPoint(qRound(x), qRound(y)));
     return result;
 }
//---------------------------------------------------------------------------------------------------
void field::moveShot_Enemy()
 {
     QRegion region = shotRect_Enemy();
     ++timerCount;

     QRect shotR = shotRect_Enemy();
     int tmp =abs(isPlaneWounded(shotR.x(), shotR.y()));
     if (shotR.x()>width() || shotR.x()<0 || shotR.y()>height() || tmp<=3)
     {
         autoShootTimer_Enemy->stop();
         emit(nextTurn());
     } else {
         region = region.unite(shotR);
     }
     if (isPanzerWounded(shotR.x(), shotR.y()))
     {
         emit(tankWounded());
         autoShootTimer_Enemy->stop();
         emit(nextTurn());
     }
     update(region);
 }
//---------------------------------------------------------------------------------------------------
void field::find_new_angle_and_force_for_enemy()
{
    update();
    QPoint tmp=mas[2];
    bool wasPlane = false;
    for (int i=3; i<7; ++i)
        if (mas[i].x()>=tank.position.x() && mas[i].x()<=enemy.position.x() && mas[i].y()<tmp.y()){
            tmp=mas[i];
            wasPlane = true;
        }

    int x0=tank.position.x(), y0=tank.position.y();
    int x1=tmp.x(), y1=tmp.y();
    int x2=enemy.position.x(), y2=enemy.position.y();

    double minDistance=x2-x0;
    int ang_to_rem=45;
    int for_to_rem=50;
    for (int a = 10; a<=90; a+=15)
        for (int f =20; f<=90; f+=15)
        {
            int ang=a-enemy.planeAngle;
            if (int(f*cos(ang * 3.14159265 / 180))==0) continue;
            int time = (x2-x0)/(f*cos(ang * 3.14159265 / 180));
            int new_y = y2 - f*sin(ang * 3.14159265 / 180)*time + 0.5*4*time*time;


            if (int(f*cos(ang * 3.14159265 / 180))==0) continue;
            int time2 = (x2-x1)/(f*cos(ang * 3.14159265 / 180));
            int new_y2 = y2 - f*sin(ang * 3.14159265 / 180)*time2 + 0.5*4*time2*time2;

            if (abs(new_y-y0)<minDistance)
                if (!wasPlane || (wasPlane && new_y2<y1))
                {
                    ang_to_rem =a;
                    for_to_rem =f;
                    minDistance = abs(new_y-y0);
                }
        }
    enemy.force=for_to_rem;
    enemy.angle=ang_to_rem;
    update();
}
//---------------------------------------------------------------------------------------------------
void field::enemyMove(int count)
{
    enemyMoveSteps = count;
    if (!isBusy() || Over)
      return;
    timerCount=0;
    enemyMoveTimer->start(15);
}
//---------------------------------------------------------------------------------------------------
void field::enemyMove_SLOT()
{
    if (abs(enemy.position.x()-tank.position.x())<30){
        enemyMoveTimer->stop();
        shoot_Enemy();
        return;
    }
    if (enemyMoveSteps<0 && enemy.position.x()>=820){
        enemyMoveTimer->stop();
        shoot_Enemy();
        return;
    }

    ++timerCount;
    if (timerCount>abs(enemyMoveSteps)){
        enemyMoveTimer->stop();
        shoot_Enemy();
        return;
    }
    int currentPlane;
    if (enemyMoveSteps>=0)
        currentPlane = findCurrentPlane(enemy.position.x()-15);
    else
        currentPlane = findCurrentPlane(enemy.position.x()+15);

    double deltaY = (mas[currentPlane+1].y()-mas[currentPlane].y())*1.0;
    double deltaX = (mas[currentPlane+1].x()-mas[currentPlane].x())*1.0;
    double K = deltaY / deltaX;
    double B = mas[currentPlane].y() - K * mas[currentPlane].x();

    enemy.planeAngle = -atan(deltaY/deltaX)*180/pi;
    if (enemyMoveSteps>0)
        enemy.position.setX(enemy.position.x() - 1);
    else
        enemy.position.setX(enemy.position.x() + 1);
    enemy.position.setY(enemy.position.x()*K + B - 9);
    update(enemyRegion());
}
