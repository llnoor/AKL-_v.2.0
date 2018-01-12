#include "authorization.h"
#include <QtWidgets>
#include <QMainWindow>

AuthorizationWindow::AuthorizationWindow(QWidget *parent):
    //QWidget(parent)
    QWidget(0, Qt::Window | Qt::FramelessWindowHint)

{
    tableView_new = new QTableView();

    //emit



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
                        << trUtf8("Telegram")
                        << trUtf8("Phone")
                        << trUtf8("Experiments")
                        << trUtf8("Selected_experiments")
                        << trUtf8("BirthDay")
                        << trUtf8("Position")
                        << trUtf8("Edit")
               );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();

    //newuserButton = new QPushButton(tr("New"));
    newuserButton = new QPushButton(tr("New user"));
    edituserButton = new QPushButton(tr("Edit"));


    QGridLayout *grid = new QGridLayout;
    //grid->addWidget(groupTable());
    grid->addWidget(tableView_new, 0, 0, model->rowCount(), model->columnCount());
    grid->addWidget(newuserButton);
    grid->addWidget(edituserButton);
    //grid->addWidget(groupTable(),  model->rowCount()+1, 0);
    setLayout(grid);

    //tableView_new->horizontalHeader()->setSectionResizeMode(1,QHeaderView::);
    tableView_new->setColumnWidth(1,120);
    tableView_new->setColumnWidth(2,120);
    tableView_new->setColumnWidth(3,120);
    tableView_new->setColumnWidth(13,100);
    tableView_new->setColumnWidth(14,40);



    setWindowTitle(tr("Authorization"));
        resize(600, 420);

    connect(newuserButton, SIGNAL(released()), this, SLOT(slotNewUser()));
    connect(edituserButton, SIGNAL(released()), this, SLOT(slotEditUser()));

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
    tableView_new->setColumnHidden(1, false);
    tableView_new->setColumnHidden(2, false);
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
    tableView_new->setColumnHidden(13, false);
    tableView_new->setColumnHidden(14, false); //for tableButton


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

    signalMapper = new QSignalMapper();

    for (int row = 0; row < model->rowCount() /*model->columnCount()*/; ++row) {
        tableButton= new QPushButton("Edit");
        tableView_new->setIndexWidget(tableView_new->model()->index(row, 14), tableButton);
        signalMapper->setMapping(tableButton, row);

    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(slotEdit2User(int)));
}

/* Метод для активации диалога добавления записей
 * */
/*void AuthorizationWindow::on_addDeviceButton_clicked()
{

    DialogAuth *addDialogAuth = new DialogAuth();
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    addDialogAuth->setWindowTitle(trUtf8("Добавить"));
    addDialogAuth->exec();
}*/

void AuthorizationWindow::slotNewUser()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    DialogReg *addDialogReg = new DialogReg();
    connect(addDialogReg, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogReg->setWindowTitle(trUtf8("Добавить"));
    addDialogReg->exec();
}

void AuthorizationWindow::slotEditUser()
{


    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */


    DialogReg *addDialogReg = new DialogReg(model->data(tableView_new->currentIndex()).toInt());
    connect(addDialogReg, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogReg->setWindowTitle(trUtf8("Редактировать"));
    addDialogReg->exec();
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
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogAuth->setWindowTitle(trUtf8("Редактировать"));
    addDialogAuth->exec();

    /*if(addDialogAuth->exec()){
        QMessageBox::information(this, trUtf8("Ошибка1"),
                                 trUtf8("уже существует1"));

    } else {
        QMessageBox::information(this, trUtf8("Ошибка2"),
                                 trUtf8("уже существует2"));
    }*/

}


QGroupBox *AuthorizationWindow::groupTable()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));

    //newuserButton = new QPushButton(tr("New user"));
    //edituserButton = new QPushButton(tr("Edit"));

    QVBoxLayout *vbox = new QVBoxLayout;
    //vbox->addWidget(newuserButton,0);
    //vbox->addWidget(edituserButton,1);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setMargin(0);
    groupBox->setLayout(vbox);

    return groupBox;
}
