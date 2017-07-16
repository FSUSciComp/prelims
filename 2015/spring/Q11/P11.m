function P11
clear all
clc
close all


A = [1  268.189  269.794
2  134.263  135.443
4  67.2803  71.7022
8   33.7778  33.9926]

hold all
plot(A(:,1), A(:,2), '-*')
plot(A(:,1), A(:,3),'-s')

c = [260, 130, 65, 32.5]

p = polyfit( A(:,1),  (A(:,2)+A(:,3))/2,1 )

x= 0:1:8


c = p(1) * x + p(2)

plot(x,c,'-.')

legend('Openmp', 'MPI','scaling line')
xlabel('number of core')
ylabel('time (s)')