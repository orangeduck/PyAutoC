CC=gcc

C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	INCS= -I ./include -I/usr/include/python2.7
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -lpython2.7
	DISTUTIL=
	
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	INCS= -I ./include -I./Python27/include
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L./Python27/libs -lpython27 -lmingw32
	DISTUTIL= -c mingw32
endif

all: demo_func demo_struct demo_mod demo_embed demo_convert

demo_func: $(OBJ_FILES)
	$(CC) demos/demo_func.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
	
demo_struct: $(OBJ_FILES)
	$(CC) demos/demo_struct.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
	
demo_mod: $(OBJ_FILES)
	python demos/setup.py build $(DISTUTIL)
	
demo_embed: $(OBJ_FILES)
	$(CC) demos/demo_embed.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
	
demo_convert: $(OBJ_FILES)
	$(CC) demos/demo_convert.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
	
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
	
clean:
	rm $(OBJ_FILES)
