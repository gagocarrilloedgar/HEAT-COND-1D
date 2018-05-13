clear all
clc
%% Heat-cond-1D-graphics

T_im=[40.000000; 
9.153439; 
9.153439; 
9.153439; 
9.153439; 
9.153439; 
9.153439; 
9.153439; 
9.153439; 
7.203825; ];

T_ex=[
40.000000; 
13.724450; 
8.560446; ];

T_CN=[40.000000; 
25.989017; 
19.949719; 
19.744089; ];

x=linspace(1,10,10);
x=x';

x1=linspace(1,10,3);
x1=x1';

x2=linspace(1,10,4);
x2=x2';

% Plots
figure;
plot(x,T_im);
title('Implicit','interpreter','latex');
xlabel('X(m)','interpreter','latex');
ylabel('Temperatura','interpreter','latex');
grid on;

figure;
plot(x1,T_ex);
title('Explicit','interpreter','latex');
xlabel('X(m)','interpreter','latex');
ylabel('Temperatura','interpreter','latex');
grid on;


figure;
plot(x2,T_CN);
title('Crank-Nicholson','interpreter','latex');
xlabel('X(m)','interpreter','latex');
ylabel('Temperatura','interpreter','latex');
grid on;

%% MAPA de temperaturas en función del tiempo

T_CN2=[];


