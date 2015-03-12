#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <QObject>
#include "calibration.h"
#include <vector>

using namespace std;

class calibration : public QObject
{
    Q_OBJECT
public:
    explicit calibration(QObject *parent = 0);
    ~calibration();
    double matrix[4][6];
    void compute_calibration(vector<double> * H_vector,vector<double> * V_vector,vector<double> * P_vector,vector<double> * M_vector,vector<double> * L_vector, std::vector<double> * R_vector );
signals:

public slots:
};

#endif // CALIBRATION_H
