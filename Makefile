SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h
PROGRAM=vm
WINDOWS_PROGRAM=vm.exe
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)
FULL_LEAK_CHECK_FILENAME="Requirement13Part1.txt"
TRACK_ORIGINS_FILENAME="Requirement13Part2.txt"
USER=s3485376

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

windows:
	gcc $(FLAGS) -o $(WINDOWS_PROGRAM) $(SOURCES)

clean:
	rm $(PROGRAM)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile

valgrind: all
	valgrind --leak-check=full --show-reachable=yes ./$(PROGRAM) stock.dat coins.dat

report_leaks: all
	valgrind --track-origins=yes --log-file=$(TRACK_ORIGINS_FILENAME) ./$(PROGRAM) stock.dat coins.dat


