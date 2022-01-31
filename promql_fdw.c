#include "postgres.h"
#include "fmgr.h"
#include "foreign/fdwapi.h"
#include "optimizer/pathnode.h"
#include "optimizer/restrictinfo.h"
#include "optimizer/planmain.h"

Datum promql_fdw_handler(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(promql_fdw_handler);

void promql_fdw_GetForeignRelSize(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid);
void promql_fdw_GetForeignPaths(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid);
ForeignScan *promql_fdw_GetForeignPlan(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid,
    ForeignPath *best_path, List *tlist, List *scan_clauses, Plan *outer_plan);
void promql_fdw_BeginForeignScan(ForeignScanState *node, int eflags);
TupleTableSlot *promql_fdw_IterateForeignScan(ForeignScanState *node);
void promql_fdw_ReScanForeignScan(ForeignScanState *node);
void promql_fdw_EndForeignScan(ForeignScanState *node);

Datum
promql_fdw_handler(PG_FUNCTION_ARGS)
{
        FdwRoutine *fdwroutine = makeNode(FdwRoutine);
        fdwroutine->GetForeignRelSize = promql_fdw_GetForeignRelSize;
        fdwroutine->GetForeignPaths = promql_fdw_GetForeignPaths;
        fdwroutine->GetForeignPlan = promql_fdw_GetForeignPlan;
        fdwroutine->BeginForeignScan = promql_fdw_BeginForeignScan;
        fdwroutine->IterateForeignScan = promql_fdw_IterateForeignScan;
        fdwroutine->ReScanForeignScan = promql_fdw_ReScanForeignScan;
        fdwroutine->EndForeignScan = promql_fdw_EndForeignScan;
	PG_RETURN_POINTER(fdwroutine);
}

PG_MODULE_MAGIC;

void promql_fdw_GetForeignRelSize(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid) {
}

void promql_fdw_GetForeignPaths(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid) {
        Path *path = (Path *)create_foreignscan_path(root, baserel,
                NULL,              /* default pathtarget */
                baserel->rows,     /* rows */
                1,                 /* startup cost */
                1 + baserel->rows, /* total cost */
                NIL,               /* no pathkeys */
                NULL,              /* no required outer relids */
                NULL,              /* no fdw_outerpath */
                NIL);              /* no fdw_private */
        add_path(baserel, path);
}

ForeignScan *promql_fdw_GetForeignPlan(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid,
    ForeignPath *best_path, List *tlist, List *scan_clauses, Plan *outer_plan) {
        scan_clauses = extract_actual_clauses(scan_clauses, false);
        return make_foreignscan(tlist,
                scan_clauses,
                baserel->relid,
                NIL, /* no expressions we will evaluate */
                NIL, /* no private data */
                NIL, /* no custom tlist; our scan tuple looks like tlist */
                NIL, /* no quals we will recheck */
                outer_plan);
}

void promql_fdw_BeginForeignScan(ForeignScanState *node, int eflags) {
}

TupleTableSlot *promql_fdw_IterateForeignScan(ForeignScanState *node) {
        return NULL;
}

void promql_fdw_ReScanForeignScan(ForeignScanState *node) {
}

void promql_fdw_EndForeignScan(ForeignScanState *node) {
}


