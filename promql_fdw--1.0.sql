CREATE FUNCTION promql_fdw_handler()
RETURNS fdw_handler
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER promql_fdw
  HANDLER promql_fdw_handler;
