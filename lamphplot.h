#ifndef LAMPHPLOT_H
#define LAMPHPLOT_H

#include <qmainwindow.h>
#include <qaction.h>

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


class LAMPhPlot : public QMainWindow
{
    Q_OBJECT

public:
    LAMPhPlot(QString loginQString);
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
    QAction *d_zoomAction;
    QAction *d_exportAction;
    MainPlot *d_plot;

    QwtPlotZoomer *d_zoomer[2];
    QwtPlotPicker *d_picker;
    QwtPlotPanner *d_panner;

private:
    QString         *login;

    QPushButton     *newExpButton;
    QPushButton     *editExpButton;
    QPushButton     *tableButton;

    //QMenuBar *menu_bar;
    //QMenuBar *menu_barDevices;
    //QLabel *infoLabel;
   


};

#endif // LAMPHPLOT_H
