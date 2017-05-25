clear all; close all; clc

N=128;
A=zeros(N,N);
dthe=2*pi/N;
%generate A
for i=1:N
    for j=1:N
        A(i, j)=fq1(i*dthe, j*dthe);
    end
end
% b)
A
%figure 1 plot a
 figure;
 colormap('hot');   % set colormap
 imagesc([1, N], [1, N], A);        % draw image and scale colormap to values range
 colorbar;          % show color scale
 
%figure 2
%plot 10th and 50th columns together with diagonal entry
figure;
plot([1:1:N],A(:,10),[1:1:N],A(:,50),10, A(10, 10),'*',50, A(50, 50),'*')

%check if A is symmetric
if norm(A'-A)==0
    fprintf('A is symmetric\n');
else
    fprintf('A is NOT symmetric\n');
end

% c) calculate the rank of different grid size
N=2048
A=zeros(N,N);
dthe=2*pi/N;
%generate A
for i=1:N
    for j=1:N
        A(i, j)=fq1(i*dthe, j*dthe);
    end
end
grid2=nofsingular(A,2,N)
grid4=nofsingular(A,4,N)
grid8=nofsingular(A,8,N)
%N=4096
N=N*2
A=zeros(N,N);
dthe=2*pi/N;
%generate A
for i=1:N
    for j=1:N
        A(i, j)=fq1(i*dthe, j*dthe);
    end
end
grid2=nofsingular(A,2,N)
grid4=nofsingular(A,4,N)
grid8=nofsingular(A,8,N)
%N=8192
N=N*2
A=zeros(N,N);
dthe=2*pi/N;
%generate A
for i=1:N
    for j=1:N
        A(i, j)=fq1(i*dthe, j*dthe);
    end
end
grid2=nofsingular(A,2,N)
grid4=nofsingular(A,4,N)
grid8=nofsingular(A,8,N)