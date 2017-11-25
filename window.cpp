#include "window.h"
#include "logowindow.h"
#include "authorization.h"
#include "sqlamp.h"
#include "experiments.h"


Window::Window() : QWidget(0, Qt::Window | Qt::FramelessWindowHint)
{
    logoWindow = new Logo();
    //logoWindow->show();

    //sqLamp = new SQLamp();

    //Exp = new Experiments();
    //Exp->show();


    authWindow = new Auth();
    //authWindow->show();

    //MainWindow_Test = new MainWindow_T();
    //MainWindow_Test ->show();

    setAttribute(Qt::WA_TranslucentBackground);
    //timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(openWindow()));
    //timer->start(3000); //timer->setInterval(3000); timer->start();

    connect(logoWindow, SIGNAL(firstWindow()) , authWindow, SLOT(openWindow()) );
}

void Window::openWindow()
{
    //logoWindow->close();
    //authWindow->show();
    //logoWindow->show();
    //timer->stop();
}




