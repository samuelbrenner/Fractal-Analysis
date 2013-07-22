filenum = [50, 200, 375];
figure;
hold on;
for i = 1:numel(filenum)
    n = filenum(i);
    filename = sprintf('~/big/dens_bbb03_hdf5_chk_%0.4d.bin_falpha_level_0.txt', n);
    falpha1 = importdata(filename);
    alpha = falpha1(:,1);
    f = falpha1(:,2);
    %plot([0, 2],[0, 2]);
    scatter(alpha, f);
end
    

% falpha1 = importdata('~/big/dens_bbb03_hdf5_chk_0375.bin_falpha_level_0.txt');
% alpha = falpha1(:,1);
% f = falpha1(:,2);
% figure;
% hold on;
plot([0, 3],[0, 3]);
% scatter(alpha, f);
