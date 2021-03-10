CC = g++

OPTIONS = -O2 -march=native
CXXFLAGS = `wx-config --cxxflags`
DLIBS = `wx-config --libs`
all: jeu_de_la_vie

grille.o: grille.cpp grille.h
	$(CC) $(OPTIONS) -c $<
jeu.o: jeu.cpp jeu.h
	$(CC) $(OPTIONS) -c $<
fenetre.o: fenetre.cpp fenetre.h jeu.h
	$(CC) $(OPTIONS) -c $< $(CXXFLAGS)
jeu_de_la_vie: fenetre.o jeu.o grille.o
	$(CC) $(OPTIONS) app.cpp -o $@ $^ $(CXXFLAGS) $(DLIBS)
# make clean	
clean:
	rm -fR psm *.o jeu_de_la_vie
