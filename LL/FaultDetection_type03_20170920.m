clear all
close all

prompt = {'(1) Stem of good motor files:',...
    '(2) Stem of bad motor files:',...    
    '(3) Stem of vibration motor files',...
    '(4) Data type:',...                         
    '(5) Threshold for making a judgement:'};
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'Data/good_1','Data/true_bad_2','Data/vibration_3','1','0.5'};
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);

file_good=answer{1};
file_bad=answer{2};
file_vibration=answer{3};
d_type=str2num(answer{4}); % d_type=1: input from file; d_type=2: input from mic
THRESHOLD=str2num(answer{5});

% File names for saving falsely detected motor data
new_good='New_Good_Motor/Data';
new_bad='New_Bad_Motor/Data';
new_vibration='New_Vibration_Motor/Data';

% Load the models for detecting specified motors
load Model/svm_type03_detect_good;
good_motor_detector=svm_model;

load Model/svm_type03_detect_bad;
bad_motor_detector=svm_model;

load Model/svm_type03_detect_vibration;
vibration_motor_detector=svm_model;
   
Fs=30000;
if d_type==2 
    recObj = audiorecorder(Fs, 16, 1);
end

% Parameters for finding the MFCC feature of a data segment

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


while 1
    if d_type==1  %%%% Input a specified data file to test the model 
        
        prompt = {'(1) Motor type:',...
            '(2) Number of motor:',...
            '(3) Number of file:'};
        dlg_title = 'Parameters';
        num_lines = 1;
        defaultans = {'1','10','10'};
        answer = inputdlg(prompt,dlg_title,num_lines,defaultans);
        
        m_type=str2num(answer{1}); % m_type=0 motor is good else bad
        n_motor=str2num(answer{2});
        n_file=str2num(answer{3});
        
        switch m_type
            case 1
                filename = sprintf('%s%02d_%02d.wav',file_good,n_motor,n_file);
            case 2
                filename = sprintf('%s%02d_%02d.wav',file_bad,n_motor,n_file);
            case 3
                filename = sprintf('%s%02d_%02d.wav',file_vibration,n_motor,n_file);
        end


        fprintf('Find the feature vector of %s/n',filename);
        [y,fs] = audioread(filename);            % read the sound file
    
    else         %%%% Capture data from the microphone        

        ask('Start recording ?');

        % Countdown
        for i=3:-1:1
            fprintf('\tWait %d seconds.\n', i);
            pause(1);
        end

        fprintf('\tStart recording.\n');
        pause(0.2);

        recordblocking(recObj,n_second);

        % play(recObj);
        y=getaudiodata(recObj);
    end
    
    
    %y_norm=norm(y); y=y/y_norm;              % normalize the data

    Y=zeros(n_step,2*N);
    for n=1:n_step
        n1=(n-1)*step_size+1;
        n2=n1+n_w-1;

        [MFCC,FBE,frame]=mfcc(y(n1:n2),Fs,Tw,Ts,alpha,window,R,M,N,Lm); 
        tmp=[mean(MFCC,2); std(MFCC,0,2)]';
        tmp=tmp/norm(tmp);   % normalize the feature           
        Y(n,:)=tmp;        
    end

    SUM=zeros(3,1);
    YY=predict(good_motor_detector,Y);
    SUM(1)=double(sum(YY)/n_step);
    
   
    YY=predict(bad_motor_detector,Y);
    SUM(2)=double(sum(YY)/n_step);
    
    YY=predict(vibration_motor_detector,Y);
    SUM(3)=double(sum(YY)/n_step);
    
    if SUM(1) == max(SUM) && SUM(1)>THRESHOLD
        plot_MARU('GOOD MOTOR','bo',SUM);
    else
        if SUM(2) == max(SUM) && SUM(2)>THRESHOLD
            plot_MARU('BAD MOTOR','rx',SUM);
        else
            if SUM(3) == max(SUM) && SUM(3)>THRESHOLD
                plot_MARU('Vibration MOTOR','gx',SUM);
            else
                plot_BATSU('REJECT','r+',SUM);
            end
        end
    end    
    
    
    teacher=questdlg('Where to save the data?', 'Selection Menu',...
        'Good_Motor','Bad_Motor','Vibration_Motor','Good_Motor');
    t = datetime;
    
    switch teacher
        case 'Good_Motor'
            filename = sprintf('%s_%s.wav',new_good,datestr(t,30));
            audiowrite(filename,y,Fs);
            fprintf('New data saved in %s\n', filename);
        case 'Bad_Motor'
            filename = sprintf('%s_%s.wav',new_bad,datestr(t,30));
            audiowrite(filename,y,Fs);
            fprintf('New data saved in %s\n', filename);
        case 'Vibration_Motor'
            filename = sprintf('%s_%s.wav',new_vibration,datestr(t,30));
            audiowrite(filename,y,Fs);
            fprintf('New data saved in %s\n', filename);
        otherwise
            fprintf('The data is not saved\n');
    end
        
    if ask('Continue test?') == false
       break; 
    end
    
    close all
end

  
function plot_MARU(figure_title,mark_type,C)
    r = 2;
    xc = 4;
    yc = 3;

    theta = linspace(0,2*pi);
    x = r*cos(theta) + xc;
    y = r*sin(theta) + yc;
    plot(x,y,mark_type)
    axis equal
    Title=sprintf('%s (%f %f %f)',figure_title,C(1),C(2),C(3));
    title(Title);
end


function plot_BATSU(figure_title,mark_type,C)
    t=0:100;
    t1=100-t;
    plot(t,mark_type); hold on
    plot(t1,mark_type)
    axis([0,100,0,100])
    Title=sprintf('%s (%f %f %f)',figure_title,C(1),C(2),C(3));
    title(Title);
end
    

