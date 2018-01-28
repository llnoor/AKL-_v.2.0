#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtSql>
#include <logowindow.h>
#include <authorization.h>
#include <sqlamp.h>
#include <experiments.h>


class Window : public QWidget
{
    Q_OBJECT
public:
    Window();

private slots:
    void openWindow();
    void login(QString loginQString);

private:
    QTimer *timer;
    Logo *logoWindow;
    AuthorizationWindow *authWindow;
    SQLamp *sqLamp;
    Experiments *exprimentsWindow;




};

#endif


