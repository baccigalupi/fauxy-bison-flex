# Yosemite comes with a version of bison and flex,
# Homebrew does not overwrite them
BISON=/usr/local/Cellar/bison/3.0.2/bin/bison
FLEX=/usr/local/Cellar/flex/2.5.37/bin/flex

# currently any optimization -O1 to -O3 causes the parser/bit.c code to segfault
CFLAGS=-g -O3 -std=gnu11 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS) -ljansson

SOURCES=$(wildcard src/**/*.c src/*.c src/*/**/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard spec/c-unit/**/*_spec.c spec/c-unit/*_spec.c spec/c-unit/*/**/*_spec.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/fauxy.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: bin/fauxy $(TARGET)

dev: CFLAGS=-g -std=gnu11 -Wall -Wextra -Isrc $(OPTFLAGS) $(LIBS)
dev: all c-unit

# converts to an archive static lib, produces build/fauxy.a
# indexes archive for use
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

build:
	@mkdir -p build
	@mkdir -p bin

# flex and bison -----------
bin/fauxy: src/parser/parse.tab.c src/parser/lex.yy.c
	$(CC) $(CFLAGS) -o bin/fauxy $(SOURCES) src/parser/parse.tab.c src/parser/lex.yy.c -ll

src/parser/parse.tab.c: src/parser/parse.y
	$(BISON) --verbose src/parser/parse.y

src/parser/lex.yy.c: src/parser/lex.l
	$(FLEX) -o src/parser/lex.yy.c src/parser/lex.l

.PHONY: run
run:
	bin/fauxy
# ---------

list-tests:
	echo $(TEST_SRC)

# C unit tests
c-unit: CFLAGS += $(TARGET) src/parser/parse.tab.c src/parser/lex.yy.c
c-unit: $(TESTS)
	sh ./spec/c-unit/lib/run_specs.sh

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f spec/c-unit/spec.log
	rm -f src/parser/parse.tab.*
	rm -f src/parser/lex.yy.*
	rm -rf bin/*
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

dependencies: dependencies/jansson dependencies/libffi

.PHONY: dependencies/jansson
dependencies/jansson:
	cd dependencies/jansson; \
	autoreconf -i; \
	./configure; \
	make; \
	make check; \
	make install

# # System Install
# PREFIX?=/usr/local
# install: all
# 	install -d $(DESTDIR)/$(PREFIX)/lib/
# 	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
