function [ result ] = fq1( w,theata )
%the function given in the question
    if w==theata;
        result=1/(2*(3*cos(theata)^2-4));
    else
        result=(cos(w)*cos(theata)+sin(w)*sin(theata)-1)/(4*(cos(w)-cos(theata))^2+(sin(w)-sin(theata))^2);
    end
end

