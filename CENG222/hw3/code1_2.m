%Adil Kaan Akan
%2171155

% part1



alpha = 0.05;
epsilon = 0.005;
N = 0.25 * ( norminv( 1 - alpha / 2 ) /  epsilon ) ^ 2; %simulation size


lambda = 5 * 4; % 5 hours and 4 per hour 


f = @(w,s) w*s*exp(w*-1 - s); 

%p = integral2(f,0,inf, @(s)2.*s,inf);

p = 0.26; %rounded to 2 decimal

success_count = 0;

for k = 1:N
	num_minions = poissrnd(lambda); %poisson variable how many minions we have caught
	U = sum(rand(num_minions,1) < p); % how many of them have the relationship that we want
	if U > 6 %if it is greater than 6 then increment count
		success_count = success_count +  1;
	end
end

part_1 = success_count/N %result of part1


%part2
%rejection method

total_weight = 0;
a = 0;
b = 10;
c = 1/exp(2);


func = @(x) exp(-x)*x;

for j = 1:N
	weight_for_turn = 0;
	num_minions = poissrnd(lambda);
	for t = 1 : num_minions
		%rejection method code from the book
		x_value = 0; %init x
		y_value = 1/exp(2); %init y
		while y_value > func(x_value)
			random_1 = rand;
			random_2 = rand;
			x_value = a + (b-a)*random_1;
			y_value = c*random_2;
		end
		weight_for_turn = weight_for_turn + x_value;
	end
	total_weight = total_weight + weight_for_turn;
end

part2 = total_weight / N

