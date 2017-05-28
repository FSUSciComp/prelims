function [ y ] = lagrange( x, x0, y0, w, n ) %x0, y0 are points, n is data size
%evaluating the function value at certain given x values and w
    y=x;    
    for i=1:size(x)
        result=1;
        for j=1:n
           result=result*(x(i)-x0(j)); 
        end
        temp=0;
        for j=1:n
           temp=temp+w(j)/(x(i)-x0(j))*y0(j); 
        end
        result=result*temp;
        y(i)=result;
    end

end