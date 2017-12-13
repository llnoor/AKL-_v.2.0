#ifndef DIALOGAUTH_H
#define DIALOGAUTH_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include "database.h"
#include <QTableView>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

class DialogAuth : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAuth(int row = -1, QWidget *parent = 0);
    ~DialogAuth();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

private:
    QGroupBox                   *groupTableAuth();
    QTableView                  *tableViewEditAuth;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;
    QPushButton                 *previousButton;
    QPushButton                 *nextButton;
    QLineEdit                   *HostnameLineEdit;
    QLineEdit                   *IPAddressLineEdit;
    QLineEdit                   *MACLineEdit;

private:
    void setupModel();
    void createUI();
    void accept();

};

#endif // DIALOGAUTH_H
