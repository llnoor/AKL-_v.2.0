#include "mainwindow_test.h"
#include "ui_mainwindow_test.h"

MainWindow_T::MainWindow_T(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QDataWidgetMapper Example");
    /* Первым делом необходимо создать объект для работы с базой данных
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* Инициализируем модели для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(DEVICE,
                     QStringList() << trUtf8("id")
                                         << trUtf8("Имя хоста")
                                         << trUtf8("IP адрес")
                                         << trUtf8("MAC-адрес")
               );
    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();
}

MainWindow_T::~MainWindow_T()
{
    delete ui;
}

void MainWindow_T::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * */
    modelDevice = new QSqlTableModel(this);
    modelDevice->setTable(tableName);
    modelDevice->select();
    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < modelDevice->columnCount(); i++, j++){
        modelDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void MainWindow_T::createUI()
{
    ui->deviceTableView->setModel(modelDevice);     // Устанавливаем модель на TableView
    ui->deviceTableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->deviceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->deviceTableView->resizeColumnsToContents();
    ui->deviceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->deviceTableView->horizontalHeader()->setStretchLastSection(true);

    connect(ui->deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
}

/* Метод для активации диалога добавления записей
 * */
void MainWindow_T::on_addDeviceButton_clicked()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    DialogAddDevice *addDeviceDialog = new DialogAddDevice();
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDeviceDialog->setWindowTitle(trUtf8("Добавить Устройство"));
    addDeviceDialog->exec();
}

/* Слот обновления модели представления данных
 * */
void MainWindow_T::slotUpdateModels()
{
    modelDevice->select();
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void MainWindow_T::slotEditRecord(QModelIndex index)
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    DialogAddDevice *addDeviceDialog = new DialogAddDevice(index.row());
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDeviceDialog->setWindowTitle(trUtf8("Редактировать Устройство"));
    addDeviceDialog->exec();
}
