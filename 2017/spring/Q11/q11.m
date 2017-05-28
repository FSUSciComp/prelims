clear all; close all; clc

%maximum likelyhood curve

n=1;
k=1;
L=@(q) nchoosek(n,k).*q.^k.*(1-q).^(n-k);

figure;
fplot(L,[0 1]);

Likelihoodratio=L(0.5)/L(1)           %calculate likelyhood ratio

%bayes inference
alf=200
bet=200
fp=@(p) p.^(alf-1).*(1-p).^(bet-1);   %calculate the prior distribution
denominator=integral(fp, 0, 1);
prior=@(p) fp(p)/denominator;

figure
fplot(prior, [0 1]);

fun=@(p) p.^(alf).*(1-p).^(bet-1);   %calculate the posterior distribution
denominator=integral(fun, 0, 1);
posterior=@(p) fun(p)/denominator;
figure;

fplot(posterior,[0 1],'.-');
hold on;
fplot(prior, [0 1]);
hold off;

probability=integral(posterior, 0.45, 0.55)   %calculate the probability that the coin is fair