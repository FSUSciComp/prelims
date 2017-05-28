function [ dcdt ] = pred( t,v,r,K,a,b,c )
%implementation of the predator and prey ODE
    dcdt = zeros(2,1);
    x=v(1);
    y=v(2);
    dcdt(1)=x*(r-r*x/K-a*y);
    dcdt(2)=y*(-1*b+c*x);
    
end

