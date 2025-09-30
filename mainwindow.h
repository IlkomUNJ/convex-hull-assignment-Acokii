#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <coordinatebox.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_slowConvex_clicked();

private slots:
    void handleAddPoint(QPoint point);

private:
    Ui::MainWindow *ui;
    QVector<QPoint> x_points;
    QVector<QPoint> hull_points;
    int iteration = 0;
};
#endif // MAINWINDOW_H
