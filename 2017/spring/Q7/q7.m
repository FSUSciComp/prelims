clear all; close all; clc

%find the exact solution using symbolic tool box
syms x y
I = int (int(exp(-10*y^2), -inf,x)*exp(10*x^2),x,0,1);
Iexact = double(I);

Iexact

%estimate I using Quadrature
xk=zeros(5);
yk=xk;
for k=1:5
    m=25*2^k;
    n=25*2^k;
    xk(k)=m;
    [y, w]=gausslaguerre(n, 0);
    [x, r]=gausslegendre(m, -1, 1);
    fun= @(x,y) 0.5.*exp(10.*(0.5.*x+0.5).^2)*exp(y-10.*(y-(0.5.*x+0.5)).^2);

    solution=0;
    for i=1:n
        for j=1:m
            solution=solution+w(i)*r(j)*fun(x(j),y(i));
        end
    end

    yk(k)=solution;

end
semilogx(xk, yk);
axis([0 1000 654 656]);
Iest=yk(3);
Iest
