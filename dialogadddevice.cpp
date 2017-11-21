#include <QtWidgets>
#include <QSql>
#include <QDebug>

#include "dialogadddevice.h"

DialogAddDevice::DialogAddDevice(int row, QWidget *parent) :
    QDialog(parent)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(groupDevice(), 0, 0);
    setLayout(grid);



    /* Метода для инициализации модели,
     * из которой будут транслироваться данные
     * */
    setupModel();

    /* Если строка не задана, то есть равна -1,
     * тогда диалог работает по принципу создания новой записи.
     * А именно, в модель вставляется новая строка и работа ведётся с ней.
     * */
    if(row == -1){
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    /* В противном случае диалог настраивается на заданную запись
     * */
    } else {
        mapper->setCurrentModelIndex(model->index(row,0));
    }

    createUI();
}

DialogAddDevice::~DialogAddDevice()
{

}

/* Метод настройки модели данных и mapper
 * */
void DialogAddDevice::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
     * */
    model = new QSqlTableModel(this);
    model->setTable(DEVICE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /* Инициализируем mapper и привязываем
     * поля данных к объектам LineEdit
     * */
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(HostnameLineEdit, 1);
    mapper->addMapping(IPAddressLineEdit, 2);
    mapper->addMapping(MACLineEdit, 3);
    /* Ручное подтверждение изменения данных
     * через mapper
     * */
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    /* Подключаем коннекты от кнопок пролистывания
     * к прилистыванию модели данных в mapper
     * */
    connect(previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(okbuttonBox()));
    /* При изменении индекса в mapper изменяем состояние кнопок
     * */
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

/* Метод для установки валидатора на поле ввода IP и MAC адресов
 * */
void DialogAddDevice::createUI()
{
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    IPAddressLineEdit->setValidator(ipValidator);

    QString macRange = "(?:[0-9A-Fa-f][0-9A-Fa-f])";
    QRegExp macRegex ("^" + macRange
                      + "\\:" + macRange
                      + "\\:" + macRange
                      + "\\:" + macRange
                      + "\\:" + macRange
                      + "\\:" + macRange + "$");
    QRegExpValidator *macValidator = new QRegExpValidator(macRegex, this);
    MACLineEdit->setValidator(macValidator);
}

void DialogAddDevice::on_buttonBox_accepted()
{
    /* SQL-запрос для проверки существования записи
     * с такими же учетными данными.
     * Если запись не существует или находится лишь индекс
     * редактируемой в данный момент записи,
     * то диалог позволяет вставку записи в таблицу данных
     * */
    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " DEVICE_HOSTNAME " FROM " DEVICE
                          " WHERE ( " DEVICE_HOSTNAME " = '%1' "
                          " OR " DEVICE_IP " = '%2' )"
                          " AND id NOT LIKE '%3' )")
            .arg(HostnameLineEdit->text(),
                 IPAddressLineEdit->text(),
                 model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

    query.prepare(str);
    query.exec();
    query.next();

    /* Если запись существует, то диалог вызывает
     * предупредительное сообщение
     * */
    if(query.value(0) != 0){
        QMessageBox::information(this, trUtf8("Ошибка хоста"),
                                 trUtf8("Хост с таким именем или IP-адресом уже существует"));
    /* В противном случае производится вставка новых данных в таблицу
     * и диалог завершается с передачей сигнала для обновления
     * таблицы в главном окне
     * */
    } else {
        mapper->submit();
        model->submitAll();
        emit signalReady();
        this->close();
    }
}

void DialogAddDevice::okbuttonBox()
{
    /* SQL-запрос для проверки существования записи
     * с такими же учетными данными.
     * Если запись не существует или находится лишь индекс
     * редактируемой в данный момент записи,
     * то диалог позволяет вставку записи в таблицу данных
     * */
    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " DEVICE_HOSTNAME " FROM " DEVICE
                          " WHERE ( " DEVICE_HOSTNAME " = '%1' "
                          " OR " DEVICE_IP " = '%2' )"
                          " AND id NOT LIKE '%3' )")
            .arg(HostnameLineEdit->text(),
                 IPAddressLineEdit->text(),
                 model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

    query.prepare(str);
    query.exec();
    query.next();

    /* Если запись существует, то диалог вызывает
     * предупредительное сообщение
     * */
    if(query.value(0) != 0){
        QMessageBox::information(this, trUtf8("Ошибка хоста"),
                                 trUtf8("Хост с таким именем или IP-адресом уже существует"));
    /* В противном случае производится вставка новых данных в таблицу
     * и диалог завершается с передачей сигнала для обновления
     * таблицы в главном окне
     * */
    } else {
        mapper->submit();
        model->submitAll();
        emit signalReady();
        this->close();
    }
}


void DialogAddDevice::accept()
{
qDebug() << HostnameLineEdit->text();
}

/* Метод изменения состояния активности кнопок пролистывания
 * */
void DialogAddDevice::updateButtons(int row)
{
    /* В том случае, если мы достигаем одного из крайних (самый первый или
     * самый последний) из индексов в таблице данных,
     * то мы изменяем состояние соответствующей кнопки на
     * состояние неактивна
     * */
    previousButton->setEnabled(row > 0);
    nextButton->setEnabled(row < model->rowCount() - 1);
}

QGroupBox *DialogAddDevice::groupDevice()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
        QGridLayout * gridLayout = new QGridLayout();



        HostnameLineEdit = new QLineEdit(tr("HostnameLineEdit"));
        IPAddressLineEdit  = new QLineEdit(tr("IPAddressLineEdit"));
        MACLineEdit  = new QLineEdit(tr("MACLineEdit"));
        previousButton = new QPushButton(tr("previousButton"));
        nextButton  = new QPushButton(tr("nextButton"));
        okButton = new QPushButton(tr("Okey"));
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);


        gridLayout->addWidget(HostnameLineEdit,0,0);
        gridLayout->addWidget(IPAddressLineEdit,1,0);
        gridLayout->addWidget(MACLineEdit,2,0);
        gridLayout->addWidget(previousButton,3,0);
        gridLayout->addWidget(nextButton,3,1);
        gridLayout->addWidget(okButton,3,2);
        gridLayout->addWidget(buttonBox,4,0);
        groupBox->setLayout(gridLayout);
    return groupBox;
}


