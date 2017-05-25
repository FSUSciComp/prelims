clear all; close all; clc

n=1024;
L=2*pi;
T=1;
nt=10000;
dt=T/nt;
x=linspace(-L/2, L/2, n+1); 

x=x(1:n);
kx=(2*pi/L)*[0:n/2-1 -n/2:-1];


u=exp(cos(x));

ut=cranknicolson( u, dt, nt, n, kx ); %exact solution
figure;
ut0=[ut(n/2+1:n) ut(1:n/2)];
xt=linspace(0, L, n+1); 
xt=xt(1:n);
plot(xt,ut0)

format long;
%convergence analysis for backward euler
nt=100;
dt=T/nt
ut1=backwardeuler( u, dt, nt, n, kx );
errornorm1=norm(ut1- ut)

nt=200;
dt=T/nt
ut2=backwardeuler( u, dt, nt, n, kx );
errornorm2=norm(ut2- ut)

nt=400;
dt=T/nt
ut3=backwardeuler( u, dt, nt, n, kx );
errornorm3=norm(ut3- ut)

nt=800;
dt=T/nt
ut4=backwardeuler( u, dt, nt, n, kx );
errornorm4=norm(ut4- ut)


 convergencerate1=log(errornorm2/errornorm1)/log(1/2)
 convergencerate2=log(errornorm3/errornorm2)/log(1/2)
 convergencerate3=log(errornorm4/errornorm3)/log(1/2)
%convergence analysis for crank niconson
nt=100;
dt=T/nt
utc1=cranknicolson( u, dt, nt, n, kx );
errornorm1=norm(utc1- ut)

nt=200;
dt=T/nt
utc2=cranknicolson( u, dt, nt, n, kx );
errornorm2=norm(utc2- ut)

nt=400;
dt=T/nt
utc3=cranknicolson( u, dt, nt, n, kx );
errornorm3=norm(utc3- ut)

nt=800;
dt=T/nt
utc4=cranknicolson( u, dt, nt, n, kx );
errornorm4=norm(utc4- ut)

 convergencerate1=log(errornorm2/errornorm1)/log(1/2)
 convergencerate2=log(errornorm3/errornorm2)/log(1/2)
 convergencerate3=log(errornorm4/errornorm3)/log(1/2)