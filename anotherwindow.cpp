#include <QtWidgets>
#include "anotherwindow.h"


AnotherWindow::AnotherWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createGroup(), 0, 0);
    setLayout(grid);

    setWindowTitle(tr("Second Group Boxes"));
    resize(480, 320);

    connect(pushButton, SIGNAL (released()),this,SLOT(openWindow()));
}

void AnotherWindow::openWindow()
{
    this->close();
    emit firstWindow();
}


QGroupBox *AnotherWindow::createGroup()
{
    QGroupBox *groupBox = new QGroupBox();

    pushButton = new QPushButton(tr("&Normal Button"));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    groupBox->setLayout(vbox);

    return groupBox;
}


