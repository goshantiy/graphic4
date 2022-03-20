#include "figura.h"
#include <QPainter>
#include <QPoint>
#include <cmath>
#include <QTimerEvent>

#include <algorithm>

#define PI 3.14159265

Figura::Figura(QWidget *parent) :QWidget(parent),
    ver(stepCount*stepCount,4), rotation(4,4), corners_
{
    { xMin, 0, zMin, 1 },
    { xMax, 0, zMin, 1 },
    { xMin, 0, zMax, 1 },
    { xMax, 0, zMax, 1 },
}
{
    this->setWindowTitle("Lab 4");
    setFixedSize(600,400);
    setAutoFillBackground(true);
    Camera::LookAt(0, 0, -1);
    Camera::Ortho(this->width() / 2, this->height() / 2, 1);
    float stepZ = (zMax - zMin) / stepCount;
    float stepX = (xMax - xMin) / stepCount;
    int k = 0;
    float z = zMin;
    for(int i = 0; i < stepCount; i++, z += stepZ)
    {
        float x = xMin;
        for(int j = 0; j < stepCount; j++, x += stepX, k++)
        {
            ver[k][0] = x;
            ver[k][1] = y(x,z);
            ver[k][2] = z;
            ver[k][3] = 1;
        }
    }
    setAngles(angleX,angleY);
}

void Figura::paintEvent(QPaintEvent *event)
{
    Matrix vertices = window(ver * rotation) * Camera::projection();
    QPainter painter(this);
    QVector<int> lower(this->width());
    QVector<int> upper(this->width());
    lower.fill(this->height());
    upper.fill(0);
    QVector<int> lower_n(lower);
    QVector<int> upper_n(upper);
    int x0, y0, x1, y1;
    bool flag_p, flag;
    int v = 0;

    for (int z = 0; z < stepCount; z++)
    {
        for (int x = 0; x < stepCount; x++)
        {
            x1 = round(vertices[v][0]);
            y1 = round(vertices[v][1]);
            flag = y1 < lower[x1] || y1 > upper[x1];
            if (x != 0 && (flag_p || flag))
            {
                int dx = abs(x1 - x0);
                int xi = -1;
                if(x0<x1)
                    xi = 1;
                int dy = -abs(y1 - y0);
                int yi = -1;
                if(y0 < y1)
                    yi = 1;
                int de = dx + dy;
                while (true)
                {
                    int flag = 0;
                    if (lower[x0] > y0)
                    {
                        lower_n[x0] = y0;
                        flag |= 1;
                    }
                    if (upper[x0] < y0)
                    {
                        upper_n[x0] = y0;
                        flag |= 2;
                    }
                    if (flag == 3)
                    {
                        painter.setPen(Qt::green);
                        painter.drawPoint(x0, y0);
                    }
                    else if (flag & 1)
                    {painter.setPen(Qt::red);
                        painter.drawPoint(x0, y0);
                    }
                    else if (flag & 2)
                    {painter.setPen(Qt::black);
                        painter.drawPoint(x0, y0);
                    }
                    if (x0 == x1 && y0 == y1) break;
                    int de2 = 2 * de;
                    if (de2 >= dy)
                    {
                        de += dy;
                        x0 += xi;
                    }
                    if (de2 <= dx)
                    {
                        de += dx;
                        y0 += yi;
                    }
                }
            }
            else
            {
                x0 = x1;
                y0 = y1;
            }
            flag_p = flag;
            v++;
        }
        lower = lower_n;
        upper = upper_n;
    }
}

const Matrix Figura::window(const Matrix &vertices)
{
    Matrix corners = corners_ * rotation;
    float norm_x = abs((*std::max_element(corners.begin(), corners.end(), [](const row &a, const row &b) { return abs(a[0]) < abs(b[0]); }))[0]);
    float norm_y = abs((*std::max_element(vertices.begin(), vertices.end(), [](const row &a, const row &b) { return abs(a[1]) < abs(b[1]); }))[1]);
    float k = std::min(this->width() / 2 / norm_x, this->height() / 2 / norm_y);

    return vertices * Matrix
        {
            { k, 0, 0, 0 },
            { 0, k, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 1 },
        };
}

void Figura::setAngles(float rotationX, float rotationY)
{
    float sinX = std::sin(rotationX * PI / 180);
    float cosX = std::cos(rotationX * PI / 180);
    float sinY = std::sin(rotationY * PI / 180);
    float cosY = std::cos(rotationY * PI / 180);
    rotation = Matrix({{cosY,0,sinY,0},
                       {0,1,0,0},
                       {-sinY,0,cosY,0},
                       {0,0,0,1}}) *
               Matrix({{1,0,0,0},
                       {0,cosX,-sinX,0},
                       {0,sinX,cosX,0},
                       {0,0,0,1}});
}

float Figura::y(const float &x, const float &z)
{



    //6
    //return(x*z*(x+z)*(x-z));

    //8
    return (std::cos(-std::sqrt(x*x + z*z)));

    //10
//    float a = (std::sqrt((x*x+z*z)));
//    return (cos(a)/(a+1));

    //13
    //float a = x * x + z * z;
    //return -1.5f * cos(1.75f * a) * exp(-a) + 0.2f * sin(x + PI) * cos(z + PI);


    //14
//    float a = (std::sqrt((x+3*PI)*(x+3*PI)+z*z));
//    float b = (std::sqrt((x-3*PI)*(x-3*PI)+z*z));
//    return (cos(a)/(a+1) + cos(b)/(b+1));

    //15
    //return (-1*log((abs (x*x*(x*x-z*z)))+0.15));


}


void Figura::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(30);
}

void Figura::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == myTimer)
    {
        if(angleY > 45 || angleY < -45)
            dA *= -1;
        angleY += dA;
        setAngles(angleX,angleY);
        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Figura::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}
