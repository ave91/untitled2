#include "plot.h"
#include "ui_plot.h"
#include <windows.h>



Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    acq_int_point=0;

}

Plot::~Plot()
{
    delete ui;
}

void Plot::run(acquisition * acq_pointer){
    acq_int_point=acq_pointer;
    if(acq_pointer!=0){
    int size=acq_pointer->data.size();
    QVector<double> x(size); // initialize with entries 0..100

    for (int i=0; i<size; ++i)
    {
      x[i] = i; // x goes from -1 to 1

    }
    QVector<double> y=QVector<double>::fromStdVector(acq_pointer->data);
    // create graph and assign data to it:
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customplot->xAxis->setLabel("x");
    ui->customplot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customplot->setInteraction(QCP::iRangeDrag, true);
   // ui->customplot->xAxis->setRange(-1, 1);
   // ui->customplot->yAxis->setRange(-1, 1);
    ui->customplot->rescaleAxes();

    ui->customplot->replot();
    }
    return;


}

void Plot::on_startButton_clicked()
{
    #if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
      QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
    #endif


      // include this section to fully disable antialiasing for higher performance:

      ui->customplot->setNotAntialiasedElements(QCP::aeAll);
      QFont font;
      font.setStyleStrategy(QFont::NoAntialias);
      ui->customplot->xAxis->setTickLabelFont(font);
      ui->customplot->yAxis->setTickLabelFont(font);
      ui->customplot->legend->setFont(font);

      ui->customplot->addGraph(); // blue line
      ui->customplot->graph(0)->setPen(QPen(Qt::blue));
      ui->customplot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
      ui->customplot->graph(0)->setAntialiasedFill(false);
      ui->customplot->addGraph(); // red line
      ui->customplot->graph(1)->setPen(QPen(Qt::red));
      ui->customplot->graph(0)->setChannelFillGraph(ui->customplot->graph(1));

      ui->customplot->addGraph(); // blue dot
      ui->customplot->graph(2)->setPen(QPen(Qt::blue));
      ui->customplot->graph(2)->setLineStyle(QCPGraph::lsNone);
      ui->customplot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
      ui->customplot->addGraph(); // red dot
      ui->customplot->graph(3)->setPen(QPen(Qt::red));
      ui->customplot->graph(3)->setLineStyle(QCPGraph::lsNone);
      ui->customplot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

      ui->customplot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
      ui->customplot->xAxis->setDateTimeFormat("hh:mm:ss");
      ui->customplot->xAxis->setAutoTickStep(false);
      ui->customplot->xAxis->setTickStep(2);
      ui->customplot->axisRect()->setupFullAxesBox();

      // make left and bottom axes transfer their ranges to right and top axes:
      connect(ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
      connect(ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->yAxis2, SLOT(setRange(QCPRange)));
       QTimer dataTimer;
      // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
      connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
      dataTimer.start(0); // Interval 0 means to refresh as fast as possible

}

