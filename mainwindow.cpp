#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QElapsedTimer>
#include <QDebug>
#include <algorithm>
#include <stack>

// Inisialisasi variabel statis untuk sorting Graham Scan
QPoint DrawingWidget::pivot;

//====================================================================
// Implementasi DrawingWidget
//====================================================================

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    // Set background putih dan ukuran minimum
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
    setMinimumSize(400, 300);
}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    // Tambahkan titik saat mouse diklik
    if (event->button() == Qt::LeftButton) {
        m_points.append(event->pos());
        m_hullPoints.clear(); // Hapus hull lama jika ada titik baru
        update(); // Jadwalkan repaint
    }
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. Gambar semua titik
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    for (const QPoint &point : m_points) {
        painter.drawEllipse(point, 3, 3);
    }

    // 2. Gambar Convex Hull jika sudah dihitung
    if (!m_hullPoints.isEmpty()) {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(Qt::NoBrush);

        // Buat poligon dari titik-titik hull
        QPolygonF hullPolygon;
        for(const QPoint &p : m_hullPoints) {
            hullPolygon << p;
        }
        painter.drawPolygon(hullPolygon);
    }
}

void DrawingWidget::clearPoints() {
    m_points.clear();
    m_hullPoints.clear();
    update();
}


//=========================================================
// ALGORITMA CONVEX HULL
//=========================================================

// Helper: Menentukan orientasi dari tiga titik (p, q, r)
// 0 --> p, q dan r segaris (collinear)
// 1 --> Searah jarum jam (Clockwise)
// 2 --> Berlawanan arah jarum jam (Counterclockwise)
int DrawingWidget::orientation(const QPoint &p, const QPoint &q, const QPoint &r) {
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
              (q.x() - p.x()) * (r.y() - q.y());
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

//--- SLOW CONVEX HULL: GIFT WRAPPING (JARVIS MARCH) ---
void DrawingWidget::calculateSlowHull() {
    if (m_points.size() < 3) return;

    QElapsedTimer timer;
    timer.start();

    m_hullPoints = giftWrapping(m_points);

    qDebug() << "Slow Convex Hull (Gift Wrapping) selesai dalam" << timer.elapsed() << "ms.";
    update();
}

QVector<QPoint> DrawingWidget::giftWrapping(const QVector<QPoint>& points) {
    int n = points.size();
    if (n < 3) return {};

    QVector<QPoint> hull;

    // 1. Cari titik paling kiri
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x() < points[l].x()) {
            l = i;
        }
    }

    // 2. Mulai dari titik paling kiri, terus bergerak berlawanan arah jarum jam
    int p = l, q;
    do {
        hull.append(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // Temukan titik 'q' yang paling berlawanan arah jarum jam
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }
        p = q;
    } while (p != l);

    return hull;
}


//--- FAST CONVEX HULL: GRAHAM SCAN ---
void DrawingWidget::calculateFastHull() {
    if (m_points.size() < 3) return;

    QElapsedTimer timer;
    timer.start();

    m_hullPoints = grahamScan(m_points);

    qDebug() << "Fast Convex Hull (Graham Scan) selesai dalam" << timer.elapsed() << "ms.";
    update();
}

// Helper: Menghitung kuadrat jarak
int DrawingWidget::distSq(const QPoint &p1, const QPoint &p2) {
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
           (p1.y() - p2.y())*(p1.y() - p2.y());
}

// Helper: Fungsi pembanding untuk sorting berdasarkan sudut polar
bool DrawingWidget::comparePoints(const QPoint &p1, const QPoint &p2) {
    int o = DrawingWidget().orientation(pivot, p1, p2);
    if (o == 0) { // Jika segaris
        // Titik yang lebih dekat akan didahulukan
        return distSq(pivot, p1) < distSq(pivot, p2);
    }
    // Jika tidak segaris, urutkan berdasarkan arah berlawanan jarum jam
    return (o == 2);
}

QVector<QPoint> DrawingWidget::grahamScan(QVector<QPoint> points) {
    int n = points.size();
    if (n < 3) return {};

    // 1. Cari titik dengan y terendah (dan x terendah jika y sama)
    int ymin = points[0].y(), min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y();
        if ((y < ymin) || (ymin == y && points[i].x() < points[min].x())) {
            ymin = points[i].y();
            min = i;
        }
    }

    // 2. Tempatkan titik terendah di awal
    std::swap(points[0], points[min]);

    // 3. Urutkan n-1 titik lainnya berdasarkan sudut polar relatif terhadap titik pertama (pivot)
    pivot = points[0];
    std::sort(points.begin() + 1, points.end(), comparePoints);

    // 4. Proses titik-titik yang sudah diurutkan
    std::stack<QPoint> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    for (int i = 3; i < n; i++) {
        // Terus hapus titik teratas dari stack selama titik tersebut membuat belokan searah jarum jam
        while (s.size() > 1) {
            QPoint top = s.top();
            s.pop();
            QPoint next_to_top = s.top();
            s.push(top);

            if (orientation(next_to_top, s.top(), points[i]) != 1) { // Jika tidak clockwise
                s.pop();
            } else {
                break;
            }
        }
        s.push(points[i]);
    }

    // Salin isi stack ke hasil akhir
    QVector<QPoint> hull;
    while (!s.empty()) {
        hull.push_back(s.top());
        s.pop();
    }
    // Karena stack LIFO, hasilnya terbalik. Kita bisa reverse, atau biarkan saja
    // karena QPolygon bisa menggambar dengan urutan apapun.
    // std::reverse(hull.begin(), hull.end());

    return hull;
}


//====================================================================
// Implementasi MainWindow
//====================================================================

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Convex Hull Visualizer");

    // Widget utama dan layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    drawingWidget = new DrawingWidget(this);
    mainLayout->addWidget(drawingWidget);

    // Layout untuk tombol-tombol
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    slowHullButton = new QPushButton("Hitung Slow Hull (Jarvis March)", this);
    fastHullButton = new QPushButton("Hitung Fast Hull (Graham Scan)", this);
    clearButton = new QPushButton("Bersihkan", this);

    buttonLayout->addWidget(slowHullButton);
    buttonLayout->addWidget(fastHullButton);
    buttonLayout->addStretch(); // Spacer
    buttonLayout->addWidget(clearButton);

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);

    // Hubungkan sinyal tombol ke slot di DrawingWidget
    connect(slowHullButton, &QPushButton::clicked, drawingWidget, &DrawingWidget::calculateSlowHull);
    connect(fastHullButton, &QPushButton::clicked, drawingWidget, &DrawingWidget::calculateFastHull);
    connect(clearButton, &QPushButton::clicked, drawingWidget, &DrawingWidget::clearPoints);
}

MainWindow::~MainWindow() {}
