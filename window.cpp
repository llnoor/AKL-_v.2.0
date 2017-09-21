#include <QSql>

#include "window.h"
#include "logowindow.h"
#include <QtWidgets>

Window::Window(): QWidget(0, Qt::Window | Qt::FramelessWindowHint)
{
    logoWindow = new Logo();
    logoWindow->show();

    setAttribute(Qt::WA_TranslucentBackground);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(openWindow()));
    timer->start(100);
}

void Window::openWindow()
{
    logoWindow->show();
}




