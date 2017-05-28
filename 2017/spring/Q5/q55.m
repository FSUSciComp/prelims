clear all; close all; clc
%chebychef point interpolation from -1 to 1
x=[-1:0.01:1]';

fun= @(x) abs(x)+0.5*x-x^2;
%generate chebychef nodes
x0=cheb(100, -1, 1);
y0=x0;
for i=1:size(x0)
    y0(i,1)=fun(x0(i,1));
end
w=generatew( x0, 101 );          %generate w
y=lagrange(x, x0, y0, w, 101);   %using the given w for lagrange interpolation
plot(x,y,'.-');
hold;
fplot(fun, [-1 1]);