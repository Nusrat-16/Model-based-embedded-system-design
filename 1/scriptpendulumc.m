clear
clc
close all

%define model constant
m=1;
l=1;
g= 9.82;
b=0;

starting_angle= pi/4; % initial condition

for theta0= starting_angle:-.01:0  %for finding the maximum angle this for loop is being used.
    sim('pendulumc_2','StopTime','100')
    
%here n1,n2 are the values from simulation output.Below command is used to
%get the value from simulation.

    osc_model1= ans.n1(end);
    osc_model2= ans.n2(end);
    
%calculating percentage difference
    percentage_diff = 100*(osc_model2 - osc_model1)/osc_model1;
      if percentage_diff <= 1
       max_theta = num2str(theta0*180/pi);
       X = ['The maximum angle is ',num2str(max_theta),'degree'];
       disp (X)
       break
    end
   
end




