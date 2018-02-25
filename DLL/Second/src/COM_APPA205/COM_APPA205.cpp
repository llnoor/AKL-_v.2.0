#include "COM_APPA205.h"

#include <stdio.h>

#include <string>
#include <QtSerialPort/QSerialPort>

#define NAME  "COM_APPA205"
#define DEVICE "APPA205"
#define TXT "_functions.txt"
#define FUNCTIONS  "char checkPORT(char,char); void setPORT(char); float getFloat(); char getUnit(); char getValue(); char getSN()"
#define INFO "The Lib for LAMPh to connect with APPA205";



float result_float;
char * unit;
char * value;
int i_test=0;

//QSerialPort port_appa;
QByteArray data;

const char* getInfo() {
    createFile();
    return INFO;
}

const char* DLLMain() {
    createFile();
    return INFO;
}

const char* getFunctions() {
    createFile();
    return FUNCTIONS;
}

bool createFile(){
    FILE *file;
    if ((file = fopen(NAME TXT,"w")) == NULL) return false;
    fprintf(file,"%c\n",FUNCTIONS);
    fclose(file);
}

const char* checkCOM( const char* const port, const char* const info ){
    std::string str = info;
    if (0 != str.find(DEVICE) ){
        //setCOM(port);
        return DEVICE;
    }

}


void setCOM( const char* const port ){
    /*port_appa->setPortName(QString::fromUtf8(port));
    port_appa->setBaudRate(QSerialPort::Baud9600);
    port_appa->setStopBits(QSerialPort::OneStop);
    port_appa->setDataBits(QSerialPort::Data8);
    port_appa->setParity(QSerialPort::NoParity);
    port_appa->setFlowControl(QSerialPort::NoFlowControl);
    port_appa->open(QIODevice::ReadWrite);*/
}

void readData(){
    /*QByteArray ba;
    ba.resize(5);
    ba[0] = 0x55;
    ba[1] = 0x55;
    ba[2] = 0x00;
    ba[3] = 0x00;
    ba[4] = 0xaa;
    port_appa->write(ba);
    port_appa->waitForBytesWritten(300);

    data = port_appa->readAll();*/
}

const char* getSN(){

    /*if (port_appa->isOpen()) readData();;
    else return 0;

    char *buff = data.data();
    int buff_int_char[60];
    for (int l=0; l<30; l++){
        buff_int_char[l]=0;
        buff_int_char[l]= buff[l]  - '0';
    }
    int sn_appa =
            buff_int_char[12]* 10000000+
            buff_int_char[13]* 1000000+
            buff_int_char[14]* 100000+
            buff_int_char[15]* 10000+
            buff_int_char[16]* 1000+
            buff_int_char[17]* 100+
            buff_int_char[18]* 10+
            buff_int_char[19];
    QString str= QString::number(sn_appa);
    return str.toStdString();*/
    return "APPA205TEST";
}

float getFloat(){

    /*if (port_appa->isOpen()) readData();;
    else return 0;

    char *buff = data.data();
    int buff_int[60];

    for (int l=0; l<60; l++){
        buff_int[l]=buff[l];
    }

    int buff_int_34=buff_int[34];
    int buff_int_35=buff_int[35];
    if (buff_int[34]<0)
    {
        buff_int_34= buff_int[34]+ 256;
    }
    if (buff_int[35]<0)
    {
        buff_int_35= buff_int[35]+ 256;
    }

    result_float= buff_int_34 +(buff_int_35*256);

    if (buff_int[36]<0)
    {
        result_float=result_float*(-1);
    }

    switch (buff_int[37])
    {
    case 0: break;
    case 1: result_float=result_float*(0.1);break;
    case 2: result_float=result_float*(0.01);break;
    case 4: result_float=result_float*(0.001);break;
    case 8: result_float=result_float*(0.0001);break;
    }

    return result_float;*/

    result_float = (float)i_test++;
    return result_float;
}


const char* getUnit(){
    unit = "V";
    return unit;
}

const char* getValue(){
    sprintf(value, "%f", result_float);

    return strcat( value, unit ) ;
}

/*void inputTest( const char* const str ) {
    std::cout << str << std::endl;
}

const char* outputTest() {
    return "Hello from LAMPhLib!";
}

QString oddUpper(const QString& str)
{
    QString strTemp;

    for (int i = 0; i < str.length(); ++i) {
        strTemp += (i % 2) ? str.at(i) : str.at(i).toUpper();
    }

    return strTemp;
}*/



