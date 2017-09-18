#ifndef ANOTHERWINDOW_H
#define ANOTHERWINDOW_H

#include <QWidget>
#include <QtSql>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

class AnotherWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnotherWindow(QWidget *parent = 0);

signals:
    void firstWindow();

private slots:
    void openWindow();

private:
    QGroupBox *createGroup();
    QPushButton *pushButton;
};

#endif // ANOTHERWINDOW_H
