import os
import sys

for i in range (1, 23) :
	file_name = 'G_' + str(i) + '.txt'
	input_file = 'input/' + file_name
	output_file = 'output/' + file_name
	cmd = './a.out <' + input_file + ' >out'
	os.system(cmd)
	cmd = 'diff ' + output_file + ' out >diff'
	os.system(cmd)
	if (os.stat("diff").st_size != 0) :
		print ('WA on test case ' + str(i))
