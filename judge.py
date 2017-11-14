import os
import sys

wa = -1
for i in range (1, 65) :
	file_name = 'M_' + str(i);
	input_file = 'input/' + file_name
	output_file = 'output/' + file_name
	cmd = './a.out <' + input_file + ' >out'
	os.system(cmd)
	cmd = 'diff ' + output_file + ' out >diff'
	os.system(cmd)
        print ('Judging test case ' + str(i))
	if (os.stat("diff").st_size != 0) :
		if (wa == -1) :
			wa = i
		print ('\tNO')
	else :
	    print ('\tOK')

print("\n-----------------------------------------\n")
if (wa == -1) :
	print("ACCEPTED!")
else:
	print("WA on test case " + str(wa))
print("\n-----------------------------------------\n")
