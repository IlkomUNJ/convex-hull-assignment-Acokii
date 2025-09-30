#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *iterationLabel = ui->iteration;

    iterationLabel->setText(QString::number(iteration));
    connect(ui->clearDot, &QPushButton::clicked,
            ui->coordinatebox, &CoordinateBox::clearPoints);
    connect(ui->coordinatebox, &CoordinateBox::addPoint,
            this, &MainWindow::handleAddPoint);

}

QPoint checkNearest(const QPoint& setter, const QVector<QPoint>& setList){
    qreal minDis = -1;
    QPoint nearestPossible;

    for(const QPoint i:setList){
        qreal distance = qPow(i.x() - setter.x(), 2) + qPow(i.y() - setter.y(), 2);
        if(minDis == -1 || distance < minDis){
            minDis = distance;
            nearestPossible = i;
        }
    }
    return nearestPossible;
}

void MainWindow::handleAddPoint(QPoint point){
    hull_points.append(point);
    qDebug() << "add point:" << point << "to x_points";
}

// checking is the point is the valid hull point
bool is_hull(QPoint& p, QPoint& q, QVector<QPoint>& allSet ){
    for(QPoint r:allSet){
        // set vector point
        QPoint pq = QPoint(q.x()-p.x(),q.y()-p.y());
        QPoint pr = QPoint(r.x()-p.x(),r.y()-p.y());

        // set the position
        qreal position = pq.x()*pr.y() - pq.y()*pr.x();

        //if position is > 0 then it's on the left and it's not the hull point
        if(position > 0){
            return false;
        }
    };
    return true;
}

void slow_convex(QVector<QPoint> hull_points, QVector<QPoint> *filtered){
    QVector<QPoint> checked = hull_points;
    QPoint p = QPoint(-1,-1);

    if(checked.isEmpty()){
        return;
    }else{
        // set p to the leftest point
        for(QPoint x:checked){
            if(p.y() == -1 || x.y() < p.y()){
                p = x;
            }
        }

        // search the nearest point from the p
        QPoint nearest = checkNearest(p, checked);

        if(is_hull(p,nearest,hull_points)){
            checked.remove(nearest.dotProduct())
        }
    }
}
void MainWindow::on_slowConvex_clicked(){
    slow_convex(hull_points, &hull_points);
}
MainWindow::~MainWindow()
{
    delete ui;
}
