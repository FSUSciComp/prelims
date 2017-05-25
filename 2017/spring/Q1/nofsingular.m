function [ Sol ] = nofsingular( A ,k, N)
%calculate the number of singular value above tol
TOL=1e-12;
Sol=zeros(k,k);
dn=N/k;
for s=1:k
    for h=1:k
        S=svd(A(dn*(s-1)+1:dn*s, dn*(h-1)+1:dn*h));
        number=0;
        for i=1:dn
            if S(i)>TOL
                number=number+1;
            end
        end
        Sol(s,h)=number;
    end
end
end

