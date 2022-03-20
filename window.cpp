#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    setFixedSize(600,400);
    myFigura = new Figura(this);
}

Window::~Window()
{
    delete ui;
}

