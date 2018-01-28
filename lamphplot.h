#ifndef LAMPHPLOT_H
#define LAMPHPLOT_H

#include <QSqlTableModel>
#include <QWidget>
#include <QAction>
#include <QToolBar>

class QSpinBox;
class QPushButton;
class MainPlot;
class Counter;
class QCheckBox;
class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;
class Plot;
class QPolygon;

QT_BEGIN_NAMESPACE
class QGroupBox;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QMenuBar;
QT_END_NAMESPACE

class LAMPhPlot : public QWidget
{
    Q_OBJECT

public:
    explicit LAMPhPlot(QString loginQString, QWidget *parent = 0);
    //~LAMPhPlot();

private Q_SLOTS:
    void showRunning( bool );
    void appendPoints( bool );
    void showElapsed( int );

    void moved( const QPoint & );
    void selected( const QPolygon & );
    void exportDocument();
    void enableZoomMode( bool );

private:
    QToolBar *toolBar();
    void initWhatsThis();

private:
    void showInfo( QString text = QString::null );

    Counter *d_randomCount;
    Counter *d_timerCount;
    QCheckBox *d_symbolType;
    QAction *d_startAction;
    QAction *d_clearAction;
    MainPlot *d_plot;

    QwtPlotZoomer *d_zoomer[2];
    QwtPlotPicker *d_picker;
    QwtPlotPanner *d_panner;

private:
    QString         *login;

    QPushButton     *newExpButton;
    QPushButton     *editExpButton;
    QPushButton     *tableButton;


private:

    QMenuBar *menu_bar;
    QMenuBar *menu_barDevices;
    QLabel *infoLabel;
   


};

#endif // LAMPHPLOT_H
