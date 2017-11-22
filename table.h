#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include "database.h"

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

class Table : public QMainWindow
{
        Q_OBJECT

public:
    explicit Table(QWidget *parent = 0);
        ~Table();

private:
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    QGroupBox *groupTable();
    DataBase        *db;
    QSqlTableModel  *model;
    QTableView *tableView;


private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();


};

#endif // TABLE_H
