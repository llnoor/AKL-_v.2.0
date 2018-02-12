#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qgroupbox.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qwhatsthis.h>
#include <qpixmap.h>


#include "lamphdevices.h"
#include "start.xpm"
#include "clear.xpm"
#include "pixmaps.h"

#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QComboBox>

#include <QDebug>
#include <QLibrary>

class MyToolBar: public QToolBar
{
public:
    MyToolBar( LAMPhDevices *parent ):
        QToolBar( parent )
    {
    }
    void addSpacing( int spacing )
    {
        QLabel *label = new QLabel( this );
        addWidget( label );
        label->setFixedWidth( spacing );
    }
};

LAMPhDevices::LAMPhDevices(QString loginQString)
{

    addToolBar(Qt::TopToolBarArea, toolBar());

    addToolBar(Qt::LeftToolBarArea, toolBar_GET());
    /*addToolBar(Qt::LeftToolBarArea, toolBar_SEND());
    addToolBar(Qt::LeftToolBarArea, toolBar_COUNTERS());

    addToolBar(Qt::RightToolBarArea, toolBar_PORTS());
    addToolBar(Qt::RightToolBarArea, toolBar_DEVICES());*/

#ifndef QT_NO_STATUSBAR
    ( void )statusBar();
#endif


    login = new QString();
    *login = loginQString;

    labelPlotSettingS = new QLabel(tr(" "));


    /*QLabel       lbl("this is the example text");
    QLibrary     lib("dynlibd");

    typedef QString (*Fct) (const QString&);
    Fct fct = (Fct)(lib.resolve("oddUpper"));
    if (fct) {
        labelPlotSettingS->setText("fct(lbl.text())");
    }*/


    setCentralWidget( labelPlotSettingS );

    getDataDll();
    //initWhatsThis();

    setContextMenuPolicy( Qt::NoContextMenu );



    connect( d_OpenWindow_Main, SIGNAL( triggered() ), this, SIGNAL(showLAMPhPlot()) );
    connect( d_OpenWindow_Main, SIGNAL( triggered() ), this, SLOT(close()) );
    connect( d_OpenWindow_Devices, SIGNAL( triggered() ), this, SIGNAL(showLAMPhDevices()) );
    connect( d_OpenWindow_Devices, SIGNAL( triggered() ), this, SLOT(close()) );
    //connect( d_OpenWindow_Temp, SIGNAL( triggered() ), this, SIGNAL(showLAMPhTemp()) );
    //connect( d_OpenWindow_Temp, SIGNAL( triggered() ), this, SLOT(close()) );
    connect( d_OpenWindow_DataTable, SIGNAL( triggered() ), this, SIGNAL(showDataTable()) );
    connect( d_OpenWindow_DataTable, SIGNAL( triggered() ), this, SLOT(close()) );
    connect( d_OpenWindow_Edit, SIGNAL( triggered() ), this, SIGNAL(showLAMPhEdit()) );
    connect( d_OpenWindow_Edit, SIGNAL( triggered() ), this, SLOT(close()) );
    connect( d_OpenWindow_Setting, SIGNAL( triggered() ), this, SIGNAL(showLAMPhSetting()) );
    connect( d_OpenWindow_Setting, SIGNAL( triggered() ), this, SLOT(close()) );

    //connect( d_OpenWindow_Exit, SIGNAL( triggered() ), this, SIGNAL(LAMPhExit()) );
    //connect( d_OpenWindow_Exit, SIGNAL( triggered() ), this, SLOT(close()) );

    setWindowTitle(tr("LAMPhDevices - %1 ").arg(login->toLower()));
    //showFullScreen();
    showMaximized();
    //this->setWindowState(Qt::WindowMaximized);

}

QToolBar *LAMPhDevices::toolBar()
{
    MyToolBar *toolBar = new MyToolBar( this );

    toolBar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

    d_connectAction = new QAction( QPixmap( start_xpm ), "Connect", toolBar );
    d_sendAction = new QAction( QPixmap( clear_xpm ), "Send/Set", toolBar );

    d_getAction = new QAction( QPixmap( zoom_xpm ), "Get/Test", toolBar );


    QAction *whatsThisAction = QWhatsThis::createAction( toolBar );
    whatsThisAction->setText( "Help" );

    toolBar->addAction( d_connectAction );
    toolBar->addAction( d_sendAction );
    toolBar->addAction( d_getAction );
    toolBar->addAction( whatsThisAction );
    toolBar->addSeparator();

    setIconSize( QSize( 22, 22 ) );

    QWidget *hBox = new QWidget( toolBar );

    //d_symbolType = new QCheckBox( "Symbols", hBox );
    //d_symbolType->setChecked( true );

    QHBoxLayout *layout = new QHBoxLayout( hBox );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );
    layout->addSpacing( 10 );
    layout->addWidget( new QWidget( hBox ), 10 ); // spacer
    //layout->addWidget( d_symbolType );
    layout->addSpacing( 5 );

    toolBar->addWidget( hBox );

    d_OpenWindow_Main = new QAction( QPixmap( start_xpm ), "Main Plot", toolBar );
    d_OpenWindow_Devices = new QAction( QPixmap( start_xpm ), "Devices", toolBar );
    d_OpenWindow_Temp = new QAction( QPixmap( start_xpm ), "Temp", toolBar );
    d_OpenWindow_DataTable = new QAction( QPixmap( start_xpm ), "DataTable", toolBar );
    d_OpenWindow_Edit = new QAction( QPixmap( start_xpm ), "Edit", toolBar );
    d_OpenWindow_Setting = new QAction( QPixmap( start_xpm ), "Setting", toolBar );
    d_OpenWindow_Exit = new QAction( QPixmap( start_xpm ), "Exit", toolBar );
    d_OpenWindow_Devices->setEnabled(false);
    d_OpenWindow_Exit->setEnabled(false);


    toolBar->addSeparator();

    toolBar->addAction( d_OpenWindow_Main );
    toolBar->addAction( d_OpenWindow_Devices );
    toolBar->addAction( d_OpenWindow_Temp );
    toolBar->addAction( d_OpenWindow_DataTable );
    toolBar->addAction( d_OpenWindow_Edit );
    toolBar->addAction( d_OpenWindow_Setting );
    toolBar->addAction( d_OpenWindow_Exit );

    return toolBar;
}


QToolBar *LAMPhDevices::toolBar_GET()
{
    MyToolBar *toolBar_GET = new MyToolBar( this );
    toolBar_GET->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hBox_GET = new QWidget( toolBar_GET );


    label_label_ReceivedData = new QLabel(tr("DATA"));
    label_comboBox_Device = new QLabel(tr("Devices"));
    label_comboBox_Device_Functions = new QLabel(tr("Functions"));
    label_comboBox_Function_Parameters = new QLabel(tr("Parameters"));
    label_lineEdit_NameData = new QLabel(tr("Name"));
    label_checkBox_Device_Show = new QLabel(tr("Plot"));
    label_checkBox_Device_Text = new QLabel(tr("Text"));
    label_checkBox_Device_DB = new QLabel(tr("DB"));
    label_comboBox_ColorData = new QLabel(tr("Color"));
    label_comboBox_SizeData = new QLabel(tr("Size"));

    for(int i=0; i<20; i++)
    {
        label_ReceivedData[i] = new QLabel();
        label_ReceivedData[i]->setText(QString("DATA %1:").arg(i));
        comboBox_Device[i] = new QComboBox();
        comboBox_Device_Functions[i] = new QComboBox();
        comboBox_Function_Parameters[i] = new QComboBox();
        lineEdit_NameData[i] = new QLineEdit();
        lineEdit_NameData[i]->setText(QString("Name %1:").arg(i));
        //lineEdit_NameData[i]->setFixedWidth(60);
        checkBox_Device_Show[i]  = new QCheckBox(tr(""));
        checkBox_Device_Text[i]  = new QCheckBox(tr(""));
        checkBox_Device_DB[i]  = new QCheckBox(tr(""));
        comboBox_ColorData[i] = new QComboBox();
        comboBox_SizeData[i] = new QComboBox();



        for (int l = 0; l < 5; ++l) {
            comboBox_Device[i]->addItem(QString("Item %1").arg(l));
            comboBox_Device_Functions[i]->addItem(QString("Item %1").arg(l));
            comboBox_Function_Parameters[i]->addItem(QString("Item %1").arg(l));
            comboBox_ColorData[i]->addItem(QString("Item %1").arg(l));
            comboBox_SizeData[i]->addItem(QString("Item %1").arg(l));
        }
        /*read list of devices name from file one by one and add as Item
         *new void function update_comboBox_Device_Functions()
         * {
         *  open file (nameofDevice.dll)
         *  get list of funtion named like "get*"
         *  add function as Item
         * }
         * */

        //SAVE PARAMETERS OF TOOLBARS
    }

    int_GET=7;

    for(int i=int_GET; i<20; i++)
    {
        label_ReceivedData[i]->hide();
        comboBox_Device[i]->hide();
        comboBox_Device_Functions[i]->hide();
        comboBox_Function_Parameters[i]->hide();
        lineEdit_NameData[i]->hide();
        checkBox_Device_Show[i]->hide();
        checkBox_Device_Text[i]->hide();
        checkBox_Device_DB[i]->hide();
        comboBox_ColorData[i]->hide();
        comboBox_SizeData[i]->hide();
    }

    button_ReceivedData_Close = new QPushButton(tr("Close"));
    button_ReceivedData_Add = new QPushButton(tr("Add"));
    connect(button_ReceivedData_Close,SIGNAL(released()), this, SLOT(toolBar_GET_hide_data())   );
    connect(button_ReceivedData_Add,SIGNAL(released()), this, SLOT(toolBar_GET_show_data()));

    QGridLayout *gridLayout = new QGridLayout( hBox_GET);

    gridLayout->addWidget(label_label_ReceivedData, 0, 0);
    gridLayout->addWidget(label_comboBox_Device, 0, 1);
    gridLayout->addWidget(label_comboBox_Device_Functions, 0, 2);
    gridLayout->addWidget(label_comboBox_Function_Parameters, 0, 3);
    gridLayout->addWidget(label_lineEdit_NameData, 0, 4);
    gridLayout->addWidget(label_checkBox_Device_Show, 0, 5);
    gridLayout->addWidget(label_checkBox_Device_Text, 0, 6);
    gridLayout->addWidget(label_checkBox_Device_DB, 0, 7);
    gridLayout->addWidget(label_comboBox_ColorData, 0, 8);
    gridLayout->addWidget(label_comboBox_SizeData, 0, 9);

    for(int i=0; i<20; i++)
    {
        gridLayout->addWidget(label_ReceivedData[i], i+1, 0);
        gridLayout->addWidget(comboBox_Device[i], i+1, 1);
        gridLayout->addWidget(comboBox_Device_Functions[i], i+1, 2);
        gridLayout->addWidget(comboBox_Function_Parameters[i], i+1, 3);
        gridLayout->addWidget(lineEdit_NameData[i], i+1, 4);
        gridLayout->addWidget(checkBox_Device_Show[i], i+1, 5);
        gridLayout->addWidget(checkBox_Device_Text[i], i+1, 6);
        gridLayout->addWidget(checkBox_Device_DB[i], i+1, 7);
        gridLayout->addWidget(comboBox_ColorData[i], i+1, 8);
        gridLayout->addWidget(comboBox_SizeData[i], i+1, 9);
    }

    gridLayout->addWidget(button_ReceivedData_Close,22,2);
    gridLayout->addWidget(button_ReceivedData_Add,22,1);

    gridLayout->setContentsMargins(5,5,5,5);
    gridLayout->setVerticalSpacing(5);
    gridLayout->setHorizontalSpacing(5);

    toolBar_GET->addWidget( hBox_GET );
    return toolBar_GET;
}

void LAMPhDevices::toolBar_GET_show_data()
{
    label_ReceivedData[int_GET]->show();
    comboBox_Device[int_GET]->show();
    comboBox_Device_Functions[int_GET]->show();
    comboBox_Function_Parameters[int_GET]->show();
    lineEdit_NameData[int_GET]->show();
    checkBox_Device_Show[int_GET]->show();
    checkBox_Device_Text[int_GET]->show();
    checkBox_Device_DB[int_GET]->show();
    comboBox_ColorData[int_GET]->show();
    comboBox_SizeData[int_GET]->show();
    if (int_GET<20)int_GET++;
}

void LAMPhDevices::toolBar_GET_hide_data()
{
    if (int_GET>5) int_GET--;
    label_ReceivedData[int_GET]->hide();
    comboBox_Device[int_GET]->hide();
    comboBox_Device_Functions[int_GET]->hide();
    comboBox_Function_Parameters[int_GET]->hide();
    lineEdit_NameData[int_GET]->hide();
    checkBox_Device_Show[int_GET]->hide();
    checkBox_Device_Text[int_GET]->hide();
    checkBox_Device_DB[int_GET]->hide();
    comboBox_ColorData[int_GET]->hide();
    comboBox_SizeData[int_GET]->hide();
}



QGroupBox *LAMPhDevices::groupLAMPhDevices()
{
   QGroupBox *groupBox = new QGroupBox(tr(""));
   groupBox->setStyleSheet("border: 0px solid white");


   labelPlotSetting = new QLabel(tr("labelPlotSetting"));

  //labelEmpty  = new QLabel(tr(""));



  QGridLayout * gridLayout = new QGridLayout();

  //gridLayout->addWidget(groupLAMPhDATA(),0,0);
  //gridLayout->addWidget(groupLAMPhPorts(),0,1);

  //gridLayout->setColumnMinimumWidth(0,500);
  //gridLayout->setColumnMinimumWidth(1,500);


  groupBox->setLayout(gridLayout);

   return groupBox;
}

/*QGroupBox *LAMPhDevices::groupLAMPhDATA()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
    //groupBox->setStyleSheet("border: 0px solid white");

    label_label_ReceivedData = new QLabel(tr("DATA"));
    label_comboBox_Device = new QLabel(tr("Devices"));
    label_comboBox_Device_Functions = new QLabel(tr("Functions"));
    label_comboBox_Function_Parameters = new QLabel(tr("Parameters"));
    label_lineEdit_NameData = new QLabel(tr("Name"));
    label_checkBox_Device_Show = new QLabel(tr("Plot"));
    label_checkBox_Device_Text = new QLabel(tr("Text"));
    label_checkBox_Device_DB = new QLabel(tr("DB"));
    label_comboBox_ColorData = new QLabel(tr("Color"));
    label_comboBox_SizeData = new QLabel(tr("Size"));

    for(int i=0; i<20; i++)
    {
        label_ReceivedData[i] = new QLabel(tr("DATA"));
        comboBox_Device[i] = new QComboBox();
        comboBox_Device_Functions[i] = new QComboBox();
        comboBox_Function_Parameters[i] = new QComboBox();
        lineEdit_NameData[i] = new QLineEdit(tr("Name"));
        //lineEdit_NameData[i]->setFixedWidth(60);
        checkBox_Device_Show[i]  = new QCheckBox(tr(""));
        checkBox_Device_Text[i]  = new QCheckBox(tr(""));
        checkBox_Device_DB[i]  = new QCheckBox(tr(""));
        comboBox_ColorData[i] = new QComboBox();
        comboBox_SizeData[i] = new QComboBox();
    }


    QGridLayout * gridLayout = new QGridLayout();

    //gridLayout->addWidget(labelPlotSetting,0,0);
    //gridLayout->addWidget(groupLAMPhDATA(),0,1);

    gridLayout->addWidget(label_label_ReceivedData, 0, 0);
    gridLayout->addWidget(label_comboBox_Device, 0, 1);
    gridLayout->addWidget(label_comboBox_Device_Functions, 0, 2);
    gridLayout->addWidget(label_comboBox_Function_Parameters, 0, 3);
    gridLayout->addWidget(label_lineEdit_NameData, 0, 4);
    gridLayout->addWidget(label_checkBox_Device_Show, 0, 5);
    gridLayout->addWidget(label_checkBox_Device_Text, 0, 6);
    gridLayout->addWidget(label_checkBox_Device_DB, 0, 7);
    gridLayout->addWidget(label_comboBox_ColorData, 0, 8);
    gridLayout->addWidget(label_comboBox_SizeData, 0, 9);


    for(int i=0; i<20; i++)
    {
        gridLayout->addWidget(label_ReceivedData[i], i+1, 0);
        gridLayout->addWidget(comboBox_Device[i], i+1, 1);
        gridLayout->addWidget(comboBox_Device_Functions[i], i+1, 2);
        gridLayout->addWidget(comboBox_Function_Parameters[i], i+1, 3);
        gridLayout->addWidget(lineEdit_NameData[i], i+1, 4);
        gridLayout->addWidget(checkBox_Device_Show[i], i+1, 5);
        gridLayout->addWidget(checkBox_Device_Text[i], i+1, 6);
        gridLayout->addWidget(checkBox_Device_DB[i], i+1, 7);
        gridLayout->addWidget(comboBox_ColorData[i], i+1, 8);
        gridLayout->addWidget(comboBox_SizeData[i], i+1, 9);

    }
    button_ReceivedData_Close = new QPushButton(tr("Close"));
    button_ReceivedData_Add = new QPushButton(tr("Add"));


    gridLayout->addWidget(button_ReceivedData_Close,22,0);
    gridLayout->addWidget(button_ReceivedData_Add,23,0);

    gridLayout->setContentsMargins(5,5,5,5);
    gridLayout->setVerticalSpacing(5);
    gridLayout->setHorizontalSpacing(5);


    groupBox->setLayout(gridLayout);
    return groupBox;
}

QGroupBox *LAMPhDevices::groupLAMPhPorts()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
    //groupBox->setStyleSheet("border: 0px solid white");

    // COM PORTS (Sockets, LAN)

    label_label_COM_Port = new QLabel(tr("Ports"));
    for(int i=0; i<20; i++) label_COM_Port[i] = new QLabel(tr("COM i  Device -> APPA205Lib"));

    // DEVICES

    label_label_Device = new QLabel(tr("Devices"));

    for(int i=0; i<20; i++){
        label_Device[i] = new QLabel(tr("I APPA205"));
        label_Device_COM_Port[i] = new QLabel(tr("COM 1"));
        button_Device_Info[i] = new QPushButton(tr("Info"));
        button_Device_Setting[i] = new QPushButton(tr("Settings"));
    }



    QGridLayout * gridLayout = new QGridLayout();


    gridLayout->addWidget(label_label_COM_Port, 0, 0);

    for(int i=0; i<20; i++)
    {
        gridLayout->addWidget(label_COM_Port[i], i+1, 0);
    }


    gridLayout->addWidget(label_label_COM_Port, 22, 0);

    for(int i=0; i<20; i++)
    {
        gridLayout->addWidget(label_Device[i], i+23, 0);
        gridLayout->addWidget(label_Device_COM_Port[i], i+23, 1);
        gridLayout->addWidget(button_Device_Info[i], i+23, 2);
        gridLayout->addWidget(button_Device_Setting[i], i+23, 3);
    }


    groupBox->setLayout(gridLayout);

     return groupBox;
}*/



void LAMPhDevices::getDataDll()
{
    static QString suffix = "";
    #ifdef QT_DEBUG
        suffix = "d";
    #endif

        static const QString LIB_NAME = "COM_Appa_Lib" + suffix;

        QLibrary lib( LIB_NAME );
        if( !lib.load() ) {
            qDebug() << "Loading failed!";
        }

        typedef void ( *InputTest )( const char* const );
        InputTest inputTest = ( InputTest ) lib.resolve( "inputTest" );
        if( inputTest ) {
            inputTest( "Hello to MyLib!" );
        }

        typedef const char* ( *OutputTest )();
        OutputTest outputTest = ( OutputTest ) lib.resolve( "outputTest" );
        if( outputTest ) {
            qDebug() << outputTest();
            //labelPlotSettingS->setText( outputTest()  );
        }

        typedef QString (*Fct) (const QString&);
        Fct fct = (Fct)(lib.resolve("oddUpper"));
        if (fct) {
            //labelPlotSettingS->setText(fct("SEND TEXT send text"));
        }

}






