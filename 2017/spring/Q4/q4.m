close all; clear all; clc

%3) case 3 solve for eigenvalue of J
syms r a b c k
J=[-1*r*b/c/k, -1*a*b/c; r*c/a-r*b/a/k,0];
eigenvalue=eig(J)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%4) 
r=1;
K=0.5;
a=1;
b=1;
c=1;
options = odeset('RelTol',1e-6);%the accuracy was setted as 10^-6
tspan = [0 50];

%case 1
c0 = [0 10];
                               
tic;
[t,sol] = ode45(@(t,v) pred( t,v,r,K,a,b,c ), tspan, c0, options);   %ode45 was used as the ode solver

wtime=toc;                                                     %calculate computational time

fprintf ( 1, 'Case 1 Elapsed time = %f\n', wtime );
figure;
plot(t,sol(:,1),'b',t,sol(:,2),'r');


%case 2
c0 = [2 2];
                              
tic;
[t,sol] = ode45(@(t,v) pred( t,v,r,K,a,b,c ), tspan, c0, options);   %ode45 was used as the ode solver

wtime=toc;                                                     %calculate computational time

fprintf ( 1, 'Case 2 Elapsed time = %f\n', wtime );
figure;
plot(t,sol(:,1),'b',t,sol(:,2),'r');

%case 3
K=2;
c0 = [2 2];
                               
tic;
[t,sol] = ode45(@(t,v) pred( t,v,r,K,a,b,c ), tspan, c0, options);   %ode45 was used as the ode solver

wtime=toc;                                                     %calculate computational time

fprintf ( 1, 'Case 3 Elapsed time = %f\n', wtime );
figure;
plot(t,sol(:,1),'b',t,sol(:,2),'r');