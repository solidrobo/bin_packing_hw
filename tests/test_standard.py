from operator import truediv
import subprocess, sys

'''
    This test compares the output of the program to a template

    The arguments are:
         <program path> <input file path>
'''

template = '''++++++++++
++++++++++
++++++++++
++++++++++
++++++++++
++++++++++
++++++++++
CamelDog++
FalconDeer
Chinchilla
'''.encode()

args = sys.argv[1:]
process = subprocess.Popen([args[0], args[1]],
                    stdout=subprocess.PIPE, 
                    stderr=subprocess.PIPE)
stdout, stderr = process.communicate()

output = stdout.decode().replace('\r','').encode()

if output != template:
    print(output, 'not equal to', template, sep='\n')
    exit(1)