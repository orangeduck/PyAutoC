CC=gcc

INCS= -I ./include -I./Python27/include

C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -shared
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L./Python27/libs -lpython27 -lmingw32
endif

demo: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) -o $@
	
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
	
clean:
	rm $(OBJ_FILES)
