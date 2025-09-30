#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>

// Forward declaration
class QPushButton;

// Kelas kustom untuk area gambar
class DrawingWidget : public QWidget {
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);

public slots:
    void calculateSlowHull();
    void calculateFastHull();
    void clearPoints();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    // Fungsi untuk menghitung orientasi tiga titik
    int orientation(const QPoint &p, const QPoint &q, const QPoint &r);
    
    // Fungsi untuk membandingkan titik untuk Graham Scan sort
    static QPoint pivot;
    static int distSq(const QPoint &p1, const QPoint &p2);
    static bool comparePoints(const QPoint &p1, const QPoint &p2);

    // Algoritma Convex Hull
    QVector<QPoint> giftWrapping(const QVector<QPoint>& points); // Slow
    QVector<QPoint> grahamScan(QVector<QPoint> points);          // Fast

    QVector<QPoint> m_points;      // Titik-titik yang diinput user
    QVector<QPoint> m_hullPoints;  // Titik-titik yang membentuk hull
};


// Kelas Window Utama
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DrawingWidget *drawingWidget;
    QPushButton *slowHullButton;
    QPushButton *fastHullButton;
    QPushButton *clearButton;
};

#endif // MAINWINDOW_H
