# Commoner [![Build Status](https://travis-ci.org/amagura/commoner.svg?branch=master)](https://travis-ci.org/amagura/commoner)

Welcome to Commoner!

# Getting Started
First you need to download a copy of Commoner:

```bash
curl -LO 'https://github.com/amagura/commoner/archive/latest.tar.gz'
```

After that, it's just the simple matter of building and installing it:

## Building
1. `autoconf -i`
2. `./configure`
3. `make`

## Installing
1. `make DESTDIR="<DIR>" install`

# Functions

## Commoner.c

### abs_path

On success, returns an allocated<sup>&dagger;</sup> pointer to the absolute path of `pth`;
on failure, returns `NULL` and sets `comnr_errno` to `errno` (set in `getdir`).

```c
char *abs_path(const char *pth);

/* Since abs_path expects a pointer to an immutable string
 *  it is safe to pass it literals
 */
char *tmp = abs_path("/symlink/to/home");
// *tmp => "/home"
```

<sup>&dagger;</sup>Remember to free.

## Str.c


# Macros

## Internal Macros
