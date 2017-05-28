function [ x ] = cheb( n, a, b )
%generate chebychef points for n order polynormial on region a to b
    x=zeros(n+1,1);
    for i=0: n
        x(i+1,1)=cos((2*i+1)*pi/(2*n+2));
    end
    x=(a+b)/2+(b-a)/2*x;
end

