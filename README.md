# ussu
A tool for authenticating user accounts for POSIX-compatible operating systems.

## Building
### Dependencies
- C library
- POSIX-compatible libcrypt

### Build dependencies
- A C compiler
- cmake

### Compilation and installation
```sh
cmake -DCMAKE_BUILD_TYPE=Release .
make install
```

#### Disabling persist
On some systems `persist` may not work. You can disable it by running commands bellow:
```sh
rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Release -DDISABLE_PERSIST=ON .
```

#### Anti-brute force
If you want to prevent from being attacked by brute force method, add `-DANTI_BRUTE_FORCE=ON` to cmake options:
```sh
rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Release -DANTI_BRUTE_FORCE=ON .
```

## Configuration
Default configuration will be installed to `${CMAKE_INSTALL_PREFIX}/etc/ussu.conf` (by default `/usr/local/etc/ussu.conf`).
Default configuration should always work for your user, if your user is in `wheel` group.

## Usage
```
ussu [ -U uid <or> -u username ] [ -G gid <or> -g groupname ] -C <or> -S <or> command
```
- `-U` -> set custom user id (default is 0), conflicts with `-u`,
- `-G` -> set custom group id (default is 0), conflicts with `-g`,
- `-u` -> set custom username (default is `root`), conflicts with `-U`,
- `-g` -> set group name (default is taken from user, by default `root`), conflicts with `-G`,
- `-S` -> run shell
- `-C` -> reset persist data. Only works if persist is enabled.
