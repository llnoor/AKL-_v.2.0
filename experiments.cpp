#include "experiments.h"
#include <QtWidgets>
#include <QMainWindow>

Experiments::Experiments(QWidget *parent):
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


    this->setupModel(EXPERIMENTS,
                        QStringList()
                        << trUtf8("ID")
                        << trUtf8("Name")
                        << trUtf8("Description")
                        << trUtf8("Author")
                        << trUtf8("Date")
                        << trUtf8("Devices")
                        << trUtf8("Parent")
                        << trUtf8("Link")
                        << trUtf8("Conf")
               );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();

    //newuserButton = new QPushButton(tr("New"));
    newuserButton = new QPushButton(tr("New user"));
    //edituserButton = new QPushButton(tr("Edit"));


    QGridLayout *grid = new QGridLayout;
    //grid->addWidget(groupTable());
    grid->addWidget(tableView_new, 0, 0, model->rowCount(), model->columnCount());
    grid->addWidget(newuserButton);
    //grid->addWidget(edituserButton);
    //grid->addWidget(groupTable(),  model->rowCount()+1, 0);
    setLayout(grid);

    //tableView_new->horizontalHeader()->setSectionResizeMode(1,QHeaderView::);
    tableView_new->setColumnWidth(1,120);
    tableView_new->setColumnWidth(2,120);
    tableView_new->setColumnWidth(3,120);
    tableView_new->setColumnWidth(13,100);



    setWindowTitle(tr("Authorization"));
        resize(550, 420);
        //this->setFont(QFont("Ubuntu"));//Roboto
        //this->setFont(QFont("Roboto",16,0,1));

    connect(newuserButton, SIGNAL(released()), this, SLOT(slotNewUser()));
    //connect(edituserButton, SIGNAL(released()), this, SLOT(slotEditUser()));

}



/*Experiments::~Experiments()
{
    delete ui;
}*/

/* Метод для инициализации модеи представления данных
 * */
void Experiments::setupModel(const QString &tableName, const QStringList &headers)
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

void Experiments::createUI()
{
    tableView_new->setModel(model);     // Устанавливаем модель на TableView
    tableView_new->setColumnHidden(0, false);    // Скрываем колонку с id записей
    tableView_new->setColumnHidden(1, false);
    tableView_new->setColumnHidden(2, false);
    tableView_new->setColumnHidden(3, false);
    tableView_new->setColumnHidden(4, false);
    tableView_new->setColumnHidden(5, false);
    tableView_new->setColumnHidden(6, false);
    tableView_new->setColumnHidden(7, false);


    // Разрешаем выделение строк
    tableView_new->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    tableView_new->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    tableView_new->resizeColumnsToContents();
    tableView_new->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView_new->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы

    connect(tableView_new, SIGNAL(clicked(QModelIndex)), this, SLOT(slotLogin(QModelIndex)));
    connect(tableView_new, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditUser(QModelIndex)));

}

/* Метод для активации диалога добавления записей
 * */
/*void Experiments::on_addDeviceButton_clicked()
{

    DialogAuth *addDialogAuth = new DialogAuth();
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    addDialogAuth->setWindowTitle(trUtf8("Добавить"));
    addDialogAuth->exec();
}*/

void Experiments::slotNewUser()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    DialogReg *addDialogReg = new DialogReg();
    connect(addDialogReg, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogReg->setWindowTitle(trUtf8("Add User"));
    addDialogReg->exec();
    //showlogoWindow();
}


void Experiments::slotEditUser(QModelIndex index)
{


    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */


    DialogReg *addDialogReg = new DialogReg(index.row());
    connect(addDialogReg, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogReg->setWindowTitle(trUtf8("Edit"));
    addDialogReg->exec();
}


void Experiments::slotUpdateModels()
{
    model->select();
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void Experiments::slotLogin(QModelIndex index)
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    DialogAuth *addDialogAuth = new DialogAuth(index.row());
    connect(addDialogAuth, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    connect(addDialogAuth, SIGNAL(accepted()),this, SIGNAL(showlogoWindow()));

    /* Выполняем запуск диалогового окна
     * */
    addDialogAuth->setWindowTitle(trUtf8("Authorization"));
    addDialogAuth->exec();

    /*if(addDialogAuth->exec()){
        QMessageBox::information(this, trUtf8("Check"),
                                 trUtf8("True"));

    } else {
        QMessageBox::information(this, trUtf8("Check"),
                                 trUtf8("False"));
    }*/

}


QGroupBox *Experiments::groupTable()
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
