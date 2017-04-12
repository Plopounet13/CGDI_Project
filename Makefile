PROG = main

# Variables pour la compilation des fichiers
CC        =  clang++
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG -I$(INCDIR)
LDFLAGS   =  -g
STD = -std=c++11
FILES = Pixel Image Util Histogramme
OBJECTS = $(FILES:=.o)


all : $(PROG)

build/%.o : src/%.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(STD) $< -o $@

$(PROG): % : build/%.o $(OBJECTS:%=build/%)
	$(CC) $(LDFLAGS) $(STD) -o bin/$@ $< $(OBJECTS:%=build/%) -lm

cleanall : clean
	rm -f $(PROG:%=bin/%)

clean :
	rm -f build/*.o


