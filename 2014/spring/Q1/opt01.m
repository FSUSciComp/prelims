clear all; close all; clc
%bfgs exact line search
A=[4 2; 2 2];
b=[-1; 1];
B=[1 0; 0 1];
eig(A)
x=[0; 0];

for i=0:2
   p= -1.*inv(B)*(A*x-b);
   af=p'*(b-A*x)/(p'*A*p);
   s=af*p;
   temp=x+s;
   y=(A*temp-b)-(A*x-b);
   B=B-(B*s)*s'*B/(s'*B*s)+y*y'/(y'*s);
   x=temp;
    x
end
