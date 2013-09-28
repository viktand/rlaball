#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSize>
#include <QPainter>
#include <math.h>

#define PI 3.14159265

QPixmap *mem_pix;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dial_valueChanged(int value) // вращение "колесика"
{
    if (mem_pix==0) mem_pix = new QPixmap(*ui->rLabel->pixmap());
    ui->rLabel->setPixmap(rotor(value, *mem_pix));
    QSize sz;
    QRect rc;
    QPoint pn;
    rc=ui->rLabel->geometry();
    pn.setX(rc.x()+rc.width()/2);
    pn.setY(rc.y()+rc.height()/2);
    sz=ui->rLabel->pixmap()->size();
    rc.setWidth(sz.width());
    rc.setHeight(sz.height());
    rc.setX(pn.x()-rc.width()/2);
    rc.setY(pn.y()-rc.height()/2);
    ui->rLabel->setGeometry(rc);
    ui->label->setText(QString::number(value));
}

QPixmap MainWindow::rotor(int a, QPixmap pix)
{
    double g=a*PI/180;
    QSize sz=pix.size();
    QPixmap canv_pix(sz*2);
    canv_pix.fill(Qt::transparent); // залить пустотой
    // центр холста
    int x=sz.width();
    int y=sz.height();
    QPainter p(&canv_pix);
    p.translate(x,y);
    p.rotate(a);
    p.translate(-x,-y);
    p.drawPixmap(x/2,y/2, pix);
    p.end();
    int h=x*fabs(sin(g))+ y*fabs(cos(g));
    int w=x*fabs(cos(g))+ y*fabs(sin(g));
    x=x-w/2;
    y=y-h/2;
    pix=canv_pix.copy(x, y, w, h);
    return pix;
}
