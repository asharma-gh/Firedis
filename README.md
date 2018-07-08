# Firedis

High performance Redis client using C NIFs
## Installation
this library depends on a system-wide installation of `hiredis`
`sudo apt install libhiredis-dev`

compile nif:

`mix compile.hi_redis`

If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `firedis` to your list of dependencies in `mix.exs`:

```elixir
def deps do
  [
    {:firedis, "~> 0.1.0"}
  ]
end
```

## Benchmarks

`redis-benchmark -n 10000 -c 1`
```
====== PING_INLINE ======
  10000 requests completed in 0.21 seconds
  1 parallel clients
```

`Firedis`
```
iex(3)> Firedis.benchmark
Benchmark 10k ping 1 connection...
"197ms"
iex(4)> Firedis.benchmark
Benchmark 10k ping 1 connection...
"211ms"
iex(5)> Firedis.benchmark
Benchmark 10k ping 1 connection...
"213ms"
iex(6)> Firedis.benchmark
Benchmark 10k ping 1 connection...
"191ms"
```

`Redix`
```
iex(5)> (:timer.tc(fn -> Enum.each(1..10000, fn(_x) -> c |> Redix.command(["PING"]) end) end) |> elem(0) |> div(1000) |> Integer.to_string) <> "ms"
"418ms"
iex(6)> (:timer.tc(fn -> Enum.each(1..10000, fn(_x) -> c |> Redix.command(["PING"]) end) end) |> elem(0) |> div(1000) |> Integer.to_string) <> "ms"
"412ms"
```

`Exredis`
```
iex(9)> (:timer.tc(fn -> Enum.each(1..10000, fn(_x) -> c |> Exredis.query(["PING"]) end) end) |> elem(0) |> div(1000) |> Integer.to_string) <> "ms"
"373ms"
iex(10)> (:timer.tc(fn -> Enum.each(1..10000, fn(_x) -> c |> Exredis.query(["PING"]) end) end) |> elem(0) |> div(1000) |> Integer.to_string) <> "ms"
"374ms"
iex(11)> (:timer.tc(fn -> Enum.each(1..10000, fn(_x) -> c |> Exredis.query(["PING"]) end) end) |> elem(0) |> div(1000) |> Integer.to_string) <> "ms"
"377ms"
```
Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/firedis](https://hexdocs.pm/firedis).

Special thanks to this tutorial 

https://www.cs.mcgill.ca/~mxia3/2017/06/18/tutorial-extending-elixir-with-c-using-NIF/
