falpha1 = importdata('falpha_level_0.txt');
alpha = falpha1(:,1);
f = falpha1(:,2);
figure;
hold on;
%plot([1, 2],[1, 2]);
scatter(alpha, f);
