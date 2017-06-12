function [ p ] = norm_pdf( x,u,sigma )
%NORM_PDF Summary of this function goes here
%   Detailed explanation goes here
    p=(1/(sqrt(2*pi)*sigma))*exp(-((u-x).^2)./(2*sigma^2));
end

