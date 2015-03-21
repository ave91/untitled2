#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <acquisition.h>

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(acquisition * acq_pointer,QWidget *parent = 0);
    void run();
    acquisition * acq_int_point;

    ~Plot();

private slots:
    void on_startButton_clicked();
    void realtimeDataSlot();

    void on_stopButton_clicked();

private:
    Ui::Plot *ui;
    QTimer dataTimer;
};

#endif // PLOT_H
