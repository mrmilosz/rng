#!/usr/bin/env python

import sys
import os
import struct
import signal

stdout = os.fdopen(sys.stdout.fileno(), 'wb', 0)

def main():
	signal.signal(signal.SIGPIPE, signal.SIG_DFL)
	while True:
		
		# REPLACE ME WITH DESIRED RNG
		uniform_random_double = 0.5
		# END REPLACE ME

		write_double_to_stdout_as_binary(uniform_random_double)

def write_double_to_stdout_as_binary(double):
	binary = struct.pack('d', double)
	stdout.write(binary)

if __name__ == '__main__':
	main()
