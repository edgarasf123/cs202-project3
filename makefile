# ------------------------------------------------------------------------------
#
# FILE NAME:       makefile
#
# DESCRIPTION:     Make file for a GNU program
#
# PURPOSE:         Build a program executable
#
# COMPILATION:     For use with the GNU toolset
#
# NOTES:           http://www.linuxforu.com/2012/06/gnu-make-in-detail-for-beginners/
#                  http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#                  http://www.cplusplus.com/forum/unices/12499/
#                  http://stackoverflow.com/questions/13745645/makefile-clock-skew-detected
#                  http://superuser.com/questions/112316/what-is-the-shell-command-to-display-contents-of-a-file
#                  http://www.tldp.org/HOWTO/Keyboard-and-Console-HOWTO-4.html
#
# MODIFICATION HISTORY:
#
# Author              Date          Modification(s)
# ----------------    ----------    ---------------
# Joel Fredrickson    2016-03-31    Version 0001
#
# ------------------------------------------------------------------------------

PROGRAM_NAME=project2

.PHONY: all clean see

#
# Compile and link ...
#

all: Polynomial.hpp

	reset
	@echo
	@echo
	g++ -c -o driver.o driver.cpp -c -fabi-version=6 -frepo -O -pedantic -std=c++11 -Wall -Wextra
	g++ -c -o Polynomial.o Polynomial.cpp -c -fabi-version=6 -frepo -O -pedantic -std=c++11 -Wall -Wextra
	@echo
	@echo
	g++ driver.o Polynomial.o -L /usr/local/lib -o ${PROGRAM_NAME}
	@echo
	@echo

#
# Clean up ...
#

clean:
	rm -f $(PROGRAM_NAME)
	rm -f *.o
	rm -f *.rpo
	reset
	@echo Contents of this directory ...
	@echo
	@echo
	ls -ltr
	@echo
	@echo

#
# See the values of the internal variables ...
#

see:
#	reset
	@echo
	@echo
	@echo "Program name:  " ${PROGRAM_NAME}
	@echo
	@echo
