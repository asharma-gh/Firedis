defmodule Firedis.Hiredis do

  @moduledoc """
  Wrapper module for the Hiredis C library
  """

  # call function on module load
  @on_load { :init, 0 }

  @app Mix.Project.config[:app]

  def init() do
    path = :filename.join(:code.priv_dir(unquote(@app)), "hiredis")
    :ok = :erlang.load_nif(path, 0)
  end

  @spec query(command :: String.t) :: String.t
  def query(command)

  def query(_) do
    exit(:nif_library_not_loaded)
  end
end
