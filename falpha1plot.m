falpha1 = importdata('falpha_level_1.txt');
alpha = falpha1(:,1);
f = falpha1(:,2);
figure;
hold on;
plot([0, 10],[0, 10]);
scatter(alpha, f);
