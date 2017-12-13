#include "authorization.h"
#include <QtWidgets>
#include <QMainWindow>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    //QWidget(parent)
    QWidget(0, Qt::Window | Qt::FramelessWindowHint)

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
    /*for(int i = 0; i < 20; i++){
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
    }*/

    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(SCIENTISTS,
                        QStringList()
                        << trUtf8("ID")
                        << trUtf8("Name")
                        << trUtf8("Surname")
                        << trUtf8("Login")
                        << trUtf8("Date")
                        << trUtf8("Parent")
                        << trUtf8("Pass")
                        << trUtf8("Email")
                        << trUtf8("Сообщение")
                        << trUtf8("Telegram")
                        << trUtf8("Phone")
                        << trUtf8("Experiments")
                        << trUtf8("Selected_experiments")
                        << trUtf8("BirthDay")
                        << trUtf8("Position")
                        << trUtf8("Theme")
               );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();


    QGridLayout *grid = new QGridLayout;
    grid->addWidget(tableView_new, 0, 0, model->rowCount(), model->columnCount());
    setLayout(grid);

    //tableView_new->horizontalHeader()->setSectionResizeMode(1,QHeaderView::);
    tableView_new->setColumnWidth(1,120);
    tableView_new->setColumnWidth(3,120);
    tableView_new->setColumnWidth(4,120);



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
    tableView_new->setColumnHidden(0, true);
    tableView_new->setColumnHidden(1, false);    // Скрываем колонку с id записей
    tableView_new->setColumnHidden(2, true);
    tableView_new->setColumnHidden(3, false);
    tableView_new->setColumnHidden(4, true);
    tableView_new->setColumnHidden(5, true);
    tableView_new->setColumnHidden(6, true);
    tableView_new->setColumnHidden(7, true);
    tableView_new->setColumnHidden(8, true);
    tableView_new->setColumnHidden(9, true);
    tableView_new->setColumnHidden(10, true);
    tableView_new->setColumnHidden(11, true);
    tableView_new->setColumnHidden(12, true);
    tableView_new->setColumnHidden(13, true);
    tableView_new->setColumnHidden(14, false);
    tableView_new->setColumnHidden(15, true);


    // Разрешаем выделение строк
    tableView_new->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    tableView_new->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    tableView_new->resizeColumnsToContents();
    tableView_new->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView_new->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы

    connect(tableView_new, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));

}

/* Метод для активации диалога добавления записей
 * */
void AuthorizationWindow::on_addDeviceButton_clicked()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    DialogAuth *addDialogAuth = new DialogAuth();
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogAuth->setWindowTitle(trUtf8("Добавить Устройство"));
    addDialogAuth->exec();
}

void AuthorizationWindow::slotUpdateModels()
{
    model->select();
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void AuthorizationWindow::slotEditRecord(QModelIndex index)
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    DialogAuth *addDialogAuth = new DialogAuth(index.row());
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModel()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogAuth->setWindowTitle(trUtf8("Редактировать Устройство"));
    addDialogAuth->exec();
}

