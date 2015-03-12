#include "calibration.h"
#include "QMessageBox"
#include "cmath"
#include "vector"



calibration::calibration(QObject *parent) : QObject(parent)
{
    //untitled_pointer_int=0;
}

calibration::~calibration()
{

}

void calibration::compute_calibration(vector<double> * H_vector,vector<double> * V_vector,vector<double> * P_vector,vector<double> * M_vector,vector<double> * L_vector, std::vector<double> * R_vector ){


    //Here detector 7 is used as total power
        double ih_tot=(*H_vector)[6];
        double iv_tot=(*V_vector)[6];
        double ip_tot=(*P_vector)[6];
        double im_tot=(*M_vector)[6];
        double il_tot=(*L_vector)[6];
        double ir_tot=(*R_vector)[6];


        double ihh=((*H_vector)[0])/(ih_tot);
        double ihv=((*H_vector)[1])/(ih_tot);
        double ihp=((*H_vector)[2])/(ih_tot);
        double ihm=((*H_vector)[3])/(ih_tot);
        double ihl=((*H_vector)[4])/(ih_tot);
        double ihr=((*H_vector)[5])/(ih_tot);
        double ivh=((*V_vector)[0])/(iv_tot);
        double ivv=((*V_vector)[1])/(iv_tot);
        double ivp=((*V_vector)[2])/(iv_tot);
        double ivm=((*V_vector)[3])/(iv_tot);
        double ivl=((*V_vector)[4])/(iv_tot);
        double ivr=((*V_vector)[5])/(iv_tot);
        double iph=((*P_vector)[0])/(ip_tot);
        double ipv=((*P_vector)[1])/(ip_tot);
        double ipp=((*P_vector)[2])/(ip_tot);
        double ipm=((*P_vector)[3])/(ip_tot);
        double ipl=((*P_vector)[4])/(ip_tot);
        double ipr=((*P_vector)[5])/(ip_tot);
        double imh=((*M_vector)[0])/(im_tot);
        double imv=((*M_vector)[1])/(im_tot);
        double imp=((*M_vector)[2])/(im_tot);
        double imm=((*M_vector)[3])/(im_tot);
        double iml=((*M_vector)[4])/(im_tot);
        double imr=((*M_vector)[5])/(im_tot);
        double ilh=((*L_vector)[0])/(il_tot);
        double ilv=((*L_vector)[1])/(il_tot);
        double ilp=((*L_vector)[2])/(il_tot);
        double ilm=((*L_vector)[3])/(il_tot);
        double ill=((*L_vector)[4])/(il_tot);
        double ilr=((*L_vector)[5])/(il_tot);
        double irh=((*R_vector)[0])/(ir_tot);
        double irv=((*R_vector)[1])/(ir_tot);
        double irp=((*R_vector)[2])/(ir_tot);
        double irm=((*R_vector)[3])/(ir_tot);
        double irl=((*R_vector)[4])/(ir_tot);
        double irr=((*R_vector)[5])/(ir_tot);


    matrix[0][0]=(-(((((-(ipr*irl*irr) + ipl*pow(irr,2) + ipr*irr*ivl - pow(irr,2)*ivl - ipl*irr*ivr + irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                     (-(ilr*irl*irr) + ill*pow(irr,2) + ilr*irr*ivl - pow(irr,2)*ivl - ill*irr*ivr + irl*irr*ivr)*
                      (-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr)) -
                  ((-(imr*irl*irr) + iml*pow(irr,2) + imr*irr*ivl - pow(irr,2)*ivl - iml*irr*ivr + irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                     (-(ilr*irl*irr) + ill*pow(irr,2) + ilr*irr*ivl - pow(irr,2)*ivl - ill*irr*ivr + irl*irr*ivr)*
                      (-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr))*
                   (-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(ipr*irp*irr*ivl) + ipp*pow(irr,2)*ivl + ipr*irl*irr*ivp - ipl*pow(irr,2)*ivp - ipp*irl*irr*ivr + ipl*irp*irr*ivr)))*
                ((-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr))*
                   ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (ihv*pow(irr,2)*ivl - ihr*irr*irv*ivl - ihv*irl*irr*ivr + ihl*irr*irv*ivr + ihr*irl*irr*ivv - ihl*pow(irr,2)*ivv) -
                     (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                      (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) -
                  ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(ihr*irp*irr*ivl) + ihp*pow(irr,2)*ivl + ihr*irl*irr*ivp - ihl*pow(irr,2)*ivp - ihp*irl*irr*ivr + ihl*irp*irr*ivr) -
                     (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                      (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (imv*pow(irr,2)*ivl - imr*irr*irv*ivl - imv*irl*irr*ivr + iml*irr*irv*ivr + imr*irl*irr*ivv - iml*pow(irr,2)*ivv))) -
               (-(((-(imr*irl*irr) + iml*pow(irr,2) + imr*irr*ivl - pow(irr,2)*ivl - iml*irr*ivr + irl*irr*ivr)*
                        (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                       (-(ilr*irl*irr) + ill*pow(irr,2) + ilr*irr*ivl - pow(irr,2)*ivl - ill*irr*ivr + irl*irr*ivr)*
                        (-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr))*
                     ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (-(ihr*irp*irr*ivl) + ihp*pow(irr,2)*ivl + ihr*irl*irr*ivp - ihl*pow(irr,2)*ivp - ihp*irl*irr*ivr + ihl*irp*irr*ivr) -
                       (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr))) +
                  (-((-(ilr*irl*irr) + ill*pow(irr,2) + ilr*irr*ivl - pow(irr,2)*ivl - ill*irr*ivr + irl*irr*ivr)*
                        (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)) +
                     (-(ihr*irl*irr) + ihl*pow(irr,2) + ihr*irr*ivl - pow(irr,2)*ivl - ihl*irr*ivr + irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr)))*
                (-((-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                          (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                       (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (-(ipr*irp*irr*ivl) + ipp*pow(irr,2)*ivl + ipr*irl*irr*ivp - ipl*pow(irr,2)*ivp - ipp*irl*irr*ivr + ipl*irp*irr*ivr))*
                     (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                          (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                       (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (imv*pow(irr,2)*ivl - imr*irr*irv*ivl - imv*irl*irr*ivr + iml*irr*irv*ivr + imr*irl*irr*ivv - iml*pow(irr,2)*ivv))) +
                  (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr))*
                   (-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                        (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (ipv*pow(irr,2)*ivl - ipr*irr*irv*ivl - ipv*irl*irr*ivr + ipl*irr*irv*ivr + ipr*irl*irr*ivv - ipl*pow(irr,2)*ivv))))/
             ((((ipr*irl*irr*ivh - ipl*pow(irr,2)*ivh - ipr*irh*irr*ivl + iph*pow(irr,2)*ivl + ipl*irh*irr*ivr - iph*irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                     (ilr*irl*irr*ivh - ill*pow(irr,2)*ivh - ilr*irh*irr*ivl + ilh*pow(irr,2)*ivl + ill*irh*irr*ivr - ilh*irl*irr*ivr)*
                      (-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr)) -
                  ((imr*irl*irr*ivh - iml*pow(irr,2)*ivh - imr*irh*irr*ivl + imh*pow(irr,2)*ivl + iml*irh*irr*ivr - imh*irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                     (ilr*irl*irr*ivh - ill*pow(irr,2)*ivh - ilr*irh*irr*ivl + ilh*pow(irr,2)*ivl + ill*irh*irr*ivr - ilh*irl*irr*ivr)*
                      (-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr))*
                   (-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(ipr*irp*irr*ivl) + ipp*pow(irr,2)*ivl + ipr*irl*irr*ivp - ipl*pow(irr,2)*ivp - ipp*irl*irr*ivr + ipl*irp*irr*ivr)))*
                ((-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr))*
                   ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (ihv*pow(irr,2)*ivl - ihr*irr*irv*ivl - ihv*irl*irr*ivr + ihl*irr*irv*ivr + ihr*irl*irr*ivv - ihl*pow(irr,2)*ivv) -
                     (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                      (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) -
                  ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(ihr*irp*irr*ivl) + ihp*pow(irr,2)*ivl + ihr*irl*irr*ivp - ihl*pow(irr,2)*ivp - ihp*irl*irr*ivr + ihl*irp*irr*ivr) -
                     (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                      (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (imv*pow(irr,2)*ivl - imr*irr*irv*ivl - imv*irl*irr*ivr + iml*irr*irv*ivr + imr*irl*irr*ivv - iml*pow(irr,2)*ivv))) -
               (-(((imr*irl*irr*ivh - iml*pow(irr,2)*ivh - imr*irh*irr*ivl + imh*pow(irr,2)*ivl + iml*irh*irr*ivr - imh*irl*irr*ivr)*
                        (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr) -
                       (ilr*irl*irr*ivh - ill*pow(irr,2)*ivh - ilr*irh*irr*ivl + ilh*pow(irr,2)*ivl + ill*irh*irr*ivr - ilh*irl*irr*ivr)*
                        (-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr))*
                     ((-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (-(ihr*irp*irr*ivl) + ihp*pow(irr,2)*ivl + ihr*irl*irr*ivp - ihl*pow(irr,2)*ivp - ihp*irl*irr*ivr + ihl*irp*irr*ivr) -
                       (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr))) +
                  (-((ilr*irl*irr*ivh - ill*pow(irr,2)*ivh - ilr*irh*irr*ivl + ilh*pow(irr,2)*ivl + ill*irh*irr*ivr - ilh*irl*irr*ivr)*
                        (-(ihr*irm*irr*ivl) + ihm*pow(irr,2)*ivl + ihr*irl*irr*ivm - ihl*pow(irr,2)*ivm - ihm*irl*irr*ivr + ihl*irm*irr*ivr)) +
                     (ihr*irl*irr*ivh - ihl*pow(irr,2)*ivh - ihr*irh*irr*ivl + ihh*pow(irr,2)*ivl + ihl*irh*irr*ivr - ihh*irl*irr*ivr)*
                      (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr))*
                   (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr)))*
                (-((-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                          (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                       (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (-(ipr*irp*irr*ivl) + ipp*pow(irr,2)*ivl + ipr*irl*irr*ivp - ipl*pow(irr,2)*ivp - ipp*irl*irr*ivr + ipl*irp*irr*ivr))*
                     (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                          (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                       (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                        (imv*pow(irr,2)*ivl - imr*irr*irv*ivl - imv*irl*irr*ivr + iml*irr*irv*ivr + imr*irl*irr*ivv - iml*pow(irr,2)*ivv))) +
                  (-((-(imr*irm*irr*ivl) + imm*pow(irr,2)*ivl + imr*irl*irr*ivm - iml*pow(irr,2)*ivm - imm*irl*irr*ivr + iml*irm*irr*ivr)*
                        (-(ilr*irp*irr*ivl) + ilp*pow(irr,2)*ivl + ilr*irl*irr*ivp - ill*pow(irr,2)*ivp - ilp*irl*irr*ivr + ill*irp*irr*ivr)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (-(imr*irp*irr*ivl) + imp*pow(irr,2)*ivl + imr*irl*irr*ivp - iml*pow(irr,2)*ivp - imp*irl*irr*ivr + iml*irp*irr*ivr))*
                   (-((-(ipr*irm*irr*ivl) + ipm*pow(irr,2)*ivl + ipr*irl*irr*ivm - ipl*pow(irr,2)*ivm - ipm*irl*irr*ivr + ipl*irm*irr*ivr)*
                        (ilv*pow(irr,2)*ivl - ilr*irr*irv*ivl - ilv*irl*irr*ivr + ill*irr*irv*ivr + ilr*irl*irr*ivv - ill*pow(irr,2)*ivv)) +
                     (-(ilr*irm*irr*ivl) + ilm*pow(irr,2)*ivl + ilr*irl*irr*ivm - ill*pow(irr,2)*ivm - ilm*irl*irr*ivr + ill*irm*irr*ivr)*
                      (ipv*pow(irr,2)*ivl - ipr*irr*irv*ivl - ipv*irl*irr*ivr + ipl*irr*irv*ivr + ipr*irl*irr*ivv - ipl*pow(irr,2)*ivv))))) );




}


