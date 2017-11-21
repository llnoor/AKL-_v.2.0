#ifndef DIALOGADDDEVICE_H
#define DIALOGADDDEVICE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <database.h>

QT_BEGIN_NAMESPACE
class QGroupBox;
class DialogAddDevice;
QT_END_NAMESPACE




class DialogAddDevice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddDevice(int row = -1, QWidget *parent = 0);
    ~DialogAddDevice();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);
    void okbuttonBox();


private:
    QGroupBox               *groupDevice();
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;

    QLineEdit *HostnameLineEdit;
    QLineEdit *IPAddressLineEdit;
    QLineEdit *MACLineEdit;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *okButton;
    QDialogButtonBox *buttonBox;


private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DIALOGADDDEVICE_H
