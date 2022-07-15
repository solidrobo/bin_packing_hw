from operator import truediv
import subprocess, sys, re

'''
    This test compares the output of the program to a template

    The arguments are:
         <program path> <input file path>
'''

matcher = re.compile(r"""(\+{10}\s*)     # ten '+' characters in a line
                        \1{6}           # six more lines same as first
                        \w{8}\+{2}\s*   # then "filled" to first 8 cells
                        \w{10}\s*\w{10} # last two rows fully filled""", re.X)

args = sys.argv[1:]
process = subprocess.Popen([args[0], args[1]],
                    stdout=subprocess.PIPE, 
                    stderr=subprocess.PIPE)
stdout, stderr = process.communicate()

output = stdout.decode()

if matcher.match(output) is None:
    print(output, 'Is not equal to template!', sep='\n')
    exit(1)