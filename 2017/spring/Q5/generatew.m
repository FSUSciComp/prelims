function [ w ] = generatew( x0, n )
%O(2) algorithm to generate w
    w=ones(n,1);
    for i=1:n
        for j=1:n
            if i~=j
                w(i)=w(i)/(x0(i)-x0(j));
            end
        end
    end

end

