FMOD = yes

GFXFLAGS = `sdl-config --cflags`
GFXLIBS = `sdl-config --libs` -lGL -lGLU -lSDL_image

ifeq ($(FMOD), yes)
 SNDFLAGS = -DAUDIO_FMOD=1
 SNDLIBS = -lfmod-3.5
endif

CC = c++
CFLAGS = -I. -O3 $(GFXFLAGS) $(SNDFLAGS)
LIBS = $(GFXLIBS) $(SNDLIBS)


SRC = 3dutils.cpp appearance.cpp audio.cpp camera.cpp collision.cpp \
		fight.cpp font.cpp glapi.cpp graphics.cpp legoblocks.cpp \
		legoman.cpp light.cpp main.cpp material.cpp menu.cpp mesh.cpp \
		object.cpp objectfactory.cpp particle.cpp run.cpp shape.cpp \
		sphere.cpp texture.cpp utils.cpp vector.cpp world.cpp end.cpp \
		fonct.cpp

		
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

