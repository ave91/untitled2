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
    explicit Plot(QWidget *parent = 0);
    void run(acquisition * acq_pointer);

    ~Plot();

private:
    Ui::Plot *ui;
};

#endif // PLOT_H
