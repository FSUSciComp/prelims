clear all; close all; clc

n=1024;
L=2*pi;
T=1;
nt=100;
dt=T/nt;
x=linspace(-L/2, L/2, n+1); 

x=x(1:n);
kx=(2*pi/L)*[0:n/2-1 -n/2:-1];


u=x;
for i=1:n
   x0=(i-1)*L/n-pi;
   if x0<-pi/2 ||x0>pi/2
       u(i)=1;
   else
       u(i)=0;
   end
end
%solve with backward euler
ut=backwardeuler( u, dt, nt, n, kx );
figure;
ut0=[ut(n/2+1:n) ut(1:n/2)];
xt=linspace(0, L, n+1); 
xt=xt(1:n);
plot(xt,ut0)

%solve with cranknicolson method
ut=cranknicolson( u, dt, nt, n, kx );
figure;
ut0=[ut(n/2+1:n) ut(1:n/2)];
xt=linspace(0, L, n+1); 
xt=xt(1:n);
plot(xt,ut0)

