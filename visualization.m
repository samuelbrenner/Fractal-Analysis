matrix = importdata('multifractal.txt');
h = pcolor(log10(matrix));
set(h, 'edgealpha', 0);