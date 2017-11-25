#include "authorization.h"
#include <QtWidgets>
#include <QMainWindow>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QWidget(parent)
    //QWidget(0, Qt::Window | Qt::FramelessWindowHint)

{
    tableView_new = new QTableView();





    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    for(int i = 0; i < 20; i++){
        QVariantList data;
        int random = qrand(); // Получаем случайные целые числа для вставки а базу данных
        data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
        data.append(QTime::currentTime()); // Получаем текущее время для вставки в БД
        // Подготавливаем полученное случайное число для вставки в БД
        data.append(random);
        // Подготавливаем сообщение для вставки в базу данных
        data.append("Получено сообщение от " + QString::number(random));
        // Вставляем данные в БД
        db->inserIntoTable(data);
    }

    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Дата")
                                   << trUtf8("Время")
                                   << trUtf8("Рандомное число")
                                   << trUtf8("Сообщение")
               );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();


    QGridLayout *grid = new QGridLayout;
    grid->addWidget(tableView_new, 0, 0, model->rowCount(), model->columnCount());
    setLayout(grid);

    //tableView_new->horizontalHeader()->setSectionResizeMode(1,QHeaderView::);
    tableView_new->setColumnWidth(1,100);
    tableView_new->setColumnWidth(2,100);



    setWindowTitle(tr("Authorization"));
        resize(480, 220);

}

/*AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}*/

/* Метод для инициализации модеи представления данных
 * */
void AuthorizationWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void AuthorizationWindow::createUI()
{
    tableView_new->setModel(model);     // Устанавливаем модель на TableView
    tableView_new->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    tableView_new->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    tableView_new->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    tableView_new->resizeColumnsToContents();
    tableView_new->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView_new->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы
}
