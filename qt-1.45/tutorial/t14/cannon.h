/****************************************************************
**
** Definition of CannonField class, Qt tutorial 14
**
****************************************************************/

#ifndef CANNON_H
#define CANNON_H

#include <qwidget.h>


class CannonField : public QWidget
{
    Q_OBJECT
public:
    CannonField( QWidget *parent=0, const char *name=0 );

    int   angle()      const { return ang; }
    int   force()      const { return f; }
    bool  gameOver()   const { return gameEnded; }
    bool  isShooting() const { return shooting; }
public slots:
    void  setAngle( int degrees );
    void  setForce( int newton );
    void  shoot();
    void  newTarget();
    void  setGameOver();
    void  restartGame();
signals:
    void  hit();
    void  missed();
    void  angleChanged( int );
    void  forceChanged( int );
protected:
    void  timerEvent( QTimerEvent * );
    void  paintEvent( QPaintEvent * );
    void  mousePressEvent( QMouseEvent * );
    void  mouseMoveEvent( QMouseEvent * );
    void  mouseReleaseEvent( QMouseEvent * );
private:
    void  stopShooting();
    void  paintShot( QPainter * );
    void  paintTarget( QPainter * );
    void  paintBarrier( QPainter * );
    void  paintCannon( QPainter * );
    QRect cannonRect() const;
    QRect shotRect() const;
    QRect targetRect() const;
    QRect barrierRect() const;
    bool  barrelHit( const QPoint & ) const;

    int   ang;
    int   f;
    bool  shooting;

    int   timerCount;
    float shoot_ang;
    float shoot_f;

    QPoint target;

    bool gameEnded;
    bool barrelPressed;
};

#endif // CANNON_H
