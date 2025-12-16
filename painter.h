#ifndef PAINTER_H
#define PAINTER_H

#include<QPainter>
#include<QPushButton>
#include<QWidget>
#include<QPaintEvent>
#include<QVector>
#include<QPointF>
#include<QApplication>
#include<QMainWindow>
#include<cmath>

class painter : public QWidget {
    Q_OBJECT
private:
    QPushButton *L;
    bool der,Clicked;
    double muti,move_x,move_y;
    QPoint Start,End,Last;
public:
    painter(QWidget *parent = nullptr) : QWidget(parent) {
        setFocusPolicy(Qt::StrongFocus);
        setFixedSize(800,600);
        der=Clicked=0;
        muti=1;
        move_x=move_y=0;
        L=new QPushButton("Take the derivative",this);
        L->setGeometry(600,560,170,20);
        connect(L,&QPushButton::clicked,this,&painter::derivative);
    }
    double calculate(double a);
    void derivative();

protected:
    void paintEvent(QPaintEvent *event) override ;
    void wheelEvent(QWheelEvent *event) override ;
    void keyPressEvent(QKeyEvent *event) override ;
    void mousePressEvent(QMouseEvent *event) override ;
    void mouseMoveEvent(QMouseEvent *event) override ;
    void mouseReleaseEvent(QMouseEvent *event) override ;
};

#endif // PAINTER_H
