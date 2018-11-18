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

### nop
A simple no-op function implemented using inline assembly:

```
if (true)
  nop();
```

Calls `__asm__ __volatile__ ("nop")`.

### strlcat
Version included in OpenBSD (circa 1999), written by Todd Miller.<sup>&Dagger;</sup>

```
size_t strlcat(char *dst, const char *src, size_t size);
```

See BSD manpages for more information.

<sup>&Dagger;</sup>Todd does not endorse my use of his code.


### strlcpy
Version included in OpenBSD (circa 2015), written by Todd Miller.  <sup>He does not endorse my use of his code.</sup>

```
size_t strlcpy(char *dst, const char *src, size_t size);
```

See BSD manpages for more information.

### bzero

When `bzero` is not provided by the system, Commoner *exports* an inline function mapping `bzero` to `memset(ptr, '\0', size)`.

```
void bzero(void *ptr, size_t sz);

/* Effectively the same */
bzero(str, 10);
memset(str, '\0', 10);
```

### bcopy
When `bcopy` is not defined by libc, Commoner *exports* an inline function mapping `bcopy` to `memcpy`.

```
void bcopy(const void *src, void *dest, size_t n);

/* Interchangeable */
bcopy(in, out, 10);
memcpy(out, in, 10);
```

### mempcpy
When `mempcpy` is not defined by libc, Commoner provides an inline function mapping `mempcpy` to memcpy`.

```
void *mempcpy(void *dest, const void *src, size_t n);

/* Interchangeable */
char *p = mempcpy(out, in, 10);

int n = 10;
char *P = (memcpy(out, in, n) + n);
```

### mempmove
Similar to `mempcpy` only with `memmove` instead.

Returns `dest + n` instead of just `dest`.

```
void *mempmove(void *dest, const void *src, size_t n);

/* Interchangeable */
char *p = mempmove(in, in, 10);

int n = 10;
char *P = (memmove(in, in, n) + n);
```

### stoll
Converts a string to `long long`; if `strtonum` is not present, `strtol` is used instead, with the result casted to `long long`.

Returns `0` on success, `-1` with `comnr_errno` set to `errno` on failure.

```
int stoll(long long *dst, const char *src);
```

## Str.c


# Macros

## Internal Macros
