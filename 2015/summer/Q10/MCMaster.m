% Master Script
gam = [-0.2, -0.9];
n = logspace(3,6,4);

% Setting up the Functions
% And Computing the Integrals
for i = 1:length(gam)
	for j = 1:length(n)
		% Set up the Functions
		f = @(x) x.^gam(i);
		f2 = @(x) x.^(2*gam(i));
		% Compute the Integrals
		Int(i,j) = MCIntegral(f, n(j), [0,1]);
		Int2(i,j) = MCIntegral(f2, n(j), [0,1]);
		% Now Compute the Error
		E(i,j) = ((1/n(j))*Int2(i,j) - (1/n(j))*Int(i,j).^2)/n(j);
	end
end

% Computing and Plotting Expected Variances vs True Errors
Itru = @(g) 1./(g+1);
if 2*gam(2) < -1
	Itru2 = @(g,n) (1 - (1/n)*(1/n).^g)./(g+1);
else
	Itru2 = @(g,n) 1./((2*g)+1);
end
for i = 1:length(gam)
	for j = 1:length(n)
		E_tru(i,j) = abs(((1/n(j))*Itru2(gam(i),n(j)) - (1/n(j))*Itru(gam(i)).^2)/n(j));
	end
end

figure(1)
	loglog(n, E(1,:), '-or', n, E_tru(1,:), '-og', n, E(2,:), '--*r', n, E_tru(2,:), '--*g');
	legend('-0.2 Approx', '-0.2 True', '-0.9 Approx', '-0.9 True')
	xlabel('Number of Points')
	ylabel('Order of the Error')
	title('Plot of Estimated Error vs Analytical Error')
