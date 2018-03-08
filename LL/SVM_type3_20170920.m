% This program uses only the type 3 features

clear all
close all

prompt = {'(1) Feature file step:',...
    '(2) Stem of Models'};
%     '(3) Type of motor to detect (1:good; 2:bad; 3:vibration)'};
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'Feature/FeatureData_type03_','Model/svm_type03_detect_'};
% defaultans = {'Feature/FeatureData_type03_','Model/svm_type03_detect','1'};
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);
file_feature=answer{1};

for MotorType2Detect=1:3
    Label=zeros(3,1);
    % MotorType2Detect=str2num(answer{3}); % 1: good; 2:bad; 3: vibration
    Label(MotorType2Detect)=1;

    % Define the model file name based on the motor type to detect
    switch MotorType2Detect
        case 1
            file_model=sprintf('%s_good',answer{2});
        case 2
            file_model=sprintf('%s_bad',answer{2});
        case 3
            file_model=sprintf('%s_vibration',answer{2});
    end

    X=[];
    X_Label=[];
    for i=1:3
        featurefilename=sprintf('%s%02d',answer{1},i);
        load(featurefilename);
        n=length(Y_Label);    
        X=[X;Y];
        X_Label=[X_Label; ones(n,1)*Label(i)];
    end

    % Find an SVM for detecting the specified motors

    tic
    svm_model=fitcsvm(X,X_Label,'Standardize',true,'KernelFunction','RBF','KernelScale','auto');
    toc

    save(file_model,'svm_model'); % save the trained model

%     cv_model=crossval(svm_model);     % find the model for cross-validation
%     Loss=kfoldLoss(cv_model)          % Find the los via 10-fold cross-validations
end

