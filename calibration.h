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
    std::vector<double> H_vector;
    std::vector<double> V_vector;
    std::vector<double> P_vector;
    std::vector<double> M_vector;
    std::vector<double> L_vector;
    std::vector<double> R_vector;

    std::vector<double> stokes_dat;


    void compute_calibration();
    void compute_calibration_4_det( );
    void compute_calibration_Numeric( );
signals:

public slots:
};

#endif // CALIBRATION_H
