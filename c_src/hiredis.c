#include <erl_nif.h>
#include <hiredis/hiredis.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define HAS_DIRTY_SCHEDULER                                                    \
  (ERL_NIF_MAJOR_VERSION > 2 ||                                                \
   (ERL_NIF_MAJOR_VERSION == 2 && ERL_NIF_MINOR_VERSION >= 10))

// State
static pthread_mutex_t* hiredis_lock;
static redisContext* redis_context = NULL;
static redisReply* redis_reply = NULL;
static char* hostname = "127.0.0.1";
static int port = 6379;

// API
//
// query :: String -> String
// takes in a redis command string `SET FOO BAR` and returns the result
static ERL_NIF_TERM query(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  pthread_mutex_lock(hiredis_lock);
  ErlNifBinary ex_query_str;

  // if input is not a string error
  // enif_inspect_iolist_as_binary returns true on success
  if (!enif_inspect_iolist_as_binary(env, argv[0], &ex_query_str)) {
    return enif_make_badarg(env);
  }

  char* c_query_str = strndup((char*)ex_query_str.data, ex_query_str.size);

  redis_reply = redisCommand(redis_context, c_query_str);
  if (redis_reply == NULL) {
    printf("Error executing command to redis...\n");
    return enif_make_badarg(env);
  }
  char result[redis_reply->len + 1];
  memcpy(result, redis_reply->str, redis_reply->len + 1);

  freeReplyObject(redis_reply);
  free(c_query_str);
  pthread_mutex_unlock(hiredis_lock);
  return enif_make_string(env, result, ERL_NIF_LATIN1);
}

// NIF Boilerplate
#if HAS_DIRTY_SCHEDULER
static ErlNifFunc funcs[] = {{"query", 1, query, ERL_NIF_DIRTY_JOB_IO_BOUND}};
#else
static ErlNifFunc funcs[] = {{"query", 1, query}};
#endif

static int load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
  if (redis_context)
    return 0;

  hiredis_lock = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(hiredis_lock, NULL);

  struct timeval timeout = {0, 250000}; // .25 seconds
  redis_context = redisConnectWithTimeout(hostname, port, timeout);
  if (redis_context == NULL || redis_context->err) {
    if (redis_context) {
      printf("Connection error: %s\n", redis_context->errstr);
      redisFree(redis_context);
    } else {
      printf("Connection error: can't allocate redis context\n");
      return 1;
    }
  }

  return 0;
}

static int reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) { return 0; }

static int upgrade(ErlNifEnv* env, void** priv, void** old_priv,
                   ERL_NIF_TERM info) {

  return load(env, priv, info);
}

static void unload(ErlNifEnv* env, void* priv) {
  if (redis_context)
    redisFree(redis_context);
  if (redis_reply)
    freeReplyObject(redis_reply);

  enif_free(priv);
}

ERL_NIF_INIT(Elixir.Firedis.Hiredis, funcs, &load, &reload, &upgrade, &unload)
