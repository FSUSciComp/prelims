// RKlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RKlib.h"
#include <stdlib.h>
#include <math.h>

////////////////////////////////////////////////
namespace RKM
{

#define MAX_BOUND		1e10
#define ERROR_ACCURACY	1e-4

RKMethod::RKMethod()
{
	m_iStage = 0;
	
	m_FuncYPrime = NULL;
	m_FuncYExact = NULL;
	m_A = NULL;
	m_B = NULL;
	m_C = NULL;
}

RKMethod::~RKMethod()
{
	m_FuncYPrime = NULL;
	m_FuncYExact = NULL;

	delete [] m_A;
	delete [] m_B;
	delete [] m_C;
}

void RKMethod::AllocateArray(int iStage)
{
	if (iStage < 1)
		return;

	m_iStage = iStage;

	m_A = new double[m_iStage*m_iStage];
	memset(m_A, 0, m_iStage*m_iStage*sizeof(double));

	m_B = new double[m_iStage];
	memset(m_B, 0, m_iStage*sizeof(double));

	m_C = new double[m_iStage];
	memset(m_C, 0, m_iStage*sizeof(double));

}
//forward euler
void RKMethod::InitCoeff_FE()
{
	AllocateArray(1);

	m_A[0] = 0.0;
	m_C[0] = 0.0;
	m_B[0] = 1.0;
}
//midpoint method
void RKMethod::InitCoeff_MidPoint()
{
	AllocateArray(2);

	m_A[2] = 1.0/2.0;
	m_C[1] = 1.0/2.0;
	m_B[1] = 1.0;
}
//heun's method
void RKMethod::InitCoeff_Heun()
{
	AllocateArray(2);

	m_A[2] = 2.0/3.0;
	m_C[1] = 2.0/3.0;
	
	m_B[0] = 1.0/4.0;
	m_B[1] = 3.0/4.0;
}
//stage 3 of RK method
void RKMethod::InitCoeff_Stage_3()
{
	AllocateArray(3);

	m_A[3] = 1.0/2.0;
	m_A[6] = -1.0;
	m_A[7] = 2.0;

	m_C[1] = 1.0/2.0;
	m_C[2] = 1.0;

	m_B[0] = 1.0/6.0;
	m_B[1] = 2.0/3.0;
	m_B[2] = 1.0/6.0;
}
//RK_4 using '3/8' Rule
void RKMethod::InitCoeff_Stage_4()
{
	AllocateArray(4);

	m_A[4] = 1.0/3.0;
	m_A[8] = -1.0/3.0;
	m_A[9] = 1.0;
	m_A[12] = 1.0;
	m_A[13] = -1.0;
	m_A[14] = 1.0;

	m_C[1] = 1.0/3.0;
	m_C[2] = 2.0/3.0;
	m_C[3] = 1.0;

	m_B[0] = 1.0/8.0;
	m_B[1] = 3.0/8.0;
	m_B[2] = 3.0/8.0;
	m_B[3] = 1.0/8.0;
}
//The Runge¨CKutta¨CFehlberg method (stage 6)
void RKMethod::InitCoeff_Stage_6()
{
	AllocateArray(6);
	
	m_A[6] = 1.0/4.0;
	m_A[12] = 3.0/32.0;
	m_A[13] = 9.0/32.0;
	m_A[18] = 1932.0/2197.0;
	m_A[19] = -7200.0/2197.0;
	m_A[20] = 7296.0/2197.0;
	m_A[24] = 439.0/216.0;
	m_A[25] = -8.0;
	m_A[26] = 3680.0/513.0;
	m_A[27] = -845.0/4104.0;
	m_A[30] = -8.0/27.0;
	m_A[31] = 2.0;
	m_A[32] = -3544.0/2565.0;
	m_A[33] = 1859.0/4104.0;
	m_A[34] = -11.0/40.0;

	m_C[1] = 1.0/4.0;
	m_C[2] = 3.0/8.0;
	m_C[3] = 12.0/13.0;
	m_C[4] = 1.0;
	m_C[5] = 1.0/2.0;

	m_B[0] = 16.0/135.0;
	m_B[1] = 0.0;
	m_B[2] = 6656.0/12825.0;
	m_B[3] = 28561.0/56430.0;
	m_B[4] = -9.0/50.0;
	m_B[5] = 2.0/55.0;
}
//
void RKMethod::InitCoeff( RK_Method rk )
{
	switch(rk)
	{
	case ForwardEuler:
		InitCoeff_FE();
		break;
	case MidPoint:
		InitCoeff_MidPoint();
		break;
	case Heun_Method:
		InitCoeff_Heun();
		break;
	case Stage_3_Method:
		InitCoeff_Stage_3();
		break;
	case Stage_4_Method:
		InitCoeff_Stage_4();
		break;
	case Stage_6_Method:
		InitCoeff_Stage_6();
		break;
	default:
		break;
	}
}


/* iStage is the stage of RK method
*  A[iStage*iStage], B[iStage], C[iStage]
*/
void RKMethod::InitCoeff( int iStage, double *A, double *B, double *C )
{
	AllocateArray(iStage);

	for (int i=0; i<iStage; ++i)
	{
		for (int j=0; j<iStage; ++j)
		{
			m_A[i*iStage+j] = A[i*iStage+j];
		}
		m_B[i] = B[i];
		m_C[i] = C[i];
	}
}
//check the coefficients
bool RKMethod::CheckCoefficient()
{
	double fSumB = 0.0;
	for (int i=0; i< m_iStage; ++i)
	{
		double fSumA1=0.0;
		for (int j=0; j< m_iStage; ++j)
		{
			fSumA1 += m_A[i*m_iStage+j];
		}
		if (fabs(fSumA1-m_C[i]) > ERROR_ACCURACY )
			return false;

		fSumB += m_B[i];
	}

	if (fabs(fSumB-1.0) > ERROR_ACCURACY )
		return false;

	return true;
}
//
double RKMethod::CalcOneStep(double tCurr, double tDelta, double yCurr)
{
	double *k = (double *)malloc(m_iStage*sizeof(double));
	double ySum = 0;
	for (int i=0; i<m_iStage; ++i)
	{
		double yTemp = 0;
		for (int j=0; j<i; ++j)
		{
			yTemp += m_A[i*m_iStage+j]*k[j];
		}
		k[i] = tDelta*m_FuncYPrime(tCurr+m_C[i]*tDelta, yCurr+yTemp);

		ySum += m_B[i] * k[i];
	}
	return yCurr+ySum;
}
//
bool RKMethod::Calc(double &fResult, char *&strLog)
{
	double yCurr = m_fY0;
	int k = (int)(0.5+(m_tT-m_tT0)/m_tDeltaT);//loop number
	double fRemainder = m_tT - m_tT0 - k*m_tDeltaT;
	for (int i=0; i<k; ++i)
	{
		double tCurr = m_tT0+i*m_tDeltaT;
		yCurr = CalcOneStep(tCurr, m_tDeltaT, yCurr );

		if (i == k-1 && fRemainder > 0)
		{//need one more step
			yCurr = CalcOneStep(tCurr+m_tDeltaT, fRemainder, yCurr );
		}

		if (yCurr > MAX_BOUND)
		{
			strLog = "The solution becomes unbounded!";
			fResult = yCurr;
			return false;
		}
	}
	strLog = "The solution has been computed successfully!";
	fResult = yCurr;
	return true;
}
//check validation
bool RKMethod::CheckSettings(char *&strLog)
{
	if (m_iStage < 1)
	{
		strLog = "No R-K method selected or set!";
		return false;
	}
	if (m_FuncYPrime == NULL)
	{
		strLog = "Cannot find the function 'f(t,y)'!";
		return false;
	}
	if (!CheckCoefficient())
	{
		strLog = "Errors in the coefficients!";
		return false;
	}
	return true;
}
//
bool RKMethod::Run( double t0, double y0, double deltaT, double T, double &fResult, char *&strLog )
{
	//check settings
	bool bRes = CheckSettings(strLog);
	//
	m_tT0 = t0;
	m_fY0 = y0;
	m_tT = T;
	m_tDeltaT = deltaT;

	bRes = bRes && Calc(fResult, strLog);

	return bRes;
}


}

