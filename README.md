# Commoner [![Build Status](https://travis-ci.org/amagura/commoner.svg?branch=master)](https://travis-ci.org/amagura/commoner)

Welcome to Commoner!

# Table of Contents

# Functions

## Commoner.c

### abs_path

```c
char *abs_path(const char *path);

/* Since abs_path expects a pointer to an immutable string
 *  it is safe to pass it literals
 */
char *tmp = abs_path("/symlink/to/home");
// *tmp => "/home"
```
## Str.c


# Macros

## Internal Macros
