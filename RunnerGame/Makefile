##########################################

#
# Nom du programme
#
PROG = RunnerGame

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#
SOURCES = main.cpp Scene.cpp Texture.cpp SuperMesh.cpp Mesh.cpp Personnage.cpp Menu.cpp
#
# Fichiers objets (ne pas modifier sauf si l'extension n'est pas .cpp)
#
OBJETS = ${SOURCES:%.cpp=%.o}

#
# Compilateur C++
#
CXX = g++

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Example: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CXXFLAGS = -std=c++11 -Wall -g

#
# Options de l'editeur de liens
#
LDFLAGS = -Wno-deprecated


#
# Librairies a utiliser
# Example: LDLIBS = -L/usr/local/qt/lib -lqt
#

LDLIBS = -lGL -lSDL2 -lSDL2_image -lwiiuse -lGLU -lbluetooth -lpthread -lSDL2_mixer

##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${PROG} sera un fichier contenant les dependances
#

all: ${PROG}

run: ${PROG}
	./${PROG}

${PROG}: depend-${PROG} ${OBJETS}
	${CXX} -o $@ ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	rm -f *.o depend-${PROG} core 1>/dev/null 2>&1



# Gestion des dependances : creation automatique des dependances en utilisant
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${PROG}:
	${CXX} $(CXXFLAGS) -MM ${SOURCES} > depend-${PROG}


###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c (CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${PROG}
