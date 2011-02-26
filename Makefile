#
#  MurmurHash3CLI - Command Line Interface for MurmurHash3
#  Copyright (C) 2011 Jaromir Capik <tavvva@email.cz>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

APPNAME = MurmurHash3CLI
TARGET_BIN_DIR = $(DESTDIR)/usr/bin/
COMPILER = g++
OBJECTS = MurmurHash3CLI.o MurmurHash3.o

$(APPNAME) : $(OBJECTS)
	$(COMPILER) -Wall -pedantic -o $(APPNAME) $(OBJECTS)

MurmurHash3CLI.o : MurmurHash3.hpp MurmurHash3CLI.cpp
	$(COMPILER) -Wall -pedantic -c MurmurHash3CLI.cpp

MurmurHash3.o : MurmurHash3.hpp MurmurHash3.cpp
	$(COMPILER) -Wall -pedantic -c MurmurHash3.cpp


.PHONY: install
install : $(APPNAME)
	mkdir -p $(TARGET_BIN_DIR)
	cp $(APPNAME) $(TARGET_BIN_DIR)

.PHONY: clean
clean :
	rm $(APPNAME)
	rm *.o

