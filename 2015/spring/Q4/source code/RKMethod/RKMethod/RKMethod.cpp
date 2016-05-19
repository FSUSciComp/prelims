// RichardsonMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "..\RKlib\RKlib.h"

using namespace std;

//Function: f(t,y) or y'(t)
double fDetriFunc(double t, double y)
{
	return -exp(-t)+40000*exp(-10000*t);
}
//Function: y(t)
double fExactFunc(double t, double y)
{
	return exp(-t)+exp(1.0)-4*exp(-10000*t);
}
double Calc(int index, double t0, double y0, double deltaT, double T)
{
	double fResult = 0;
	RKM::RKMethod rk;	
	switch(index)
	{
	case 1:
		rk.InitCoeff(RKM::RKMethod::ForwardEuler);
		break;
	case 21:
		rk.InitCoeff(RKM::RKMethod::MidPoint);
		break;
	case 22:
		rk.InitCoeff(RKM::RKMethod::Heun_Method);
		break;
	case 3:
		rk.InitCoeff(RKM::RKMethod::Stage_3_Method);
		break;
	case 4:
		rk.InitCoeff(RKM::RKMethod::Stage_4_Method);
		break;
	case 6:
		rk.InitCoeff(RKM::RKMethod::Stage_6_Method);
		break;
	default:
		break;
	}
	rk.InitFunc(&fDetriFunc);

	char * strLog = NULL;
	bool bRes = rk.Run(t0, y0, deltaT, T, fResult, strLog);
	printf("%s\n", strLog);
	return fResult;
}
//
int _tmain(int argc, _TCHAR* argv[])
{
	int index = 1;// stage index
	double t0 = 0;
	double y0 = exp(1.0)-3;
	double T = 1;
	double fExact = fExactFunc(T,0);
	double fDeltaT[6];
	double fScale = 1000.0;
	for(int i=0; i<6; ++i)
	{
		fDeltaT[i] = (1.0)/(pow(2.0,i)*fScale);
	}

	double fValue[6]={0};
	double fErro[6]={0};
	double fRate[6]={0};
	for (int i=0; i<6; ++i)
	{
		double fResult = 0.0;
		fResult = Calc(index, t0, y0, fDeltaT[i], T);
		fValue[i] = fResult;
		fErro[i] = fabs(fResult-fExact);
	}
	for (int i=1; i<6; ++i)
	{
		fRate[i] = log(fErro[i-1]/fErro[i])/log(2.0);
	}
	ofstream outFile("report06.txt", ios::out);
	if (!outFile.is_open())
		return false;

	outFile.precision(8);
	outFile.setf(std::ios::fixed, std::ios::floatfield);
	//output methods
	switch (index)
	{
	case 1:
		outFile<<"Using the Forward Euler method to get x:"<<endl;
		break;
	case 12:
		outFile<<"Using the Backward Euler method to get x:"<<endl;
		break;
	case 21:
		outFile<<"Using the Midpoint method to get x:"<<endl;
		break;
	case 22:
		outFile<<"Using the Heun's method to get x:"<<endl;
		break;
	case 3:
		outFile<<"Using the Stage-3 RK method to get x:"<<endl;
		break;
	case 4:
		outFile<<"Using the Stage-4 RK method to get x:"<<endl;
		break;
	case 6:
		outFile<<"Using the Stage-6 RK method to get x:"<<endl;
		break;
	}
	outFile<<"DeltaT     Value     Error    Rate"<<endl;
	for (int i=0; i<6; ++i)
	{
		outFile<<fDeltaT[i]<<"   "<<fValue[i]<<"   "<<fErro[i]<<"   "<<fRate[i]<<endl;
	}
	outFile<<endl;
	outFile.close();

	return 0;
}





