SUBDIRS = src
dist_doc_DATA = README

clean-local:
	astyle -rvA8T8xeyxC70z2xWYK "*.c"
	astyle -rvA8T8xeyxC70z2xWYK "*.h"
	find . -name '*.orig' -exec rm -f {} +
