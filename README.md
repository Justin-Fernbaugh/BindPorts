# BindPorts

## How to compile
```bash make.sh```

## Description
The was a experimental program intended to test whether or not it's possible to have a single parent process bind all ports on a server.
An issue which I ran into was that a single process in my testing environment could not bind to the full 65k+ ports available.
Ultimately the solution was to use 'exec' to a separate process that continues binding ports until the range given in the program is fully binded.
In order to provide as more value I did not clean up the code so consider it to be in a 'alpha' state. There's comments explaining the steps taken at
different sections of the code. Additionally, there's code blocks which are commented but I didn't remove them in case it explains why I chose to write it the way I did.
