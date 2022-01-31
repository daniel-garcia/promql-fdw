CREATE EXTENSION promql_fdw;
CREATE SERVER promql_server FOREIGN DATA WRAPPER promql_fdw;
CREATE FOREIGN TABLE sequential_ints ( val int ) SERVER promql_server;
SELECT * FROM sequential_ints;
