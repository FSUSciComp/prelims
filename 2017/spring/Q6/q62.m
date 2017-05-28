clear all; close all; clc

Tv=4.053427893898620693391286; %true value
x0=1.5;
h=zeros(13,1);
for n=2:14
   h(n-1, 1)=10^(-1*n); 
end
fun=@(x) exp(x)./(sqrt(sin(x).^3+cos(x).^3));
e=zeros(size(h));
for i=1:size(h);
   e(i,1)=abs((fun(x0+h(i,1))-fun(x0-h(i,1)))/(2*h(i,1))-Tv);     %centered difference method
end


figure;
ei=zeros(size(h));
for i=1:size(h);
   ei(i,1)=abs(imag(fun(x0+1i*h(i,1)))/h(i,1)-Tv);                %complex step derivative
end

loglog(h,e,h, ei,'*');                                            %loglog plot of result
