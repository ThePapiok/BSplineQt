#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <cstdio>
#include <cstdlib>
#include <cmath>

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im=QImage(1000, 1000, QImage::Format_RGB32);
    im.fill(0);
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    p2.x=e->pos().x();
    p2.y=e->pos().y();
    if(id!=-1)
    {
        lista[id].x=p2.x;
        lista[id].y=p2.y;
        rysujKrzywa();
    }
}

void Ekran::mousePressEvent(QMouseEvent *e)
{
    id=-1;
    int dl=lista.length()-1;
    p1.x=e->pos().x();
    p1.y=e->pos().y();
    if(e->button()==Qt::RightButton)
    {
        lista.push_back(p1);
        rysujKrzywa();
    }
    else if(e->button()==Qt::MiddleButton)
    {
        for(int i=0;i<=dl;i++)
        {
            if(sqrt(pow((p1.x-lista[i].x),2)+pow((p1.y-lista[i].y),2))<=8)
            {
                lista.erase(lista.begin()+i);
                rysujKrzywa();
                break;
            }
        }
    }
    else if(e->button()==Qt::LeftButton)
    {
        for(int i=0;i<=dl;i++)
        {
            if(sqrt(pow((p1.x-lista[i].x),2)+pow((p1.y-lista[i].y),2))<=8)
            {
                id=i;
                break;
            }
        }
    }
}

void Ekran::drawPunkt(int x,int y,int r,int g,int b)
{
    for(int i=y-2;i<=y+2;i++)
    {
        for(int j=x-2;j<=x+2;j++)
        {
            if((j<im.width()&&j>=0)&&(i<im.height()&&i>=0))
            {
                uchar *pix=im.scanLine(i)+4*j;
                pix[0]=b;
                pix[1]=g;
                pix[2]=r;
            }
        }
    }


}

void Ekran::drawPixel(int x,int y,int r,int g,int b)
{
    if((x<im.width()&&x>=0)&&(y<im.height()&&y>=0))
    {
        uchar *pix=im.scanLine(y)+4*x;
        pix[0]=b;
        pix[1]=g;
        pix[2]=r;
    }
}

void Ekran::linia(int x1,int y1,int x2,int y2,int r,int g,int b)
{
    if(abs(y2-y1)<=abs(x2-x1))
        {
            float y=y1;
            float a=(float)(y2-y1)/(x2-x1);
            if(x1<x2)
            {
                for(int i=x1;i<=x2;i++)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b);
                    y+=a;
                }
            }
            else
            {
                for(int i=x1;i>=x2;i--)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b);
                    y-=a;
                }
            }

        }
        else
        {
            float x=x1;
            float a=(float)(x1-x2)/(y1-y2);
            if(y1<y2)
            {
                for(int i=y1;i<=y2;i++)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b);
                    x+=a;
                }
            }
            else
            {
                for(int i=y1;i>=y2;i--)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b);
                    x-=a;
                }
            }
        }
}

void Ekran::rysujKrzywa()
{
    int dl=lista.length()-1;
    double t;
    int x,y,xold,yold;
    im.fill(0);
    if(dl>=3)
    {
        for(int i=0;i<=dl;i++)
        {
            drawPunkt(lista[i].x,lista[i].y,102,102,255);
        }
    }
    if(dl>=3)
    {
    for(int i=3;i<=dl;i++)
    {

        xold=(1.0/6)*lista[i-3].x+(4.0/6)*lista[i-2].x+(1.0/6)*lista[i-1].x;
        yold=(1.0/6)*lista[i-3].y+(4.0/6)*lista[i-2].y+(1.0/6)*lista[i-1].y;
        for(int j=1;j<=100;j++)
        {
            t=j/100.0;
            x=((-pow(t,3)+3*t*t-3*t+1)*lista[i-3].x)/6+((3*pow(t,3)-6*t*t+4)*lista[i-2].x)/6+((-3*pow(t,3)+3*t*t+3*t+1)*lista[i-1].x)/6+pow(t,3)*lista[i].x/6;
            y=((-pow(t,3)+3*t*t-3*t+1)*lista[i-3].y)/6+((3*pow(t,3)-6*t*t+4)*lista[i-2].y)/6+((-3*pow(t,3)+3*t*t+3*t+1)*lista[i-1].y)/6+pow(t,3)*lista[i].y/6;
            linia(xold,yold,x,y,255,255,255);
            xold=x;
            yold=y;


        }
    }
    }
    else
    {
        for(int i=0;i<=dl;i++)
        {
            drawPunkt(lista[i].x,lista[i].y,255,255,0);
        }

    }
    update();
}
