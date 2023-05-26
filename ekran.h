#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>


struct coord
{
    int x;
    int y;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
        explicit Ekran(QWidget *parent = nullptr);
protected:
        void paintEvent(QPaintEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mousePressEvent(QMouseEvent *);
        void linia(int x1,int y1,int x2,int y2,int r,int g,int b);
        void rysujKrzywa();
private:
        QImage im;
        void drawPunkt(int x,int y,int r,int g,int b);
        void drawPixel(int x,int y,int r,int g,int b);
        coord p1;
        coord p2;
        int id=-1;
        QVector<coord> lista;
signals:

};

#endif // EKRAN_H
