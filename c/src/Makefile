#  Copyright 2015 Alexej Magura
#
#  Copying and distribution of this file, with or without modification,
#  are permitted in any medium without royalty provided the copyright
#  notice and this notice are preserved.  This file is offered as-is,
#  without any warranty.

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mydir := $(abspath $(lastword $(dir $(MAKEFILE_LIST))))
cwd := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

all:
	cd $(mydir)/../test; \
	$(MAKE) $@

ext:
	cd $(mydir)/../test; \
	$(MAKE) $@

check:
	cd $(mydir)/../test; \
	$(MAKE) $@

clean:
	cd $(mydir)/../test; \
	$(MAKE) $@

valgrind:
	cd $(mydir)/../test; \
	$(MAKE) $@
