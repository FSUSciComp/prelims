close all; clear all; clc
%initialize
A=[4 5 4 7 5 7 4; 6 8 5 8 8 11 6; 5 7 5 9 9 10 7; 6 8 5 8 9 11 7; 4 3 2 3 4 7 3; 4 6 5 8 8 8 6; 1 3 3 5 5 5 4; 5 6 6 8 8 9 7];
r=7;
m=8;
n=7;
TOL=0.01;
[U, S, V]= svd(double(A)); %svd on A

term2=0;                                         %calculate denominator in error estimation
for i=1:r
    term2=term2+S(i, i)^2;
end

for p=1:r                                          %calculate smallest p
    term1=0;
  
    for i=(p+1):r
        term1=term1+S(i, i)^2;
    end

    RelativeError2=sqrt(term1/term2);
    
    if (RelativeError2<TOL)                           %break the loop untill the relative error smaller than 0.01
        break;
    end
end

p

Approx=zeros(m,n);                          %display the approximation
for n=1:p
    Approx=Approx+U(: , n)*V(: , n)'*S(n , n);
end
Approx