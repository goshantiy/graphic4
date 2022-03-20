#include "camera.h"

#include "matrix.h"

#include <cmath>


float Camera::x_;
float Camera::y_;
float Camera::z_;

Matrix Camera::view_(4, 4);
Matrix Camera::projection_(4, 4);

void Camera::LookAt(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;

    Matrix T
    {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { -x, -y, -z, 1 },
    };

    Matrix S
    {
        { -1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    Matrix R_90
    {
        { 1, 0, 0, 0 },
        { 0, 0, -1, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 0, 1 },
    };

    //
    float s, c;
    float d = sqrt(x * x + y * y);

    if (d == 0)
    {
        c = 1;
        s = 0;
    }
    else
    {
        c = y / d;
        s = x / d;
    }

    Matrix R_u
    {
        { c, 0, s, 0 },
        { 0, 1, 0, 0 },
        { -s, 0, c, 0 },
        { 0, 0, 0, 1 },
    };

    //
    float l = sqrt(d * d + z * z);

    if (l == 0)
    {
        c = 1;
        s = 0;
    }
    else
    {
        c = d / l;
        s = z / l;
    }

    Matrix R_w
    {
        { 1, 0, 0, 0 },
        { 0, c, -s, 0 },
        { 0, s, c, 0 },
        { 0, 0, 0, 1 },
    };

    view_ = T * S * R_90 * R_u * R_w;
}

void Camera::Ortho(float offset_x, float offset_y, float zoom)
{
    projection_ = Matrix
    {
        { zoom, 0, 0, 0 },
        { 0, -zoom, 0, 0 },
        { 0, 0, 0, 0 },
        { offset_x, offset_y, 0, 1 },
    };
}

