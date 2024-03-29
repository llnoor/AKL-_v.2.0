/*-------------------------------------------------
*	
*	Created by Ilnur Gimazov (ubvfp94@mail.ru)
*	
*-------------------------------------------------
*/


#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qwhatsthis.h>
#include <qpixmap.h>
#include <qwt_counter.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include "randomplot.h"
#include "mainwindow.h"
#include "start.xpm"
#include "clear.xpm"

#include "pixmaps.h"

class MyToolBar: public QToolBar
{
public:
    MyToolBar( MainWindow *parent ):
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

class Counter: public QWidget
{
public:
    Counter( QWidget *parent,
            const QString &prefix, const QString &suffix,
            int min, int max, int step ):
        QWidget( parent )
    {
        QHBoxLayout *layout = new QHBoxLayout( this );

        if ( !prefix.isEmpty() )
            layout->addWidget( new QLabel( prefix + " ", this ) );

        d_counter = new QSpinBox( this );
        d_counter->setRange( min, max );
        d_counter->setSingleStep( step );
        layout->addWidget( d_counter );

        if ( !suffix.isEmpty() )
            layout->addWidget( new QLabel( QString( " " ) + suffix, this ) );
    }

    void setValue( int value ) { d_counter->setValue( value ); }
    int value() const { return d_counter->value(); }

private:
    QSpinBox *d_counter;
};

class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( int xAxis, int yAxis, QWidget *canvas ):
        QwtPlotZoomer( xAxis, yAxis, canvas )
    {
        setTrackerMode( QwtPicker::AlwaysOff );
        setRubberBand( QwtPicker::NoRubberBand );

        // RightButton: zoom out by 1
        // Ctrl+RightButton: zoom out to full size

        setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
            Qt::RightButton );
    }
};

MainWindow::MainWindow()
{
    addToolBar( toolBar() );
#ifndef QT_NO_STATUSBAR
    ( void )statusBar();
#endif

    d_plot = new RandomPlot( this );
    const int margin = 4;
    d_plot->setContentsMargins( margin, margin, margin, margin );


    d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft,
        d_plot->canvas() );
    d_zoomer[0]->setRubberBand( QwtPicker::RectRubberBand );
    d_zoomer[0]->setRubberBandPen( QColor( Qt::green ) );
    d_zoomer[0]->setTrackerMode( QwtPicker::ActiveOnly );
    d_zoomer[0]->setTrackerPen( QColor( Qt::white ) );

    d_panner = new QwtPlotPanner( d_plot->canvas() );
    d_panner->setMouseButton( Qt::MidButton );

    d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
            QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
            d_plot->canvas() );
        d_picker->setStateMachine( new QwtPickerDragPointMachine() );
        d_picker->setRubberBandPen( QColor( Qt::green ) );
        d_picker->setRubberBand( QwtPicker::CrossRubberBand );
        d_picker->setTrackerPen( QColor( Qt::white ) );

    setCentralWidget( d_plot );

    connect( d_startAction, SIGNAL( toggled( bool ) ), this, SLOT( appendPoints( bool ) ) );
    connect( d_clearAction, SIGNAL( triggered() ), d_plot, SLOT( clear() ) );
    connect( d_symbolType, SIGNAL( toggled( bool ) ), d_plot, SLOT( showSymbols( bool ) ) );
    connect( d_plot, SIGNAL( running( bool ) ), this, SLOT( showRunning( bool ) ) );
    connect( d_plot, SIGNAL( elapsed( int ) ), this, SLOT( showElapsed( int ) ) );

    initWhatsThis();

    setContextMenuPolicy( Qt::NoContextMenu );

    /*int on = 1;
    d_panner->setEnabled( on );

    d_zoomer[0]->setEnabled( on );
    d_zoomer[0]->zoom( 0 );

    d_picker->setEnabled( !on );

    //showInfo();*/

    connect( d_picker, SIGNAL( moved( const QPoint & ) ),
        SLOT( moved( const QPoint & ) ) );
    connect( d_picker, SIGNAL( selected( const QPolygon & ) ),
        SLOT( selected( const QPolygon & ) ) );

    enableZoomMode( false );
    showInfo();

}



QToolBar *MainWindow::toolBar()
{
    MyToolBar *toolBar = new MyToolBar( this );

    toolBar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

    d_startAction = new QAction( QPixmap( start_xpm ), "Start", toolBar );
    d_startAction->setCheckable( true );
    d_clearAction = new QAction( QPixmap( clear_xpm ), "Clear", toolBar );
    QAction *whatsThisAction = QWhatsThis::createAction( toolBar );
    whatsThisAction->setText( "Help" );

    toolBar->addAction( d_startAction );
    toolBar->addAction( d_clearAction );
    toolBar->addAction( whatsThisAction );

    setIconSize( QSize( 22, 22 ) );

    QWidget *hBox = new QWidget( toolBar );

    d_symbolType = new QCheckBox( "Symbols", hBox );
    d_symbolType->setChecked( true );

    d_randomCount =
        new Counter( hBox, "Points", QString::null, 1, 100000, 100 );
    d_randomCount->setValue( 1000 );

    d_timerCount = new Counter( hBox, "Delay", "ms", 0, 100000, 100 );
    d_timerCount->setValue( 0 );

    QHBoxLayout *layout = new QHBoxLayout( hBox );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );
    layout->addSpacing( 10 );
    layout->addWidget( new QWidget( hBox ), 10 ); // spacer
    layout->addWidget( d_symbolType );
    layout->addSpacing( 5 );
    layout->addWidget( d_randomCount );
    layout->addSpacing( 5 );
    layout->addWidget( d_timerCount );

    showRunning( false );

    toolBar->addWidget( hBox );

    QToolButton *btnZoom = new QToolButton( toolBar );
    btnZoom->setText( "Zoom" );
    btnZoom->setIcon( QPixmap( zoom_xpm ) );
    btnZoom->setCheckable( true );
    btnZoom->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnZoom );
    connect( btnZoom, SIGNAL( toggled( bool ) ), SLOT( enableZoomMode( bool ) ) );

    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setIcon( QPixmap( print_xpm ) );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );
    connect( btnExport, SIGNAL( clicked() ), SLOT( exportDocument() ) );

    return toolBar;
}

void MainWindow::appendPoints( bool on )
{
    if ( on )
        d_plot->append( d_timerCount->value(),
                        d_randomCount->value() );
    else
        d_plot->stop();
}

void MainWindow::showRunning( bool running )
{
    d_randomCount->setEnabled( !running );
    d_timerCount->setEnabled( !running );
    d_startAction->setChecked( running );
    d_startAction->setText( running ? "Stop" : "Start" );
}

void MainWindow::showElapsed( int ms )
{
    QString text;
    text.setNum( ms );
    text += " ms";

    statusBar()->showMessage( text );
}

void MainWindow::initWhatsThis()
{
    const char *text1 =
        "Zooming is enabled until the selected area gets "
        "too small for the significance on the axes.\n\n"
        "You can zoom in using the left mouse button.\n"
        "The middle mouse button is used to go back to the "
        "previous zoomed area.\n"
        "The right mouse button is used to unzoom completely.";

    const char *text2 =
        "Number of random points that will be generated.";

    const char *text3 =
        "Delay between the generation of two random points.";

    const char *text4 =
        "Start generation of random points.\n\n"
        "The intention of this example is to show how to implement "
        "growing curves. The points will be generated and displayed "
        "one after the other.\n"
        "To check the performance, a small delay and a large number "
        "of points are useful. To watch the curve growing, a delay "
        " > 300 ms and less points are better.\n"
        "To inspect the curve, stacked zooming is implemented using the "
        "mouse buttons on the plot.";

    const char *text5 = "Remove all points.";

    d_plot->setWhatsThis( text1 );
    d_randomCount->setWhatsThis( text2 );
    d_timerCount->setWhatsThis( text3 );
    d_startAction->setWhatsThis( text4 );
    d_clearAction->setWhatsThis( text5 );
}

void MainWindow::exportDocument()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( d_plot, "LAMPh.pdf" );
}

void MainWindow::enableZoomMode( bool on )
{
    d_panner->setEnabled( on );

    d_zoomer[0]->setEnabled( on );
    //d_zoomer[0]->zoom( 0 );

    d_picker->setEnabled( !on );

    showInfo();
}

void MainWindow::showInfo( QString text )
{
    if ( text == QString::null )
    {
        if ( d_picker->rubberBand() )
            text = "Cursor Pos: Press left mouse button in plot region";
        else
            text = "Zoom: Press mouse button and drag";
    }

#ifndef QT_NO_STATUSBAR
    statusBar()->showMessage( text );
#endif
}

void MainWindow::moved( const QPoint &pos )
{
    QString info;
    info.sprintf( "Freq=%g, Ampl=%g, Phase=%g",
        d_plot->invTransform( QwtPlot::xBottom, pos.x() ),
        d_plot->invTransform( QwtPlot::yLeft, pos.y() ),
        d_plot->invTransform( QwtPlot::yRight, pos.y() )
    );
    showInfo( info );
}

void MainWindow::selected( const QPolygon & )
{
    showInfo();
}
