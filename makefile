# Compiler is G++
CXX = g++-3.4

#MUDLib directory
MUDLIBDIR = ../Libraries
SOCKETLIBDIR = $(MUDLIBDIR)/SocketLib
THREADLIBDIR = $(MUDLIBDIR)/ThreadLib
BASICLIBDIR  = $(MUDLIBDIR)/BasicLib
RMUDDIR = ./RMUD

# libraries
LIBS = -lpthread

# flags
CFLAGS = -I$(MUDLIBDIR)

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(SOCKETLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(THREADLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(BASICLIBDIR)/*.cpp -c;

Rmud: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.cpp -c;
	$(CXX) $(CFLAGS) $(RMUDDIR)/*.cpp -c;

main: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.cpp -c;

link: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.o $(LIBS)
