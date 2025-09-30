#ifndef COORDINATEBOX_H
#define COORDINATEBOX_H

#include <QGroupBox>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QVector>
#include <QPoint>

class CoordinateBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit CoordinateBox(QWidget *parent = nullptr);
    void clearPoints();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override ;

signals:
    void addPoint(QPoint point);

private:
    QVector<QPoint> m_points;
};

#endif // COORDINATEBOX_H
