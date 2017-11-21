#ifndef MAINWINDOW_TEST_H
#define MAINWINDOW_TEST_H

#include <QTableView>
#include <QWidget>
#include <QtSql>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QMainWindow>
#include <QSqlTableModel>

#include <database.h>
#include <dialogadddevice.h>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

class MainWindow_Test : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow_Test();

private slots:
    void on_addDeviceButton_clicked();
    void slotUpdateModels();
    void slotEditRecord(QModelIndex index);

private:
    DataBase                    *db;
    QSqlTableModel              *modelDevice;
    QGroupBox *groupTest();
    QLabel *label;
    QTableView *deviceTableView;
    QPushButton *addDeviceButton;
    QPushButton *editDeviceButton;
    QPushButton *selectDeviceButton;


private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_TEST_H
