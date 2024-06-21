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
title('Transformada rápida de Fourier')
grid on
%---------------------------Variable de control---------------------------%
a = 1;
%----------------------------Filtro Pasabajos-----------------------------%
if a == 1
%-------------------------Diseño filtro pasabajos-------------------------%
wc = 5.4; %Frecuencia de corte
filter = ((VF>=-wc)&(VF<=wc).*(1))+((VF<-wc)&(VF>wc).*(0));
plot(VF,filter,'linewidth',3);
title('filtro pasa bajas y Transformada rapida de Fourier');
xlabel('Hz');
ylabel('pulse')
hold on 
grid on
%-------------------------Aplicación del filtro Pasabajos-----------------%
figure
subplot(2,1,1)
low_filter = X.*fftshift(filter);
low_filter2 = fftshift(abs(low_filter).^2);
stem(VF,mag2db(low_filter2),'r');
title('Transformada rapida de Fourier Senal filtrada');
xlabel('W');
ylabel('F(w)')
hold on 
grid on
%----------------------Transformada inversa de Fourier--------------------%
subplot(2,1,2)
invert_transform = ifft(low_filter);
plot(t,real(invert_transform));
grid on
title('Señal Fitrada en tiempo')
xlabel('seg')
ylabel('Amplitd')
end
