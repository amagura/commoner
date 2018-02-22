#!/usr/bin/env bash
set -xv

ver=("$(sed -r '/^AC_INIT/!d; s/^AC_INIT..Commoner., .([0-9.]+)..*/\1/' configure.ac)")
ver+=("$(awk -F '.' '{printf("%d.%d.%d", $1, $2, ++$NF)}' <<<"${ver[0]}")")
sed -ri 's/^(AC_INIT..Commoner., .)'"${ver[0]}"'(.)/\1'"${ver[1]}"'\2/' configure.ac
