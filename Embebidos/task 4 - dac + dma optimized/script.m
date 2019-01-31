function wfdbdemo()
% WFDB App Toolbox Demo
%
% Written by Ikaro Silva, 2013
% Last modified: January 10, 2014
%

[~,config]=wfdbloadlib;
echo on
display('Reading samples ECG signal from MIT-BIH Arrhythmia Database')
N=10000;
[signal,frequency,times]=rdsamp('mitdb/100',1,N);

display('Reading and plotting annotations (human labels) of QRS complexes performend on the signals')
%by cardiologists.
[ann,type,subtype,chan,num]=rdann('mitdb/100','atr',1,N);

%Plot 2D version of signal and labels
figure
plot(times(1:N),signal(1:N));hold on;grid on
%plot(times(ann(ann<N)+1),signal(ann(ann<1)+1),'ro');

[ecg_resampled,time]= resample(signal,times,1000);
samples = size(ecg_resampled,1);

minimum = min(ecg_resampled)
maximum = max(ecg_resampled)
span = maximum-minimum
%Plot 2D version of signal and labels
figure
ecg_resampled_scaled = (ecg_resampled(1:samples)- minimum)*(5/span);
ecg_resampled_integer = uencode((ecg_resampled_scaled-2.5),11,2.5);
plot(time(1:samples),ecg_resampled_scaled(1:samples));hold on;grid on
figure
plot(time(1:samples),ecg_resampled_integer(1:samples));hold on;grid on


%Write scaled values to c code file
fileID = fopen('ecg_resampled_scaled.c','w+');
fprintf(fileID, 'const float ecg_resampled_scaled[] = {\r\n');
for index = 1:(samples-1)
    fprintf(fileID,'%2.4f, \r\n',ecg_resampled_scaled(index));
end
fprintf(fileID,'%2.4f \r\n',ecg_resampled_scaled(samples));
fprintf(fileID, '};\r\n');
fclose(fileID);

fileID = fopen('ecg_resampled_integer.c','w+');
fprintf(fileID, 'const uint16_t ecg_resampled_integer[] = {\r\n');
for index = 1:(samples-1)
    fprintf(fileID,'%4d, \r\n',ecg_resampled_integer(index));
end
fprintf(fileID,'%4d \r\n',ecg_resampled_integer(samples));
fprintf(fileID, '};\r\n');
fclose(fileID);


%dlmwrite('ecg_resampled_scaled.txt', ecg_resampled_scaled);

%Stack the ECG signals based on the labeled QRSs
display('Ploting 3D version of signal and labels')
[RR,tms]=ann2rr('mitdb/100','atr',N);
delay=round(0.1/tm(2));
M=length(RR);
offset=0.3;
stack=zeros(M,min(RR))+NaN;
qrs=zeros(M,2)+NaN;
for m=1:M
    stack(m,1:min(RR)+1)=ecg(tms(m)-delay:tms(m)+min(RR)-delay);
    qrs(m,:)=[delay+1 ecg(tms(m))];
end

%Generate plot inspired by
%Clifford GD, Azuaje F, McSharry PE, editors.
%Advanced Methods and Tools for ECG Analysis.
%1st ed., Norwood, MA, USA: Artech House; 2006. (Engineering in Medicine and Biology; 1).
figure
[X,Y] = meshgrid(1:min(RR)+1,1:M);
surf(Y,X,stack);hold on;grid on
shading interp
plot3(1:M,qrs(:,1),qrs(:,2)+offset,'go-','MarkerFaceColor','g')
view(120, 30);
axis off

%Generate plot inspired by
% Samenie et al
% "Filtering Noisy ECG Signals Using Extended Kalman Filter Based on a
% Modified Dynamic ECG Model"
% Computers in Cardiology, 2005
figure
stack=stack';
stack=stack(:)+[0:length(stack(:))-1]'.*0.0005;
theta=linspace(0,M*2*pi,length(stack));
x=sin(theta);y=cos(theta);
plot3(x,y,stack,'b')
grid on
axis off

%Display information about databases availabe in PhysioNet
fprintf('**Querying PhysioNet for available databases...\n')
db_list=physionetdb;
db_size=length(db_list);
fprintf(['\tYou currently have access to ' num2str(db_size) ' databases for download in PhysioNet (type ''help physionetdb'' for more info)!\n'])

display('Demoing finished !!')
display('For more information about the toolbox, type ''wfdb'' at the command prompt.')
echo off
