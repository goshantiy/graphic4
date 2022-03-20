#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "figura.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
    Figura* myFigura;
};
#endif // WINDOW_H
