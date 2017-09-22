#include <QSql>

#include "window.h"
#include "logowindow.h"
#include "authorization.h"
#include <QtWidgets>

Window::Window(): QWidget(0, Qt::Window | Qt::FramelessWindowHint)
{
    logoWindow = new Logo();
    logoWindow->show();

    authWindow = new Auth();
    //authWindow->show();

    setAttribute(Qt::WA_TranslucentBackground);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(openWindow()));
    timer->start(3000);
}

void Window::openWindow()
{
    logoWindow->close();
    authWindow->show();
    //logoWindow->show();
    //timer->stop();
}




