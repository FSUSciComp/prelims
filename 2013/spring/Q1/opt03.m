clear all; close all; clc

r=1; la=0;

n=2;
for i=1:n
   x1=(10*r-la)/(28+10*r);
   x2=4*x1;
   r=2*r;
   la=la+2*r*(x1+x2-5);
end
x1
x2
h=x1+x2-5