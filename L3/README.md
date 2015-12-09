## README

* matrix.c:
	* multiplicates two matrizen with help from multiply_matrix.h

* multiply_matrix.c:
	* read a given matrix and multiplicates two given matrizen

* multiply_matrix.h:
	* the header-file to multiply_matrix.c

* matr-gen.py:
	* creates a matrix with the given values
	
* work.c:
	* works as long as the given time in seconds and milliseconds, and return the needed seconds

* work_test.sh:
	* a .sh-file to automatically test work.c 

* mthread.c:
	* a given number of threads prints the words 'Hello World' and waits a random time

* makefile:
	* makefile for work.c, matrix.c and mthread.c

* racecondition.py:
	* shows a race condition

* forksqrt.py:
	* calculates the square roots of given numbers

* cyforksqrt.pyx:
	* contains methods to calculate the square root (in cython)

* measure.py:
	* measures the execution time of various square root methods

* setup.py:
	* used to build a python module

* gen_inputsqrt.py:
	* generates random numbers 

* L3 - Design:
	* the design to mthread.c

* L3 - Timing:
	* has Timing-Numbers for some of the programms above (racecondition.py, cyforksqrt.pyx, matrix.c and mthread.c)

* Hilfreiche Quellen für C:
	* Für "clock_t" = http://www.tutorialspoint.com/c_standard_library/c_function_clock.htm;
	* Für "read = getline()"" = http://c-for-dummies.com/blog/?p=1112
	* Für "strtok" = http://www.c-howto.de/tutorial-strings-zeichenketten-stringfunktionen-zerteilen-strtok.html
	* Für "lrand" = http://www.mkssoftware.com/docs/man3/drand48.3.asp
