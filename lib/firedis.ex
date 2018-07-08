defmodule Firedis do

  def benchmark() do
    IO.puts("Benchmark 10k ping 1 connection...")
    {millisec, _} = :timer.tc(fn ->
      Enum.each(1..10000, fn(_x) ->
        Firedis.Hiredis.query("PING")
      end)
    end)
    Integer.to_string(div(millisec,  1000)) <> "ms"
  end
end
