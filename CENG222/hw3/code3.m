alpha = 0.05;
epsilon = 0.005;
N = 0.25 * ( norminv( 1 - alpha / 2 ) /  epsilon ) ^ 2; %simulation size

total = 0;

for k = 1:N
	A = exprnd(1/2);
	B = normrnd(0,1);
	if B < 0
		B_abs = B * -1;
	end
	if B >= 0
		B_abs = B;
	end
	total = total + (A + 2*B)/(1+B_abs);
end

part_3 = total/N