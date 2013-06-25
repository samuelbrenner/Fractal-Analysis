matrix = importdata('multifractal.txt');
h = pcolor(log2(matrix));
set(h, 'edgealpha', 0);