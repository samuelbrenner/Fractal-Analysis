clear all; close all; clc;

% Load in the data
filename = 'flame_data/n7d1r10t15b/n7d1r10t15b.bin_plot.txt';
[header,data] = hdrload(filename);

% Initialize data to be read from header
slope = 0;
intercept = 0;

% Parse the header information
nHeaderLines = size(header,1);
for i=1:nHeaderLines
    line = header(i,:);
    splitLine = regexp(line,':','split');
    
    switch(lower(splitLine{1}))
        case('slope')
            slope = str2double(splitLine{2});
        case('intercept')
            intercept = str2double(splitLine{2});
        otherwise
            fprintf('No use for key = %s\n',splitLine{1});
    end
            
        
end

fprintf('Filename:  %s\n',filename);
fprintf('Slope:     %f\n',slope);
fprintf('Intercept: %f\n',intercept);

%% Create plot
% Create figure window
figure
hold on;

% Plot the raw data points
plot(data(:,1),data(:,2),'ko','linewidth',3)

% Plot the regression line
% This involves either hardcoding the domain (the X's) of the line,
% or determining a domain from the last couple data points
% I'll show the second method, because it's more complicated
nBack = 5;
xMin = data(end-nBack, 1);
xMax = data(end,       1);
x = linspace(xMin,xMax,2);
y = slope*x + intercept;

plot(x,y,'k--')

% Create labels
xlabel('$$\mathrm{log_{2}\left(1/\epsilon\right)}$$','interpreter','latex')
ylabel('$$\mathrm{log_{2}\left(N\right)}$$','interpreter','latex')

text(1.5, 14, sprintf('Dimension: %1.4f\n',slope), 'fontsize', 34, 'fontname', 'Times');











