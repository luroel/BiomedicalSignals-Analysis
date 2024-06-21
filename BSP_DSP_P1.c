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
%----------------------Remueve componente en DC---------------------------%
S = HR_s01-mean(HR_s01);
%-------------------------Transformada de Fourier-------------------------%
X = fft(S);
X = transpose(X); %Voltea filas y columnas por que la fft da contraria
X1 = abs(X).^2;
X1 = fftshift(X1);
%------------------------Frecuencia normalizada---------------------------%
vec_frec = linspace(-1,1,length(X1));
VF = vec_frec.*(Fs)/2;
%----------------------Transformada de Fourier Visualización------------------%
figure
stem(VF,X1)
xlabel('W');
ylabel('f(W)');
title('Transformada rapida de Fourier')
grid on