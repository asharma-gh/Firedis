defmodule FiredisTest do
  use ExUnit.Case
  doctest Firedis

  test "ping" do
    assert Firedis.Hiredis.query("PING") == 'PONG'
  end
end
