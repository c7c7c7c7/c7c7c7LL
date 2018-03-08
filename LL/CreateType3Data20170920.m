clear all
close all

prompt = {'(1) Number of files per motor:',...
    '(2) Number of good motors:',...
    '(3) Number of bad motors:',...
    '(4) Number of vibration motors:',...
    '(5) Stem of good motor files:',...
    '(6) Stem of bad motor files:',...
    '(7) Stem of vibration motor files:',...
    '(8) Stem of feature file'};
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'21','52','59','50','Data/good_1',...
    'Data/true_bad_2','Data/vibration_3','Feature/FeatureData'};
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);

n_file=str2num(answer{1});
for i=1:3
    [Y, Y_Label]=find_feature(answer{5+i-1},str2num(answer{2+i-1}),n_file,i);
    
    % Save the feature data
    filename=sprintf('%s_type03_%02d',answer{8},i);
    save(filename,'Y','Y_Label');    
end


% % %    
% % % % function used to find the features and labels 
% % % % m_type=1 for good motors; 2 for bad motors; and 3 for vibration.
% % % % Find the MFCC features of all data (all fixed)
% % % 
function [Y, Y_Label]=find_feature(file_stem,n_motor,n_file,m_type)

Tw = 30;           % analysis frame duration (ms)
Ts = 10  ;         % analysis frame shift (ms)
alpha = 0.97;      % preemphasis coefficient
R = [ 300 8000 ];  % frequency range to consider
M = 32;            % number of filterbank channels 
N = 17;            % number of cepstral coefficients
Lm = 32;           % cepstral sine lifter parameter

Fs=30000;
n_second=15;       % use only 10-second data
l_data=Fs*n_second;  % number of elements in each datum
l_frame=round(1E-3*Tw*Fs);   % number of elements per frame
l_shift=round(1E-3*Ts*Fs);   % number of elements for shifting the frame

n_w=Fs;                      % length of the sliding window
n_frame=round((n_w-l_frame)/l_shift)+1; % number of frames in a data segment
window=hamming(l_frame);     % window used for finding the MCFF features
step_size=round(n_w/2);      % step to move the sliding window
n_step=(l_data-n_w)/step_size+1; % number of segments in one datum

n_data=n_motor*n_file;
if m_type==2 
    n_data=n_data-2; % two "bad" motors are switched to good motors
end

Y=zeros(n_step*n_data, 2*N);
Y_Label=zeros(n_step*n_data,1);

k=1;
for i=1:n_motor
    if m_type==2
        if i==6 || i==9
            continue
        end
    end

    for j=1:n_file
        filename = sprintf('%s%02d_%02d.wav',file_stem,i,j);
        fprintf('Finding the feature vector of %s\n',filename);
        [y,fs] = audioread(filename);            % read the sound file
        y_norm=norm(y); y=y/y_norm;              % normalize the data     

        for n=1:n_step
            n1=(n-1)*step_size+1;
            n2=n1+n_w-1;

            [MFCC,FBE,frame]=mfcc(y(n1:n2),Fs,Tw,Ts,alpha,window,R,M,N,Lm);                      
            tmp=[mean(MFCC,2); std(MFCC,0,2)]';
            tmp=tmp/norm(tmp);   % normalize the feature   

            Y_Label(k)=m_type;
            Y(k,:)=tmp;  
            k=k+1;
        end
    end
end
end
