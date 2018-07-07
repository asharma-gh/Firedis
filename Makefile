CFLAGS += -g -O3 -ansi -pedantic -Wall -Wextra -Wno-unused-parameter
ERLANG_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)
CFLAGS += -I$(ERLANG_PATH)
CFLAGS += -Wno-unused-function -std=gnu99 -fPIC -Wl,--no-as-needed /usr/local/lib/libhiredis.so


all: build

build:
	mix compile
priv/hiredis.so: c_src/hiredis.c
		gcc-6 $(CFLAGS) -shared -o $@ c_src/hiredis.c


clean:
	mix clean
	rm priv/* || true


.PHONY: all clean
