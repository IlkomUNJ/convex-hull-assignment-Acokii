#include "coordinatebox.h"
#include <QDebug>

CoordinateBox::CoordinateBox(QWidget *parent) : QGroupBox(parent) {}

void CoordinateBox::paintEvent(QPaintEvent *event)
{
    QGroupBox::paintEvent(event); // Penting: Panggil fungsi base class

    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 5)); // Atur warna dan ketebalan titik

    for (const QPoint &point : m_points) {
        painter.drawPoint(point);
    }
}

void CoordinateBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int yOffset = contentsRect().y();
        QPoint adjusted = event->pos();
        if(adjusted.y()<yOffset){
            return;
        }else{
            m_points.append(adjusted);
            update();
        }
    }
    emit addPoint(event->pos());
}

void CoordinateBox::clearPoints(){
    m_points.clear();
    qDebug() << "x_points emptied";
    update();
}
// void CoordinateBox::mouseMoveEvent(QMouseEvent *event)
// {
//     // Hanya tambahkan titik jika tombol kiri mouse ditekan
//     if (event->buttons() & Qt::LeftButton) {
//         m_points.append(event->pos());
//         update(); // Perbarui widget untuk memicu paintEvent
//     }
// }

// void CoordinateBox::mouseReleaseEvent(QMouseEvent *event)
// {
//     // Opsional: Anda bisa menambahkan logika di sini setelah gambar selesai
//     // Misalnya, untuk memproses titik-titik yang telah digambar
// }
