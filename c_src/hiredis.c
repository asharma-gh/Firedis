#include <hiredis/hiredis.h>
#include <erl_nif.h>
#include <stdio.h>
#include <string.h>
#define HAS_DIRTY_SCHEDULER (ERL_NIF_MAJOR_VERSION > 2 || (ERL_NIF_MAJOR_VERSION == 2 && ERL_NIF_MINOR_VERSION >= 10))


static redisContext* redis_context = NULL;
static redisReply* redis_reply = NULL;
static char* hostname = "127.0.0.1";
static int port = 6379;

// API
static ERL_NIF_TERM query(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {

  return 0;
}

// NIF Boilerplate
#if HAS_DIRTY_SCHEDULER
static ErlNifFunc funcs[] = {
  {"query", 1, query, ERL_NIF_DIRTY_JOB_IO_BOUND}
};
#else
static ErlNifFunc funcs[] = {
  {"query", 1, query}
};
#endif
  
static
int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {

  return 0;
}

static
int
reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {

  return 0;
}

static
int
upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info) {

  return load(env, priv, info);
}

static
void
unload(ErlNifEnv* env, void* priv) {
  if (redis_context) redisFree(redis_context);
  if (redis_reply) freeReplyObject(redis_reply);
}

ERL_NIF_INIT(Elixir.Firedis.Hiredis, funcs, &load, &reload, &upgrade, &unload)
