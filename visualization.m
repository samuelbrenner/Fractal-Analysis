matrix = importdata('fractalOut.txt');
h = pcolor(matrix);

matrix2 = importdata('c_hdf5_plt_cnt_1000_uncorrected.txt');
g = pcolor (matrix2);