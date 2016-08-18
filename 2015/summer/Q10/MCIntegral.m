function [Int] = MCIntegral(f, n, bounds)
	% Synopsis: Takes in a function and its integration
	%			parameters and returns the integral
	%
	% Inputs: f = an inline function to integrate
	%		  bounds = a vector with the bounds of integration
	%		  n = number of points to use
	%
	% Ouputs: Int = the estimated value of the integral
	
	% Bounds and Random Samplings
	B = bounds;
	R = rand(length(B)/2, n);
	
	% Move Random Samples so that they are in the correct
	% Bounds for each integral
	R(1,:) = (B(2)-B(1))*R(1,:)+B(1);
	if length(B) >= 4
		for i = 2:length(B)
			R(i,:) = R(i,:)*(B(2*i) - B(2*i-1)) + B(2*i-1);
		end
	end
	
	% Compute the Volume of the Domain
	V = B(2) - B(1);
	if length(B) >= 4
		for i = 4:2:length(B)
			V = V * (B(i) - B(i-1));
		end
	end
	
	% Evaluate the Function at all Random Points
	s = f(R');

	% Compute the Sum of all Evaluation
	T = sum(s);

	% Compute the E[f] and the Integral Value
	E_f = T./n;
	Int = E_f*V;
end
