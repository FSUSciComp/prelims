% Gauss-Laguerre
% question 3 in Spring 2014.
f = 1:1:10000;
order = 100;
a = 0; b = 1;
filename = 'result';
[x,w] = laguerre_rule ( order, a, b, filename );

nSize = length(f);
res = zeros(n,1);
for i=1:nSize
    fcn = feval(@func, x, f(i));
    res(i) = sum(w.* fcn)*f(i);
end

figure (1)
semilogx(f, res)


% appximation
% using B-spline package to approximate the noise data    
np = nSize; % number of smaple 
% space
xmin = 0;
xmax = 20;
xdataorg = f;
ydata = res;
xmin = min(f);
xmax = max(f);
xdata = (xdataorg-xmin) / (xmax-xmin); % transform to [0,1]
% bspline settings
nbin = 10; % bins
p = 3;  % order
m = p*2+nbin+1-1; % number of total knots
n = m - p - 1;  % n+1 = m-p : number of basis functions
% knot vector
xorg= linspace(xmin, xmax, nbin+1); % internal knots are fixed
x = (xorg-xmin) / (xmax-xmin); % transform to [0,1]
t = [ zeros(1, p) x ones(1, p) ];  % knot vector
%
A = zeros(np,n+1);  
for j=0:n
    A(:, j+1) = bspline_basis(j,p+1,t,xdata);
end
Y = (A'*A)\(A'*ydata); % coeff. Y
yS = A*Y;  % simulated results

% plot
figure (2)
semilogx(xdataorg, ydata)  % original data

hold all
% B-spline approximation
semilogx(xdataorg, yS, 'linewidth', 2)


xlabel('x')
ylabel('y')
set(gcf, 'color', 'w')

hold off



 
 
 
 
 
 





