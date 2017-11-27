#include "database.h"
#include <QDateTime>
#include <QTime>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/Git/git/LAMP/DataBase/db/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/Git/git/LAMP/DataBase/db/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;

    //Table delete after tests
    if(query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_RANDOM    " INTEGER         NOT NULL,"
                            TABLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }


    //SCIENTISTS
    if(query.exec( "CREATE TABLE " SCIENTISTS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            SCIENTISTS_NAME                 " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_SURNAME              " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_LOGIN                " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_DATE                 " DATE            NOT NULL,"
                            SCIENTISTS_PARENT               " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_PASS                 " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_EMAIL                " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_TELEGRAM             " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_PHONE                " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_EXPERIMENTS          " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_SELECTED_EXPERIMENTS " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_BIRTHDAY             " DATE            NOT NULL,"
                            SCIENTISTS_POSITION             " VARCHAR(255)    NOT NULL,"
                            SCIENTISTS_THEME                " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << SCIENTISTS;
        qDebug() << query.lastError().text();
        return false;
    }

    //EXPERIMENTS
    if(query.exec( "CREATE TABLE " EXPERIMENTS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            EXPERIMENTS_NAME                    " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_DESCRIPTION             " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_AUTHOR                  " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_DATE                    " DATE            NOT NULL,"
                            EXPERIMENTS_DEVICES                 " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_PARENT                  " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_LINK                    " VARCHAR(255)    NOT NULL,"
                            EXPERIMENTS_CONF                    " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << EXPERIMENTS;
        qDebug() << query.lastError().text();
        return false;
    }

    //DEVICES
    if(query.exec( "CREATE TABLE " DEVICES " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            DEVICES_NAME                        " VARCHAR(255)    NOT NULL,"
                            DEVICES_TYPE                        " VARCHAR(255)    NOT NULL,"
                            DEVICES_DATE                        " DATE            NOT NULL,"
                            DEVICES_DESCRIPTION                 " VARCHAR(255)    NOT NULL,"
                            DEVICES_LINK                        " VARCHAR(255)    NOT NULL,"
                            DEVICES_CONF                        " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << DEVICES;
        qDebug() << query.lastError().text();
        return false;
    }

    //THEMES
    if(query.exec( "CREATE TABLE " THEMES " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            THEMES_NAME                         " VARCHAR(255)    NOT NULL,"
                            THEMES_DESCRIPTION                  " VARCHAR(255)    NOT NULL,"
                            THEMES_AUTHOR                       " VARCHAR(255)    NOT NULL,"
                            THEMES_CONF                         " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << THEMES;
        qDebug() << query.lastError().text();
        return false;
    }

    //LOGS
    if(query.exec( "CREATE TABLE " LOGS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            LOGS_NAME                       " VARCHAR(255)    NOT NULL,"
                            LOGS_DATE                       " DATE            NOT NULL,"
                            LOGS_TIME                       " TIME            NOT NULL,"
                            LOGS_TYPE                       " VARCHAR(255)    NOT NULL,"
                            LOGS_DESCRIPTION                " VARCHAR(255)    NOT NULL,"
                            LOGS_PROCESS                    " VARCHAR(255)    NOT NULL,"
                            LOGS_PROBLEM                    " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << LOGS;
        qDebug() << query.lastError().text();
        return false;
    }

    //EXPERIMENT
    if(query.exec( "CREATE TABLE " EXPERIMENT " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            EXPERIMENT_NAME                     " VARCHAR(255)    NOT NULL,"
                            EXPERIMENT_DESCRIPTION              " VARCHAR(255)    NOT NULL,"
                            EXPERIMENT_AUTHOR                   " VARCHAR(255)    NOT NULL,"
                            EXPERIMENT_DATE                     " DATE            NOT NULL,"
                            EXPERIMENT_TIME                     " TIME            NOT NULL,"
                            EXPERIMENT_DATA                     " VARCHAR(255)    NOT NULL,"
                            EXPERIMENT_TABLE                    " VARCHAR(255)    NOT NULL,"
                            EXPERIMENT_CONF                     " VARCHAR(255)    NOT NULL"
                        " )"
                    ))
    {
        //return true;
    } else {
        qDebug() << "DataBase: error of create " << EXPERIMENT;
        qDebug() << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO " LOGS " ( " LOGS_NAME ", "
                                              LOGS_DATE ", "
                                              LOGS_TIME ", "
                                              LOGS_TYPE ", "
                                              LOGS_DESCRIPTION ", "
                                              LOGS_PROCESS ", "
                                              LOGS_PROBLEM " ) "
                                              "VALUES (:Name, :Date, :Time, :Type, :Description, :Process, :Problem )");
    query.bindValue(":Name",        "FirstConnection");
    query.bindValue(":Date",        QDate::currentDate());
    query.bindValue(":Time",        QTime::currentTime());
    query.bindValue(":Type",        "0");
    query.bindValue(":Description",    "SQL created");
    query.bindValue(":Process",        "SQL");
    query.bindValue(":Problem",        "No problem");
    // После чего выполняется запросом методом exec()
    if(query.exec())
    {
        return true;
    } else {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }


    return false;
}




/* Creat tables in time of experiments
 * TableExperimentsOf
 * TableSelectedExperimentsOf
 * TableDevicesOf
 * TableExperimentNumber
*/

bool DataBase::createNewTableExperimentsOf(const QVariantList &table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE :Table ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Experiment_name VARCHAR(255) NOT NULL )");

    query.bindValue(":Table", table[0].toString());

    if(query.exec())
    {
        return true;
    } else {
        qDebug() << "DataBase: error of create " << table[0].toString();
        qDebug() << query.lastError().text();
        return false;
    }

}

bool DataBase::createNewTableSelectedExperimentsOf(const QVariantList &table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE :Table ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Experiment_name VARCHAR(255) NOT NULL )");

    query.bindValue(":Table", table[0].toString());

    if(query.exec())
    {
        return true;
    } else {
        qDebug() << "DataBase: error of create " << table[0].toString();
        qDebug() << query.lastError().text();
        return false;
    }

}

bool DataBase::createNewTableDevicesOf(const QVariantList &table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE :Table ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Device_name VARCHAR(255) NOT NULL )");

    query.bindValue(":Table", table[0].toString());

    if(query.exec())
    {
        return true;
    } else {
        qDebug() << "DataBase: error of create " << table[0].toString();
        qDebug() << query.lastError().text();
        return false;
    }

}

bool DataBase::createNewTableExperimentNumber(const QVariantList &table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE :Table ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "ExperimentNumber VARCHAR(255) NOT NULL )");

    query.bindValue(":Table", table[0].toString());

    if(query.exec())
    {
        return true;
    } else {
        qDebug() << "DataBase: error of create " << table[0].toString();
        qDebug() << query.lastError().text();
        return false;
    }

}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_RANDOM ", "
                                             TABLE_MESSAGE " ) "
                  "VALUES (:Date, :Time, :Random, :Message )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Random",      data[2].toInt());
    query.bindValue(":Message",     data[3].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}



bool DataBase::inserIntoNewTableExperimentsOf(const QVariantList &ndata)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO :Table ( Experiment_name ) "
                  "VALUES (:Data )");

    query.bindValue(":Table", ndata[0].toString());
    query.bindValue(":Data", ndata[1].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << ndata[0].toString();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoNewTableSelectedExperimentsOf(const QVariantList &ndata)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO :Table ( Experiment_name ) "
                  "VALUES (:Data )");

    query.bindValue(":Table", ndata[0].toString());
    query.bindValue(":Data", ndata[1].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << ndata[0].toString();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoNewTableDevicesOf(const QVariantList &ndata)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO :Table ( Device_name ) "
                  "VALUES (:Data )");

    query.bindValue(":Table", ndata[0].toString());
    query.bindValue(":Data", ndata[1].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << ndata[0].toString();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoNewTableExperimentNumber(const QVariantList &ndata)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO :Table ( ExperimentNumber ) "
                  "VALUES (:Data )");

    query.bindValue(":Table", ndata[0].toString());
    query.bindValue(":Data", ndata[1].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << ndata[0].toString();
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}










