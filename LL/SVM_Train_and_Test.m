clear all
close all

POSITIVE=1;
NEGATIVE=0;
NOTUSED=-1;

prompt = {'(1) Stem of feature files for good motors:',...
          '(2) Stem of feature files for bad motors:',...
          '(3) number of files per motor:',...
          '(4) number of good motors:',...
          '(5) number of bad motors:',...
          '(6) number of data per person:',...
          '(7) type of data:',...
          '(8) type of feature:',...
          '(9) type of test:'};
dlg_title = 'Parameters';
num_lines = 1;
defaultans = {'Results\MFCC17_Good','Results\MFCC17_Bad',...
              '21','50','37','7','5','2','2'};  
answer = inputdlg(prompt,dlg_title,num_lines,defaultans);   

n_filepermotor=str2num(answer{3});
n_goodmotor=str2num(answer{4});
n_badmotor=str2num(answer{5});
n_fileperperson=str2num(answer{6});
type_data=str2num(answer{7});
type_feature=str2num(answer{8});
type_test=str2num(answer{9});

% type of test are as follows:
% 1) For each motor, use data of one person for test;
% 2) For each motor, use 1/3 of data selected at random for test.
% 3) Just use all data, and conduct 10-fold cross validation (as before).

filename1 = sprintf('%s%02d_%02d',answer{1},type_data,type_feature);
filename2 = sprintf('%s%02d_%02d',answer{2},type_data,type_feature);

load(filename1);
Y_good=Y;

load(filename2);
Y_bad=Y;

% shuffle the data if test type is 2
if type_test==2
    Order=randperm(size(Y_good,1));
    Y_good=Y_good(Order',:);
    Order=randperm(size(Y_bad,1));
    Y_bad=Y_bad(Order',:);
end

Loss=zeros(1,3);
for test_count=1:3   
    
    [Good_train, Good_test]=ArrangeData(Y_good,n_filepermotor,n_goodmotor,n_fileperperson,test_count);
    [Bad_train, Bad_test]=ArrangeData(Y_bad,n_filepermotor,n_badmotor,n_fileperperson,test_count);
    
    XX=[Good_train; Bad_train];                                         % training data
    XX_Label=[zeros(size(Good_train,1),1); ones(size(Bad_train,1),1)];
    Order=randperm(length(XX_Label));                                   % shuffle the data before training
    XX=XX(Order',:);
    XX_Label=XX_Label(Order');    
    
    YY=[Good_test; Bad_test];                                           % testing data
    YY_Label=[zeros(size(Good_test,1),1); ones(size(Bad_test,1),1)];

    tic
    svm_model=fitcsvm(XX,XX_Label,'Standardize',true,'KernelFunction','RBF','KernelScale','auto');
    toc
    
    Id=predict(svm_model,YY);  
    n=length(YY_Label);
    c=zeros(2,2);
    for i=1:n
        if Id(i)==0 && YY_Label(i)==0
            c(1,1)=c(1,1)+1;
        elseif Id(i)==0 && YY_Label(i)==1
            c(1,2)=c(1,2)+1;
        elseif Id(i)==1 && YY_Label(i)==0
            c(2,1)=c(2,1)+1;
        else
            c(2,2)=c(2,2)+1;
        end
    end
    disp(c)
    
    Loss(test_count)=loss(svm_model,YY,YY_Label);
   
end
disp(Loss);
