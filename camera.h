#ifndef CAMERA_H
#define CAMERA_H
#include <QPainter>

#include "matrix.h"

class Camera
{
    friend Figura;
public:
    Camera() = delete;

    static const float x() { return x_; }
    static const float y() { return y_; }
    static const float z() { return z_; }

    static const Matrix &view() { return view_; }
    static const Matrix &projection() { return projection_; }

    static void LookAt(float x, float y, float z);
    static void Ortho(float offset_x, float offset_y, float zoom);

private:
    static float x_;
    static float y_;
    static float z_;
    static Matrix view_;
    static Matrix projection_;
};

#endif // CAMERA_H
