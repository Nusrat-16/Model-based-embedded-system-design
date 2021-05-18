clear
clc
close all

mu = []; % variable for storing mu values
lamda_out = []; % variable for storing lamda values
%for storing the index this k is used
k = 1;
 %as the range for lamda is given 
for lamda= 0:.01:1
    sim('a1bc1.slx','StopTime','10');
    mu (k) = ans.mu;  %this command is for getting the value from matlab
    lamda_out (k)= lamda;
    k = k+1;
end

figure (1)
plot (lamda_out, mu)
xlabel ('\lambda')
ylabel ('\mu')
title ('\lambda vs \mu graph')

mu_max_pos = find(mu==max (mu));% finding the position for maximum mu
lamda_max = lamda_out(mu_max_pos);% lamda_max from the maximum mu position

