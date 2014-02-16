# $Id: Makefile,v 1.8 2002/07/22 06:11:25 msell Exp $
#
#
# $Log: Makefile,v $
# Revision 1.8  2002/07/22 06:11:25  msell
# end.cpp
#
# Revision 1.7  2002/07/21 20:35:25  msell
# -D_GNU_SOURCE pois
#
# Revision 1.6  2002/07/21 20:33:27  msell
# -g pois
#
# Revision 1.5  2002/07/21 15:16:13  msell
# -Wall pois
#
# Revision 1.4  2002/07/21 15:12:59  msell
# test
#
# Revision 1.3  2002/07/21 15:12:16  msell
# Äänet enabloitu :)
#
# Revision 1.2  2002/07/19 19:48:06  msell
# Makefile
#
# Revision 1.1  2002/07/19 19:46:07  msell
# Makefile
#
#
#
# $Date: 2002/07/22 06:11:25 $

FMOD = yes

GFXFLAGS = `sdl-config --cflags`
GFXLIBS = `sdl-config --libs` -lGL -lGLU -lSDL_image

ifeq ($(FMOD), yes)
 SNDFLAGS = -DUSEFMOD=1
 SNDLIBS = -lfmod-3.5
endif

CC = c++
CFLAGS = -I. -O3 $(GFXFLAGS) $(SNDFLAGS) -pg -s
LIBS = $(GFXLIBS) $(SNDLIBS)


SRC = 3dutils.cpp appearance.cpp audio.cpp camera.cpp collision.cpp \
		fight.cpp font.cpp glapi.cpp graphics.cpp legoblocks.cpp \
		legoman.cpp light.cpp main.cpp material.cpp menu.cpp mesh.cpp \
		object.cpp objectfactory.cpp particle.cpp run.cpp shape.cpp \
		sphere.cpp texture.cpp utils.cpp vector.cpp world.cpp end.cpp

		
OBJ = $(SRC:%.cpp=src/%.o)

all: blockofighter

clean:
	rm -f $(OBJ) gmon.out

distclean: clean
	rm -f blockofighter

blockofighter: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

