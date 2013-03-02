#!/usr/bin/env python

from random import random
from sys    import stdout
from struct import pack
import signal

def main():
	signal.signal(signal.SIGPIPE, signal.SIG_DFL)
	try:
		while True:
			
			# REPLACE ME WITH DESIRED RNG
			uniform_random_double = random()
			# END REPLACE ME

			write_double_to_stdout_as_binary(uniform_random_double)
	except IOError:
		print('Pipe closed. Who cares.')

def write_double_to_stdout_as_binary(double):
	stdout.buffer.write(pack('d', double))

if __name__ == '__main__':
	main()
