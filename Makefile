CFLAGS += -g -O3 -ansi -pedantic -Wall -Wextra -Wno-unused-parameter
ERLANG_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)
CFLAGS += -I$(ERLANG_PATH)
CFLAGS += -I/usr/local/include -I/usr/include -L/usr/local/lib -L/usr/lib
CFLAGS += -lhiredis
CFLAGS += -Wno-unused-function


all: build

build:
	mix compile
priv/hiredis.so: c_src/hiredis.c
		$(CC) $(CFLAGS) -shared -o $@ c_src/hiredis.c


clean:
	mix clean
	rm priv/* || true


.PHONY: all clean
