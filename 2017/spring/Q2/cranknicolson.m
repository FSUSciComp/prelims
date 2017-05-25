function [ut] = cranknicolson(  u, dt, nt, n, kx )
%the implementation of cranknicolson method
uf=fft(u);
funcn=@(dt ,w) (2-dt*w*w)./(2+dt*w*w);
for i=1:nt
    for k=1:n
        uf(k)=funcn(dt,kx(k))*uf(k);
    end
end
ut=ifft(uf);

end

