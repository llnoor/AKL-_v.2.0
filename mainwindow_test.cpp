#include <QtWidgets>
#include <QSql>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QDialog>


#include "mainwindow_test.h"

MainWindow_Test::MainWindow_Test(): QWidget(0)
{

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(groupTest(), 0, 0);
    setLayout(grid);

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


void MainWindow_Test::setupModel(const QString &tableName, const QStringList &headers)
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

void MainWindow_Test::createUI()
{
    deviceTableView->setModel(modelDevice);     // Устанавливаем модель на TableView
    deviceTableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    deviceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    deviceTableView->resizeColumnsToContents();
    deviceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    deviceTableView->horizontalHeader()->setStretchLastSection(true);

    //connect(addDeviceButton,SIGNAL(relised()),this,SLOT(on_addDeviceButton_clicked()));
    connect(deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
}

/* Метод для активации диалога добавления записей
 * */
void MainWindow_Test::on_addDeviceButton_clicked()
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
void MainWindow_Test::slotUpdateModels()
{
    modelDevice->select();
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void MainWindow_Test::slotEditRecord(QModelIndex index)
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

QGroupBox *MainWindow_Test::groupTest()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
        QGridLayout * gridLayout = new QGridLayout();

        label = new QLabel(tr("Table"));
        addDeviceButton = new QPushButton(tr("Submit"));
        editDeviceButton = new QPushButton(tr("Edit"));
        selectDeviceButton = new QPushButton(tr("Select"));
        deviceTableView = new QTableView();


        gridLayout->addWidget(label,0,0);
        gridLayout->addWidget(addDeviceButton,0,1);
        gridLayout->addWidget(deviceTableView,1,0);
        groupBox->setLayout(gridLayout);
    return groupBox;
}
