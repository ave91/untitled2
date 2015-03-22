#include "plot.h"
#include "ui_plot.h"
#include <windows.h>



Plot::Plot(acquisition * acq_pointer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    acq_int_point=0;
    acq_int_point=acq_pointer;
   // QGridLayout * layout1 = new QGridLayout(parent);
   //   layout1->addWidget(ui->customplot,0, 0);

}

Plot::~Plot()
{
    delete ui;
}

void Plot::run(){

    if(acq_int_point!=0){
    int size=acq_int_point->data.size();
    int single_size=size/7;
    QVector<double> x(size); // initialize with entries 0..100

    for (int i=0; i<size; ++i)
    {
      x[i] = i; // x goes from -1 to 1

    }

    vector<float64> data0(&(acq_int_point->data[0]),&acq_int_point->data[single_size-1]);
    vector<float64> data1(&acq_int_point->data[single_size],&acq_int_point->data[2*single_size-1]);
    vector<float64> data2(&acq_int_point->data[2*single_size],&acq_int_point->data[3*single_size-1]);
    vector<float64> data3(&acq_int_point->data[3*single_size],&acq_int_point->data[4*single_size-1]);
    vector<float64> data4(&acq_int_point->data[4*single_size],&acq_int_point->data[5*single_size-1]);
    vector<float64> data5(&acq_int_point->data[5*single_size],&acq_int_point->data[6*single_size-1]);
    vector<float64> data6(&acq_int_point->data[6*single_size],&acq_int_point->data[7*single_size-1]);


    QVector<double> y0=QVector<double>::fromStdVector(data0);
    QVector<double> y1=QVector<double>::fromStdVector(data1);
    QVector<double> y2=QVector<double>::fromStdVector(data2);
    QVector<double> y3=QVector<double>::fromStdVector(data3);
    QVector<double> y4=QVector<double>::fromStdVector(data4);
    QVector<double> y5=QVector<double>::fromStdVector(data5);
    QVector<double> y6=QVector<double>::fromStdVector(data6);

    // create graph:
    ui->customplot->addGraph();
    ui->customplot->addGraph();
    ui->customplot->addGraph();
    ui->customplot->addGraph();
    ui->customplot->addGraph();
    ui->customplot->addGraph();
    ui->customplot->addGraph();

    ui->customplot->graph(0)->setPen(QPen(Qt::blue));
    ui->customplot->graph(1)->setPen(QPen(Qt::red));
    ui->customplot->graph(2)->setPen(QPen(Qt::green));
    ui->customplot->graph(3)->setPen(QPen(Qt::black));
    ui->customplot->graph(4)->setPen(QPen(Qt::cyan));
    ui->customplot->graph(5)->setPen(QPen(Qt::yellow));
    ui->customplot->graph(6)->setPen(QPen(Qt::gray));


    ui->customplot->graph(0)->setData(x, y0);
    ui->customplot->graph(1)->setData(x, y1);
    ui->customplot->graph(2)->setData(x, y2);
    ui->customplot->graph(3)->setData(x, y3);
    ui->customplot->graph(4)->setData(x, y4);
    ui->customplot->graph(5)->setData(x, y5);
    ui->customplot->graph(6)->setData(x, y6);




    // give the axes some labels:
    ui->customplot->xAxis->setLabel("Sample");
    ui->customplot->yAxis->setLabel("Volt");
    // set axes ranges, so we see all data:
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->yAxis2, SLOT(setRange(QCPRange)));
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
   // ui->customplot->xAxis->setRange(-1, 1);
   // ui->customplot->yAxis->setRange(-1, 1);
    ui->customplot->rescaleAxes();
    ui->customplot->legend->setVisible(true);

    ui->customplot->replot();
    }
    return;


}

void Plot::on_startButton_clicked()
{   /*
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
*/


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

/*
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

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
*/

}

void Plot::realtimeDataSlot(){

    int size=acq_int_point->data.size();
    int single_size=size/7;
    QVector<double> x(size); // initialize with entries 0..100

    for (int i=0; i<size; ++i)
    {
      x[i] = i; // x goes from -1 to 1

    }

    vector<float64> data0(&(acq_int_point->data[0]),&acq_int_point->data[single_size-1]);
    vector<float64> data1(&acq_int_point->data[single_size],&acq_int_point->data[2*single_size-1]);
    vector<float64> data2(&acq_int_point->data[2*single_size],&acq_int_point->data[3*single_size-1]);
    vector<float64> data3(&acq_int_point->data[3*single_size],&acq_int_point->data[4*single_size-1]);
    vector<float64> data4(&acq_int_point->data[4*single_size],&acq_int_point->data[5*single_size-1]);
    vector<float64> data5(&acq_int_point->data[5*single_size],&acq_int_point->data[6*single_size-1]);
    vector<float64> data6(&acq_int_point->data[6*single_size],&acq_int_point->data[7*single_size-1]);


    QVector<double> y0=QVector<double>::fromStdVector(data0);
    QVector<double> y1=QVector<double>::fromStdVector(data1);
    QVector<double> y2=QVector<double>::fromStdVector(data2);
    QVector<double> y3=QVector<double>::fromStdVector(data3);
    QVector<double> y4=QVector<double>::fromStdVector(data4);
    QVector<double> y5=QVector<double>::fromStdVector(data5);
    QVector<double> y6=QVector<double>::fromStdVector(data6);

    ui->customplot->graph(0)->setData(x, y0);
    ui->customplot->graph(1)->setData(x, y1);
    ui->customplot->graph(2)->setData(x, y2);
    ui->customplot->graph(3)->setData(x, y3);
    ui->customplot->graph(4)->setData(x, y4);
    ui->customplot->graph(5)->setData(x, y5);
    ui->customplot->graph(6)->setData(x, y6);

    ui->customplot->graph(0)->rescaleValueAxis();
    ui->customplot->graph(1)->rescaleValueAxis(true);
    ui->customplot->graph(2)->rescaleValueAxis(true);
    ui->customplot->graph(3)->rescaleValueAxis(true);
    ui->customplot->graph(4)->rescaleValueAxis(true);
    ui->customplot->graph(5)->rescaleValueAxis(true);
    ui->customplot->graph(6)->rescaleValueAxis(true);



    ui->customplot->replot();



/*
    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
      double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      ui->customplot->graph(0)->addData(key, value0);
      ui->customplot->graph(1)->addData(key, value1);
      // set data of dots:
      ui->customplot->graph(2)->clearData();
      ui->customplot->graph(2)->addData(key, value0);
      ui->customplot->graph(3)->clearData();
      ui->customplot->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->customplot->graph(0)->removeDataBefore(key-8);
      ui->customplot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->customplot->graph(0)->rescaleValueAxis();
      ui->customplot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customplot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customplot->replot();

*/

}

void Plot::on_stopButton_clicked()
{
   disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
}
