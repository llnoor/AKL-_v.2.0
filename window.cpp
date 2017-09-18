#include <QtWidgets>
#include "window.h"
#include "anotherwindow.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createPushButtonGroup(), 0, 0);
    setLayout(grid);

    setWindowTitle(tr("First Group Boxes"));
    resize(480, 320);

    sWindow = new AnotherWindow();

    //Connect()
    connect(pushButton, SIGNAL (released()),this,SLOT(openWindow()));
    connect(sWindow, &AnotherWindow::firstWindow, this, &Window::show);


}

void Window::openWindow()
{
    sWindow->show();
    this->close();
}

QGroupBox *Window::createPushButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox();

    pushButton = new QPushButton(tr("&Normal Button"));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    groupBox->setLayout(vbox);

    return groupBox;
}

