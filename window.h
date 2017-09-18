/****************************************************************************
**
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtSql>
#include <anotherwindow.h>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

    float new_sql();

private slots:
    void openWindow();

private:
    QGroupBox *createPushButtonGroup();
    AnotherWindow *sWindow;
    AnotherWindow *thirdWindow;
    QPushButton *pushButton;

};
//! [0]

#endif
