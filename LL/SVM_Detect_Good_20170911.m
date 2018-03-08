clear all
close all

POSITIVE=1;
NEGATIVE=0;
NOTUSED=-1;

prompt = {'(1) Stem of feature files:',...
    '(2) Stem of model files:'}
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'Feature/FeatureData','Model/svm'};  
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);   

% Load the data from the specified file
% which contains Y and Y_Label
% Y is a N x D matrix, and Y_Label is Nx1 vector
% D is the dimension of a datum
% There are three values for each element of Y_Label: 1, 2, 3

load(answer{1});
n_data=length(Y_Label);

% Train an SVM for good motor detection
% Vibration and Bad (in sound) motors belong to the same class,
% so their labels are 1.

G_Label=zeros(n_data,1);
for i=1:n_data
    if Y_Label(i)==1
        G_Label(i)=0;
    else
        G_Label(i)=1;
    end
end

tic
svm_model=fitcsvm(Y,G_Label,'Standardize',true,'KernelFunction','RBF','KernelScale','auto');
toc
model_file=sprintf('%s_good_motor_detector',answer{2});
save(model_file,'svm_model');

cv_model=crossval(svm_model);     % find the model for cross-validation
Loss=kfoldLoss(cv_model)          % Find the loss via 10-fold cross-validation 