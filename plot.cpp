#include "plot.h"
#include "ui_plot.h"



Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);


}

Plot::~Plot()
{
    delete ui;
}

void Plot::run(acquisition * acq_pointer){
    if(acq_pointer!=0){
    int size=acq_pointer->data.size();
    QVector<double> x(size), y(size); // initialize with entries 0..100
    for (int i=0; i<size; ++i)
    {
      x[i] = i; // x goes from -1 to 1
    }
    y.fromStdVector(acq_pointer->data);
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
