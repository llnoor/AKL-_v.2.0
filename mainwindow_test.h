#ifndef MAINWINDOW_T_H
#define MAINWINDOW_T_H

#include <QMainWindow>
#include <QSqlTableModel>

#include <database.h>
#include <dialogadddevice.h>

namespace Ui {
class MainWindow;
}

class MainWindow_T : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_T(QWidget *parent = 0);
    ~MainWindow_T();

private slots:
    void on_addDeviceButton_clicked();
    void slotUpdateModels();
    void slotEditRecord(QModelIndex index);

private:
    Ui::MainWindow              *ui;
    DataBase                    *db;
    QSqlTableModel              *modelDevice;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_T_H
