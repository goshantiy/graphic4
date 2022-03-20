#ifndef FIGURA_H
#define FIGURA_H

#include <QWidget>

#include "matrix.h"
#include "camera.h"

#define PI 3.14159265

class Figura : public QWidget
{
    Q_OBJECT
public:
    Figura(QWidget *parent = nullptr);


private:


    void paintEvent(QPaintEvent *event) override;
    const Matrix window(const Matrix &vertices);
    void setAngles(float rotationX, float rotationY);
    float y(const float &x, const float &z);

//6
//    float xMin = -2;
//    float xMax = 2;
//    float zMin = -2;
//    float zMax = 2;

    //8
    float xMin = -2*PI;
    float xMax = 2*PI;
    float zMin = -2*PI;
    float zMax = 2*PI;


    //10
//        float xMin = -2*PI;
//        float xMax = 2*PI;
//        float zMin = -2*PI;
//        float zMax = 2*PI;

    //13
    //float xMin = -2;
    //float xMax = 2;
    //float zMin = -2;
    //float zMax = 2;


    //14
//        float xMin = -6*PI;
//        float xMax = 6*PI;
//        float zMin = -3*PI;
//        float zMax = 3*PI;

    //15
//    float xMin = -5;
//    float xMax = 5;
//    float zMin = -5;
//    float zMax = 5;

    int stepCount = 100;
    Matrix ver;
    Matrix rotation;
    Matrix corners_;
    float angleY = 0;
    float angleX = 15;
    float dA = 5;
    int myTimer;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // FIGURA
