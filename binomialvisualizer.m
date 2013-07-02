binomialdata = importdata('binomial.txt');
x = binomialdata(:,1);
y = binomialdata(:,2);
bar(x, y);