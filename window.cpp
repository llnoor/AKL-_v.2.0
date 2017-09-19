#include <QtWidgets>
#include <QLabel>
#include "window.h"
#include "anotherwindow.h"

Window::Window(QWidget *parent): QWidget(0, Qt::Window | Qt::FramelessWindowHint)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createPushButtonGroup(), 0, 0);
    setLayout(grid);

    setWindowTitle(tr("LAMP"));
    resize(480, 120);

    //QDesktopWidget *pDescwidget=QApplication::desktop();
    //move(pDescwidget->width()/2-width()/2, pDescwidget->height()/2-height()/2);


    sWindow = new AnotherWindow();
    setAttribute(Qt::WA_TranslucentBackground);
    //setStyleSheet("background:white;");

    setStyleSheet("background: rgba(255, 255, 255, 100);");
                  //"background-color: rgba(255, 255, 255, 100);");


    //Connect()
    connect(pushButton, SIGNAL (released()),this,SLOT(openWindow()));
    connect(sWindow, &AnotherWindow::firstWindow, this, &Window::show);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(openWindow()));
    timer->start(3000);


}

void Window::openWindow()
{
    sWindow->show();
    this->close();
    timer->stop();
}

QGroupBox *Window::createPushButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
    groupBox->setStyleSheet("border: 0px solid white");

    /*groupBox->setStyleSheet("QGroupBox {font: normal 13px \"Arial\";"
                            "border: 0px solid gray;} "
                            "QGroupBox::title "
                            "{"
                            "font: normal 18px \"Arial\"; "
                            "color: rgb(51,51,51); }");*/

    pushButton = new QPushButton(tr("&Normal Button"));

    label_1 = new QLabel(tr(" LAMP "));
    label_1->setFont(QFont("Russo One",100));
    label_1->setStyleSheet("color: gray;");

    label_2 = new QLabel(tr("         Laboratory for Advanced Materials Physics\n "));
    label_2->setFont(QFont("Russo One",13));
    label_2->setStyleSheet("color: gray;");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label_1);
    vbox->addWidget(label_2);
    //vbox->addWidget(pushButton);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setMargin(0);
    groupBox->setLayout(vbox);

    return groupBox;
}

