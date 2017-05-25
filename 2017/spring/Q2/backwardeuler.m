function [ ut ] = backwardeuler( u, dt, nt, n, kx )
%the implementation of spectral backwardeuler
uf=fft(u);
funbe=@(dt ,w) 1./(1+dt*w*w);
for i=1:nt
    for k=1:n
        uf(k)=funbe(dt,kx(k))*uf(k);
    end
end
ut=ifft(uf);

end

