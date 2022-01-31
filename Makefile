MODULE_big = promql_fdw
OBJS = promql_fdw.o

EXTENSION = promql_fdw
DATA = promql_fdw--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

