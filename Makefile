PROG = prog 

all:
	g++ -o $(PROG) *.cpp *.h

clean:
	-rm -f prog