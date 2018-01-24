#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include <QMainWindow>
#include <QSqlTableModel>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include <database.h>
#include <dialogauth.h>
#include <dialogreg.h>
#include <QTableView>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

class Experiments : public QWidget
{
    Q_OBJECT

public:
    explicit Experiments(QWidget *parent = 0);
    //~Experiments();

signals:
    void showlogoWindow();
    //void openExperiments();

private slots:
    //void on_addDeviceButton_clicked();

    void slotUpdateModels();
    void slotLogin(QModelIndex index);
    void slotNewUser();
    void slotEditUser(QModelIndex index);

private:

    DataBase        *db;
    QSqlTableModel  *model;
    QGroupBox *groupTable();
    QTableView *tableView;
    QPushButton *newuserButton;
    QPushButton *edituserButton;
    QPushButton *tableButton;


private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // EXPERIMENTS_H
