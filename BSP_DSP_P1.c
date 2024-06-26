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

if a == 2
    %---------------------Diseño filtro altas-----------------------------%
VF1 = vec_frec.*(Fs)/2;
wc = 60; %Frecuencia de corte
filter = ((VF1>=-wc)&(VF1<=wc).*(1))+((VF1<-wc)&(VF1>wc).*(0));
filter2 = 1-filter; %Invertir el filtro
plot(VF1,filter2,'linewidth',3);
xlabel('tiempo');
ylabel('pulse');
title('filtro pasa altos y Transformada rapida de Fourier Se?al Normalizada');
hold on 
grid on
%---------------------Aplicación del filtro pasa altas--------------------%
figure
subplot(2,1,1)
high_filter = X.*fftshift(filter2); %Porque multiplico por algo que no tiene fftshift
%high_filter2 = abs(high_filter).^2;
high_filter2 = fftshift(abs(high_filter).^2);
%stem(VF,fftshift(high_filter2),'r');
stem(VF,high_filter2,'r');
title('Transformada rapida de Fourier Se?al filtrada');
xlabel('W');
ylabel('F(w)')
hold on 
grid on
%----------------------Transformada inversa de Fourier--------------------%
subplot(2,1,2)
invert_transform = ifft(high_filter);
plot(t,real(invert_transform));
grid on
title('Se?al Fitrada en tiempo')
xlabel('seg')
ylabel('Amplitd')
end

if a == 3
   %----------------------Diseño filtro bandas----------------------------%
wc = 2; %Frecuencia de corte
wd = 5; %Limite de frecuencia
filter = ((VF>=wc)&(VF<=wd).*(1))+((VF<wc)&(VF>wd).*(0));
filter_2 = ((VF>=-wd)&(VF<=-wc).*(1))+((VF<-wc)&(VF>-wd).*(0));
bandpass = filter+filter_2;
plot(VF,bandpass,'linewidth',3);
xlabel('tiempo');
ylabel('pulse')
title('filtro pasa bandas');

hold on 
grid on
%---------------------Aplicación del filtro pasa bandas-------------------%
figure
subplot(2,1,1)
band_filter = X.*fftshift(bandpass);
band_filter2 = abs(band_filter).^2;
stem(VF,fftshift(band_filter2),'r');
title('Transformada rapida de Fourier Se?al filtrada');
xlabel('W');
ylabel('F(w)')
hold on 
grid on
%-------------------Transformada inversa de Fourier-----------------------%
subplot(2,1,2)
invert_transform = ifft(band_filter);
plot(t,real(invert_transform));
grid on
title('Se?al Fitrada en tiempo')
xlabel('seg')
ylabel('Amplitd') 
end

if a == 4
    %------------------Diseño filtro rechaza bandas-----------------------%
wc = 10; %Frecuencia de corte
wd = 60; %Limite de frecuencia
filter = ((VF>=wc)&(VF<=wd).*(1))+((VF<wc)&(VF>wd).*(0));
filter_2 = ((VF>=-wd)&(VF<=-wc).*(1))+((VF<-wc)&(VF>-wd).*(0));
bandpass = filter+filter_2;
r_bandas = 1-bandpass;
plot(VF,r_bandas,'linewidth',3);
title('');
xlabel('tiempo');
ylabel('pulse')
title('filtro rechazabandas');
hold on 
grid on
%--------------------Aplicación del filtro rechaza bandas-----------------%
figure
subplot(2,1,1)
filtered = X.*fftshift(r_bandas);
filtered2 = abs(filtered).^2;
stem(VF,fftshift(filtered2),'r');
title('Transformada rapida de Fourier Se?al filtrada');
xlabel('W');
ylabel('F(w)')
hold on 
grid on
%---------------------Transformada inversa de Fourier---------------------%
subplot(2,1,2)
invert_transform = ifft(filtered);
plot(t,real(invert_transform));
grid on
title('Se?al Fitrada en tiempo')
xlabel('seg')
ylabel('Amplitd')
end

%------------------------Creacion de las ventanas-------------------------%
w = 280; %tama?o de la ventana
[S,F,t1] = spectrogram(real(invert_transform),rectwin(w),w-1,4096);
figure
f1 = linspace(0,0.5,2049).*(Fs);
image(t,f1,real(mag2db(abs(S))));
axis xy;
%axis([0 45 0 100]);
title('Espectrograma de frecuencias se?al filtrada');
ylabel('Frecuencia');
xlabel('Tiempo');