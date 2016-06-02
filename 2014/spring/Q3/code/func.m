function res = func(t, f)

res = exp(-t).^(f-2);
res1 = erf(sqrt(t)).^(f-1);
res2 = (exp(-t).*erf(sqrt(t))).^(f-1) ./ exp(-t);
res = res.*res1;
if abs(res2-res) > 1e-3
    a = 3;
end

end
