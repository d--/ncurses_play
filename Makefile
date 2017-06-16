.PHONY: all install clean

CFLAGS = -Wall

all: bin/cursing

build:
	mkdir -p build

bin:
	mkdir -p bin

bin/cursing: src/cursing.c | bin
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ \
		-lncurses \
		$(shell pkg-config --cflags --libs sdl2) \
		$(shell pkg-config --cflags --libs sdl2_mixer)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	$(RM) -r build bin

