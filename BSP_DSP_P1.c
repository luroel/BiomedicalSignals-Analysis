%--------------------Procesamiento de señales medicas---------------------%
clc 
clear all
close all
%---------------------------Datos de muestreo-----------------------------%
N = 8368;
Fs = 200;
Ts = 1/Fs;
t = (0:N-1)*Ts;
%------------------Adquisición de la señal en tiempo----------------------%
load('HR_s01.mat');
figure
plot(t,HR_s01)
xlabel('Tiempo (s)')
ylabel('Amplitud')
title('Se?al Electrocardiograma')
grid on