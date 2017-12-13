#include "dialogauth.h"
#include <QtWidgets>
#include <QMainWindow>

DialogAuth::DialogAuth(int row, QWidget *parent) :
    QDialog(parent)
{
    //ui->setupUi(this);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(groupTableAuth(), 0, 0);
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

     //createUI();
 }

 DialogAuth::~DialogAuth()
 {
     //delete ui;
 }

 /* Метод настройки модели данных и mapper
  * */
 void DialogAuth::setupModel()
 {
     /* Инициализируем модель и делаем выборку из неё
      * */
     model = new QSqlTableModel(this);
     model->setTable(SCIENTISTS);
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
     /* При изменении индекса в mapper изменяем состояние кнопок
      * */
     connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
 }

 /* Метод для установки валидатора на поле ввода IP и MAC адресов
  * */
 void DialogAuth::createUI()
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

 void DialogAuth::on_buttonBox_accepted()
 {
     /* SQL-запрос для проверки существования записи
      * с такими же учетными данными.
      * Если запись не существует или находится лишь индекс
      * редактируемой в данный момент записи,
      * то диалог позволяет вставку записи в таблицу данных
      * */
     QSqlQuery query;
     QString str = QString("SELECT EXISTS (SELECT " SCIENTISTS_LOGIN " FROM " SCIENTISTS
                           " WHERE ( " SCIENTISTS_LOGIN " = '%1' )"
                           " AND id NOT LIKE '%2' )")
             .arg(HostnameLineEdit->text(),
                  //IPAddressLineEdit->text(),
                  model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

     query.prepare(str);
     query.exec();
     query.next();

     /* Если запись существует, то диалог вызывает
      * предупредительное сообщение
      * */
     if(query.value(0) != 0){
         QMessageBox::information(this, trUtf8("Ошибка"),
                                  trUtf8("уже существует"));
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

 void DialogAuth::accept()
 {

 }

 /* Метод изменения состояния активности кнопок пролистывания
  * */
 void DialogAuth::updateButtons(int row)
 {
     /* В том случае, если мы достигаем одного из крайних (самый первый или
      * самый последний) из индексов в таблице данных,
      * то мы изменяем состояние соответствующей кнопки на
      * состояние неактивна
      * */
     previousButton->setEnabled(row > 0);
     nextButton->setEnabled(row < model->rowCount() - 1);
 }


 QGroupBox *DialogAuth::groupTableAuth()
 {
     QGroupBox *groupBox = new QGroupBox(tr(""));
     groupBox->setStyleSheet("border: 0px solid white");

     previousButton = new QPushButton(tr("Previous"));
     nextButton = new QPushButton(tr("Next"));
     HostnameLineEdit = new QLineEdit();
     IPAddressLineEdit = new QLineEdit();
     MACLineEdit = new QLineEdit();

     /*label_1 = new QLabel(tr(" LAMP "));
     label_1->setFont(QFont("Russo One",100));
     label_1->setStyleSheet("color: gray;");

     label_2 = new QLabel(tr("         Laboratory for Advanced Materials Physics\n "));
     label_2->setFont(QFont("Russo One",13));
     label_2->setStyleSheet("color: gray;");*/

     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addWidget(HostnameLineEdit);
     vbox->addWidget(IPAddressLineEdit);
     vbox->addWidget(MACLineEdit);
     vbox->setMargin(0);
     groupBox->setLayout(vbox);

     return groupBox;
 }
