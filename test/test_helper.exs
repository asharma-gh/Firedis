ExUnit.start()

cmds = [
  ["ping"]
]


Enum.each(cmds, fn args ->
  {output, status} = System.cmd("redis-cli", args, stderr_to_stdout: true)
  if status !=0 do
    IO.puts """
    Command:

    redis-cli #{Enum.join(args, " ")}

    error'd with:

    #{output}

    Please verify the redis server is running and listening on 127.0.0.1:6379 with no authentication.
    """
    System.halt(1)
  end
end)
