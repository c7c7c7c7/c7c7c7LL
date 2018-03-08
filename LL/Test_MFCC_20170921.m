% Compare the features of two specified motor data

clear all
close all

prompt = {'Name of the sound file:'};
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'Data/good_111_01.wav'};
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);

motor=answer{1};

Tw = 30;           % analysis frame duration (ms)
Ts = 10;           % analysis frame shift (ms)
alpha = 0.97;      % preemphasis coefficient
R = [ 300 8000 ];  % frequency range to consider
M = 32;            % number of filterbank channels 
C = 17;            % number of cepstral coefficients
L = 32;            % cepstral sine lifter parameter

[x,fs] = audioread(motor); 

NX=norm(x);
% x=x/NX;

window=hamming(Tw*fs*0.001);
[ MFCC_x, FBE_x, frame_x ] = ...
              mfcc( x, fs, Tw, Ts, alpha, window, R, M, C, L );

% plot several frames and the corresponding MFCCs

nf=size(MFCC_x,2);
Fig_per_row=3;
N_row=4;
L=Tw*fs*0.001;

for i=1:N_row
    %r=randi(nf);
    r=10+(i-1)*round(nf/N_row);
    
    xx=frame_x(:,r); % The segmented signal
    
    XX=fft(xx);      % spectrum of the signal
    P2 = abs(XX/L);
    P1 = P2(1:L/2+1);
    P1(2:end-1) = 2*P1(2:end-1);
    f = fs*(0:(L/2))/L;
        
    mfcc=MFCC_x(:,r); % cepstrum of the signal
    
    subplot(N_row,Fig_per_row,(i-1)*Fig_per_row+1);
    plot(frame_x(:,r));
    xlim([0 inf]);
    xlabel('f (Hz)')
    tmp=sprintf('The %d-th windowed frame',r);
    title(tmp);
    
    subplot(N_row,Fig_per_row,(i-1)*Fig_per_row+2);
    plot(f,P1);
    xlim([0 inf]);
    tmp=sprintf('Spectrum of the %d-th windowed frame',r);
    title(tmp);
    
    subplot(N_row,Fig_per_row,(i-1)*Fig_per_row+3);
    plot(MFCC_x(:,r));
    xlim([0 inf]);
    tmp=sprintf('MFCC of the %d-th windowed frame',r);
    title(tmp);
end

figure;
xx=1:size(MFCC_x,1);
errorbar(xx,mean(MFCC_x,2),std(MFCC_x,0,2));
xlim([0 inf]);


