defmodule FiredisTest do
  use ExUnit.Case
  doctest Firedis

  test "greets the world" do
    assert Firedis.hello() == :world
  end
end
