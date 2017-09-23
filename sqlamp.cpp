#include "sqlamp.h"
#include "initdb.h"

#include <QtSql>

SQLamp::SQLamp()
{

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, "Unable to load database", "This program needs the SQLITE driver");

    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }




}


