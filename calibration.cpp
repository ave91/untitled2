#include "calibration.h"
#include "QMessageBox"
#include "cmath"
#include "vector"
#include "Eigen/Core"
#include "Eigen/LU"
#include <iostream>


using namespace Eigen;

calibration::calibration(QObject *parent) : QObject(parent)
{
    //untitled_pointer_int=0;
    H_vector.reserve(7);
    H_vector.resize(7);
    V_vector.reserve(7);
    V_vector.resize(7);
    L_vector.reserve(7);
    L_vector.resize(7);
    P_vector.reserve(7);
    P_vector.resize(7);
    M_vector.reserve(7);
    M_vector.resize(7);
    L_vector.reserve(7);
    L_vector.resize(7);
    R_vector.reserve(7);
    R_vector.resize(7);

    stokes_dat.resize(4);

}

calibration::~calibration()
{

}

void calibration::compute_calibration_4_det( ){


    //Here detector 7 is used as total power
        /*
        double ih_tot=H_vector[6];
        double iv_tot=V_vector[6];
        double ip_tot=P_vector[6];
        double il_tot=L_vector[6];
        */
        double ih_tot=1;
        double iv_tot=1;
        double ip_tot=1;
        double il_tot=1;

        double ihh=(H_vector[0])/(ih_tot);
        double ihv=(H_vector[1])/(ih_tot);
        double ihp=(H_vector[2])/(ih_tot);
        double ihl=(H_vector[3])/(ih_tot);


        double ivh=(V_vector[0])/(iv_tot);
        double ivv=(V_vector[1])/(iv_tot);
        double ivp=(V_vector[2])/(iv_tot);
        double ivl=(V_vector[3])/(iv_tot);

        double iph=(P_vector[0])/(ip_tot);
        double ipv=(P_vector[1])/(ip_tot);
        double ipp=(P_vector[2])/(ip_tot);
        double ipl=(P_vector[3])/(ip_tot);


        double ilh=(L_vector[0])/(il_tot);
        double ilv=(L_vector[1])/(il_tot);
        double ilp=(L_vector[2])/(il_tot);
        double ill=(L_vector[3])/(il_tot);

        matrix[0][0]=((ihv*ilp*ipl - ihp*ilv*ipl - ihv*ill*ipp + ihl*ilv*ipp + ihp*ill*ipv - ihl*ilp*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ihv*ilp*ivl) + ihp*ilv*ivl + ihv*ill*ivp - ihl*ilv*ivp - ihp*ill*ivv + ihl*ilp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ihv*ipp*ivl - ihp*ipv*ivl - ihv*ipl*ivp + ihl*ipv*ivp + ihp*ipl*ivv - ihl*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ilv*ipp*ivl) + ilp*ipv*ivl + ilv*ipl*ivp - ill*ipv*ivp - ilp*ipl*ivv + ill*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[0][1]=((-(ihp*ill*iph) + ihl*ilp*iph + ihp*ilh*ipl - ihh*ilp*ipl - ihl*ilh*ipp + ihh*ill*ipp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ihp*ill*ivh - ihl*ilp*ivh - ihp*ilh*ivl + ihh*ilp*ivl + ihl*ilh*ivp - ihh*ill*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ihp*ipl*ivh) + ihl*ipp*ivh + ihp*iph*ivl - ihh*ipp*ivl - ihl*iph*ivp + ihh*ipl*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ilp*ipl*ivh - ill*ipp*ivh - ilp*iph*ivl + ilh*ipp*ivl + ill*iph*ivp - ilh*ipl*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[0][2]=((ihv*ill*iph - ihl*ilv*iph - ihv*ilh*ipl + ihh*ilv*ipl + ihl*ilh*ipv - ihh*ill*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ihv*ill*ivh) + ihl*ilv*ivh + ihv*ilh*ivl - ihh*ilv*ivl - ihl*ilh*ivv + ihh*ill*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ihv*ipl*ivh - ihl*ipv*ivh - ihv*iph*ivl + ihh*ipv*ivl + ihl*iph*ivv - ihh*ipl*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ilv*ipl*ivh) + ill*ipv*ivh + ilv*iph*ivl - ilh*ipv*ivl - ill*iph*ivv + ilh*ipl*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[0][3]=((-(ihv*ilp*iph) + ihp*ilv*iph + ihv*ilh*ipp - ihh*ilv*ipp - ihp*ilh*ipv + ihh*ilp*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ihv*ilp*ivh - ihp*ilv*ivh - ihv*ilh*ivp + ihh*ilv*ivp + ihp*ilh*ivv - ihh*ilp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (-(ihv*ipp*ivh) + ihp*ipv*ivh + ihv*iph*ivp - ihh*ipv*ivp - ihp*iph*ivv + ihh*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv) + (ilv*ipp*ivh - ilp*ipv*ivh - ilv*iph*ivp + ilh*ipv*ivp + ilp*iph*ivv - ilh*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[1][0]=(-((ihv*ilp*ipl - ihp*ilv*ipl - ihv*ill*ipp + ihl*ilv*ipp + ihp*ill*ipv - ihl*ilp*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv)) + (-(ilv*ipp*ivl) + ilp*ipv*ivl + ilv*ipl*ivp - ill*ipv*ivp - ilp*ipl*ivv + ill*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[1][1]=(-((-(ihp*ill*iph) + ihl*ilp*iph + ihp*ilh*ipl - ihh*ilp*ipl - ihl*ilh*ipp + ihh*ill*ipp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv)) + (ilp*ipl*ivh - ill*ipp*ivh - ilp*iph*ivl + ilh*ipp*ivl + ill*iph*ivp - ilh*ipl*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[1][2]=(-((ihv*ill*iph - ihl*ilv*iph - ihv*ilh*ipl + ihh*ilv*ipl + ihl*ilh*ipv - ihh*ill*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv)) + (-(ilv*ipl*ivh) + ill*ipv*ivh + ilv*iph*ivl - ilh*ipv*ivl - ill*iph*ivv + ilh*ipl*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[1][3]=(-((-(ihv*ilp*iph) + ihp*ilv*iph + ihv*ilh*ipp - ihh*ilv*ipp - ihp*ilh*ipv + ihh*ilp*ipv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv)) + (ilv*ipp*ivh - ilp*ipv*ivh - ilv*iph*ivp + ilh*ipv*ivp + ilp*iph*ivv - ilh*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[2][0]=((-(ihv*ilp*ivl) + ihp*ilv*ivl + ihv*ill*ivp - ihl*ilv*ivp - ihp*ill*ivv + ihl*ilp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[2][1]=((ihp*ill*ivh - ihl*ilp*ivh - ihp*ilh*ivl + ihh*ilp*ivl + ihl*ilh*ivp - ihh*ill*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[2][2]=((-(ihv*ill*ivh) + ihl*ilv*ivh + ihv*ilh*ivl - ihh*ilv*ivl - ihl*ilh*ivv + ihh*ill*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[2][3]=((ihv*ilp*ivh - ihp*ilv*ivh - ihv*ilh*ivp + ihh*ilv*ivp + ihp*ilh*ivv - ihh*ilp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[3][0]=((ihv*ipp*ivl - ihp*ipv*ivl - ihv*ipl*ivp + ihl*ipv*ivp + ihp*ipl*ivv - ihl*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[3][1]=((-(ihp*ipl*ivh) + ihl*ipp*ivh + ihp*iph*ivl - ihh*ipp*ivl - ihl*iph*ivp + ihh*ipl*ivp)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[3][2]=((ihv*ipl*ivh - ihl*ipv*ivh - ihv*iph*ivl + ihh*ipv*ivl + ihl*iph*ivv - ihh*ipl*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
        matrix[3][3]=((-(ihv*ipp*ivh) + ihp*ipv*ivh + ihv*iph*ivp - ihh*ipv*ivp - ihp*iph*ivv + ihh*ipp*ivv)/(ihv*ilp*ipl*ivh - ihp*ilv*ipl*ivh - ihv*ill*ipp*ivh + ihl*ilv*ipp*ivh + ihp*ill*ipv*ivh - ihl*ilp*ipv*ivh - ihv*ilp*iph*ivl + ihp*ilv*iph*ivl + ihv*ilh*ipp*ivl - ihh*ilv*ipp*ivl - ihp*ilh*ipv*ivl + ihh*ilp*ipv*ivl + ihv*ill*iph*ivp - ihl*ilv*iph*ivp - ihv*ilh*ipl*ivp + ihh*ilv*ipl*ivp + ihl*ilh*ipv*ivp - ihh*ill*ipv*ivp - ihp*ill*iph*ivv + ihl*ilp*iph*ivv + ihp*ilh*ipl*ivv - ihh*ilp*ipl*ivv - ihl*ilh*ipp*ivv + ihh*ill*ipp*ivv));
}


void calibration::compute_calibration_Numeric( ){

   MatrixXd Smat(4,6);
    Smat<<1, 1, 1, 1, 1, 1, 1,-1, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, -1;
    //std::cout<<Smat<<std::endl;
     MatrixXd Dmat(6,6);
     MatrixXd Dmat_inv(6,6);
      MatrixXd final(4,6);
     for(int i=0;i<6;i++){
        Dmat(i,0)=H_vector[i];
        Dmat(i,1)=V_vector[i];
        Dmat(i,2)=P_vector[i];
        Dmat(i,3)=M_vector[i];
        Dmat(i,4)=L_vector[i];
        Dmat(i,5)=R_vector[i];


     }
    cout<<Dmat<<endl;
     Dmat_inv=Dmat.inverse();
    //Check
    cout<<Dmat_inv*Dmat<<endl;
    //
    final=Smat*Dmat_inv;
    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
            matrix[i][j]=final(i,j);
        }

    }
    cout<<final<<endl;
}
