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

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/firedis](https://hexdocs.pm/firedis).

Special thanks to this tutorial 

http://webcache.googleusercontent.com/search?q=cache:ovwDR-XfKs8J:cs.mcgill.ca/~mxia3/2017/06/18/tutorial-extending-elixir-with-c-using-NIF/+&cd=2&hl=en&ct=clnk&gl=us&client=ubuntu
