// ExRKMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "..\ExRKlib\ExRKlib.h"

using namespace std;

#pragma warning(disable: 4244)

#define  N_1 3//length of vector in problem 1
#define  N_2 2//length of vector in problem 2: a, v
#define  N_3A 5//length of vector in problem 3a: v1, a1, v2, a2, g
#define  N_3B 7//length of vector in problem 3b: v1, a1, v2, a2, v3, a3, g

typedef  void (*YFunc)(double, double*, double*); //f(t,y)

double p = 0.1;//p starting at 0.1 and decreasing by 0.01

//Function: f(t,y) or y'(t)
//in problem 1
void fDetriFunc1(double t, double *w, double *f)
{
	f[0] = 2*w[1] - 4*t;
	f[1] = -w[0] + w[2] - exp(t) + 2.0;
	f[2] = w[0] - 2*w[1] + w[2] + 4*t;
}
//in problem 2
void fDetriFunc2(double t, double *w, double *f)
{//w0, w1 represents a, v respectly.
	f[0] = 0.025*w[1];//a
	f[1] = 0.15*w[1] - p*w[1]*w[0];//v
}
//in problem 3
void fDetriFunc3a(double t, double *w, double *f)
{//w0, w1, w2, w3, w4 represents v1, a1, v2, a2, g respectly.
// 	double k=0.1;
// 	double r = 0.5;
// 	double p = 0.5;
// 	double s = 0.25;
// 	double u = 0.1;

	f[0] = w[0]*(0.5 - 0.25*w[4] - 0.5*w[1]);//v1
	f[1] = 0.1*w[0] - 0.1*w[1]*(w[0]+w[2]);//a1
	f[2] = w[2]*(0.5 - 0.25*w[4] - 0.5*w[3]);//v2
	f[3] = 0.1*w[2] - 0.1*w[3]*(w[0]+w[2]);//a2
	f[4] = (0.1-0.1*w[4])*(w[0]+w[2]);//g
}
void fDetriFunc3b(double t, double *w, double *f)
{//w0, w1, w2, w3, w4 w5 w6 represents v1, a1, v2, a2, v3, a3, g respectly.
// 	double k=0.1;
// 	double r = 0.5;
// 	double p = 0.5;
// 	double s = 0.25;
// 	double u = 0.1;

	f[0] = w[0]*(0.5 - 0.25*w[6] - 0.5*w[1]);//v1
	f[1] = 0.1*w[0] - 0.1*w[1]*(w[0]+w[2]+w[4]);//a1
	f[2] = w[2]*(0.5 - 0.25*w[6] - 0.5*w[3]);//v2
	f[3] = 0.1*w[2] - 0.1*w[3]*(w[0]+w[2]+w[4]);//a2
	f[4] = w[4]*(0.5 - 0.25*w[6] - 0.5*w[5]);//v3
	f[5] = 0.1*w[4] - 0.1*w[5]*(w[0]+w[2]+w[4]);//a3
	f[6] = (0.1-0.1*w[6])*(w[0]+w[2]+w[4]);//g
}
//Function: y(t)
void fExactFunc1(double t, double *w)
{
	w[0] = -cos(2*t);
	w[1] = sin(2*t)+2*t;
	w[2] = cos(2*t)+exp(t);
}
//
bool Calc(int stage, YFunc func, int nLength, double t0, double *y0, double deltaT, double T, double *fResult, char *&strLog)
{
	ExRKM::ExRKMethod rk;
	switch(stage)
	{
	case 1:
		rk.InitCoeff(ExRKM::ExRKMethod::ForwardEuler);
		break;
	case 2:
		rk.InitCoeff(ExRKM::ExRKMethod::MidPoint);
		break;
// 	case 2:
// 		rk.InitCoeff(ExRKM::ExRKMethod::Heun_Method);
// 		break;
	case 3:
		rk.InitCoeff(ExRKM::ExRKMethod::Stage_3_Method);
		break;
	case 4:
		rk.InitCoeff(ExRKM::ExRKMethod::Stage_4_Method);
		break;
	case 5:
		rk.InitCoeff(ExRKM::ExRKMethod::Stage_6_Method);
		break;
	default:
		break;
	}
	rk.InitFunc(func);

	return rk.Run(nLength, t0, y0, deltaT, T, fResult, strLog);
}
double CalcErr(int n, double *fValue, double *fExact)
{
	double fRes = 0.0;
	for (int l=0; l<n; ++l)
	{
		fRes += (fValue[l] - fExact[l])*(fValue[l] - fExact[l]);
	}
	return sqrt(fRes);
}
void ExRKMethod1()
{
	double t0 = 0;
	double y0[N_1] = {-1,0,2};
	double T = 10;
	double fExact[N_1];
	fExactFunc1(T, fExact);
	double fDeltaT[5];
	double fScale = 10.0;
	int nStep=5;
	for(int i=0; i<nStep; ++i)
	{
		fDeltaT[i] = (1.0)/(pow(2.0,i)*fScale);
	}

	for (int s=1; s<=5; ++s)
	{
		double fErro[5]={0};
		double fRate[5]={0};
		for (int i=0; i<nStep; ++i)
		{
			double fResult[N_1] = {0.0};
			char *log = NULL;
			bool bRes = Calc(s, &fDetriFunc1, N_1, t0, y0, fDeltaT[i], T, fResult, log);
			fErro[i] = CalcErr(N_1, fResult,fExact);
		}
		for (int i=1; i<nStep; ++i)
		{
			fRate[i] = log(fErro[i-1]/fErro[i])/log(2.0);
		}
		printf("\nStage  %d\n", s);
		printf("Error    Rate\n", s);
		for (int i=0; i<nStep; ++i)
		{
			printf("%.3e   %.3e\n", fErro[i], fRate[i]);
		}
	}
}
void ExRKMethod2a()
{
	ofstream outFile("t-a-v.txt", ios::out);
	if (!outFile.is_open())
		return ;

	outFile.precision(8);
	outFile.setf(std::ios::fixed, std::ios::floatfield);
	outFile<<"T(hours)          a		  v"<<endl;

	double t0 = 0;
	double y0[N_2] = {0,0.01};
	double T = 4*24;
	double fDeltaT=0.25;
	int nStep= (T-t0)/fDeltaT;
	for(int i=0; i<=nStep; ++i)
	{
		double fCurrT = t0+i*fDeltaT;
		double fResult[N_2] = {0.0};
		char *log = NULL;
		bool bRes = Calc(4, &fDetriFunc2, N_2, t0, y0, fDeltaT, fCurrT, fResult, log);
		if (bRes)
		{
			outFile<<fCurrT<<"   "<<fResult[0]<<"   "<<fResult[1]<<endl;
		}
	}
	outFile.close();
}
void ExRKMethod2b()
{
	int k = 0;
	double t0 = 0;
	double y0[N_2] = {0,0.01};
	double T = 4*24;
	double fDeltaT=0.25;
	int nStep= (T-t0)/fDeltaT;

	bool bContinue = true;
	while (bContinue)
	{
		std::string str = std::string("p-t-v-")+std::to_string((unsigned long long)k)+".txt";
		ofstream outFile(str.c_str(), ios::out);
		if (!outFile.is_open())
			return ;

		outFile.precision(8);
		outFile.setf(std::ios::fixed, std::ios::floatfield);
		outFile<<"p : "<<p<<endl;
		outFile<<"T(hours)            v"<<endl;
		for(int i=0; i<=nStep; ++i)
		{
			double fCurrT = t0+i*fDeltaT;
			double fResult[N_2] = {0.0};
			char *log = NULL;
			bool bRes = Calc(4, &fDetriFunc2, N_2, t0, y0, fDeltaT, fCurrT, fResult, log);
			if (bRes)
			{
				outFile<<fCurrT<<"   "<<fResult[1]<<endl;
			}
			if (fResult[1] > 20)
				bContinue = false;
		}	
		outFile.close();

		++k;
		p -= 0.01;
	}
}

void ExRKMethod3a()
{
	ofstream outFile("t-v1-v2-a1-a2-g.txt", ios::out);
	if (!outFile.is_open())
		return ;

	outFile.precision(8);
	outFile.setf(std::ios::fixed, std::ios::floatfield);
	outFile<<"T(hours)		v1	  v2	   a1	 a2 	g"<<endl;

	double t0 = 0;
	double y0[N_3A] = {0.01, 0, 0, 0, 0};
	double T = 100;
	double tV2 = 10;
	double yV2[N_3A] = {0.0, 0, 0.0001, 0, 0};
	double fDeltaT=0.25;
	int nStep= (T-t0)/fDeltaT+0.5;
	int iStepV2 = (tV2-t0)/fDeltaT+0.5;
	for(int i=0; i<=nStep; ++i)
	{
		double fCurrT = t0+i*fDeltaT;
		double fResult[N_3A] = {0.0};
		char *log = NULL;
		bool bRes = (i <= iStepV2) ? Calc(4, &fDetriFunc3a, N_3A, t0, y0, fDeltaT, fCurrT, fResult, log)
								  : Calc(4, &fDetriFunc3a, N_3A, tV2, yV2, fDeltaT, fCurrT, fResult, log);
		
		if (i == iStepV2)//v2 appears 
		{
			fResult[2] = 0.0001;
			memcpy(yV2, fResult, N_3A*sizeof(double));
		}

		if (bRes)
		{
			outFile<<fCurrT<<"   "<<fResult[0]<<"   "<<fResult[2]\
			<<"   "<<fResult[1]<<"   "<<fResult[3]<<"   "<<fResult[4]<<endl;
		}

		if (fResult[0]+fResult[2] > 20)
			break;
	}
	outFile.close();
}
void ExRKMethod3b()
{
	ofstream outFile("t-v1-v2-v3-a1-a2-a3-g.txt", ios::out);
	if (!outFile.is_open())
		return ;

	outFile.precision(8);
	outFile.setf(std::ios::fixed, std::ios::floatfield);
	outFile<<"T(hours)		v1	 v2	v3	a1	a2	a3	g"<<endl;

	double t0 = 0;
	double y0[N_3B] = {0.01, 0, 0, 0, 0, 0, 0};
	double T = 100;
	double tV2 = 10;
	double yV2[N_3B] = {0.0, 0, 0.0001, 0, 0, 0, 0};
	double tV3 = 20;
	double yV3[N_3B] = {0.0, 0, 0.0, 0, 0.00001, 0, 0};
	double fDeltaT=0.25;
	int nStep= (T-t0)/fDeltaT+0.5;
	int iStepV2 = (tV2-t0)/fDeltaT+0.5;
	int iStepV3 = (tV3-t0)/fDeltaT+0.5;
	for(int i=0; i<=nStep; ++i)
	{
		double fCurrT = t0+i*fDeltaT;
		double fResult[N_3B] = {0.0};
		char *log = NULL;
		bool bRes =true;
		if (i <= iStepV2)
			bRes = Calc(4, &fDetriFunc3b, N_3B, t0, y0, fDeltaT, fCurrT, fResult, log);
		else if (i <= iStepV3)
			bRes = Calc(4, &fDetriFunc3b, N_3B, tV2, yV2, fDeltaT, fCurrT, fResult, log);
		else
			bRes = Calc(4, &fDetriFunc3b, N_3B, tV3, yV3, fDeltaT, fCurrT, fResult, log);
		
		if (i == iStepV2)//v2 appears 
		{
			fResult[2] = 0.0001;
			memcpy(yV2, fResult, N_3B*sizeof(double));
		}
		if (i == iStepV3)//v3 appears 
		{
			fResult[4] = 0.00001;
			memcpy(yV3, fResult, N_3B*sizeof(double));
		}

		if (bRes)
		{
			outFile<<fCurrT<<"   "<<fResult[0]<<"   "<<fResult[2]<<"   "<<fResult[4]\
				<<"   "<<fResult[1]<<"   "<<fResult[3]<<"   "<<fResult[5]<<"   "<<fResult[6]<<endl;
		}

		if (fResult[0]+fResult[2] + fResult[4] > 20)
			break;		
	}
	outFile.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//ExRKMethod1();
	//ExRKMethod2a();
	//ExRKMethod2b();
	//ExRKMethod3a();
	ExRKMethod3b();

	system("pause");
	return 0;
}

