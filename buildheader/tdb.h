#ifndef _DB_H
#define _DB_H
/* This code generated by make_db_h.   Copyright (c) 2007, 2008 Tokutek */
#ident "Copyright (c) 2007, 2008 Tokutek Inc.  All rights reserved."
#include <sys/types.h>
/*stdio is needed for the FILE* in db->verify*/
#include <stdio.h>
#include <stdint.h>
#if defined(__cplusplus)
extern "C" {
#endif
#define TOKUDB 1
#define TOKUDB_NATIVE_H 1
#define DB_VERSION_MAJOR 4
#define DB_VERSION_MINOR 6
#define DB_VERSION_PATCH 19
#ifndef _TOKUDB_WRAP_H
#define DB_VERSION_STRING "Tokutek: TokuDB 4.6.19"
#else
#define DB_VERSION_STRING_ydb "Tokutek: TokuDB (wrapped bdb)"
#endif
#ifndef TOKU_OFF_T_DEFINED
#define TOKU_OFF_T_DEFINED
typedef int64_t toku_off_t;
#endif
typedef struct __toku_db_env DB_ENV;
typedef struct __toku_db_key_range DB_KEY_RANGE;
typedef struct __toku_db_lsn DB_LSN;
typedef struct __toku_db DB;
typedef struct __toku_db_txn DB_TXN;
typedef struct __toku_db_txn_active DB_TXN_ACTIVE;
typedef struct __toku_db_txn_stat DB_TXN_STAT;
typedef struct __toku_dbc DBC;
typedef struct __toku_dbt DBT;
typedef u_int32_t db_recno_t;
typedef int(*YDB_CALLBACK_FUNCTION)(DBT const*, DBT const*, void*);
#include <tdb-internal.h>
#ifndef __BIGGEST_ALIGNMENT__
  #define __BIGGEST_ALIGNMENT__ 16
#endif
typedef struct __toku_db_btree_stat64 {
  u_int64_t bt_nkeys; /* how many unique keys (guaranteed only to be an estimate, even when flattened)          */
  u_int64_t bt_ndata; /* how many key-value pairs (an estimate, but exact when flattened)                       */
  u_int64_t bt_dsize; /* how big are the keys+values (not counting the lengths) (an estimate, unless flattened) */
  u_int64_t bt_fsize; /* how big is the underlying file                                                         */
} DB_BTREE_STAT64;
typedef struct __toku_loader DB_LOADER;
struct __toku_loader_internal;
struct __toku_loader {
  struct __toku_loader_internal *i;
  int (*set_error_callback)(DB_LOADER *loader, void (*error_cb)(DB *db, int i, int err, DBT *key, DBT *val, void *error_extra), void *error_extra); /* set the error callback */
  int (*set_poll_function)(DB_LOADER *loader, int (*poll_func)(void *extra, float progress), void *poll_extra);             /* set the polling function */
  int (*put)(DB_LOADER *loader, DBT *key, DBT* val);                                                      /* give a row to the loader */
  int (*close)(DB_LOADER *loader);                                                                        /* finish loading, free memory */
  int (*abort)(DB_LOADER *loader);                                                                        /* abort loading, free memory */
};
typedef struct __toku_indexer DB_INDEXER;
struct __toku_indexer_internal;
struct __toku_indexer {
  struct __toku_indexer_internal *i;
  int (*set_error_callback)(DB_INDEXER *indexer, void (*error_cb)(DB *db, int i, int err, DBT *key, DBT *val, void *error_extra), void *error_extra); /* set the error callback */
  int (*set_poll_function)(DB_INDEXER *indexer, int (*poll_func)(void *extra, float progress), void *poll_extra);             /* set the polling function */
  int (*build)(DB_INDEXER *indexer);  /* build the indexes */
  int (*close)(DB_INDEXER *indexer);  /* finish indexing, free memory */
  int (*abort)(DB_INDEXER *indexer);  /* abort  indexing, free memory */
};
typedef struct __toku_engine_status {
  char             creationtime[26];        /* time of environment creation */ 
  char             startuptime[26];         /* time of engine startup */ 
  char             now[26];                 /* time of engine status query (i.e. now)  */ 
  u_int64_t        ydb_lock_ctr;            /* how many times has ydb lock been taken/released?                                                                      */
  u_int32_t        num_waiters_now;         /* How many are waiting on the ydb lock right now (including the current lock holder if any)?                            */
  u_int32_t        max_waiters;             /* The maximum of num_waiters_now.                                                                                       */
  u_int64_t        total_sleep_time;        /* Total time spent (since the system was booted) sleeping (by the indexer) to give foreground threads a chance to work. */
  u_int64_t        max_time_ydb_lock_held;  /* Maximum time that the ydb lock was held (tokutime_t).                                                                 */
  u_int64_t        total_time_ydb_lock_held;/* Total time client threads held the ydb lock (really tokutime_t, convert to seconds with tokutime_to_seconds())        */
  u_int64_t        total_time_since_start;  /* Total time since the lock was created (tokutime_t).  Use this as total_time_ydb_lock_held/total_time_since_start to get a ratio.   */
  u_int32_t        checkpoint_period;       /* delay between automatic checkpoints  */ 
  u_int32_t        checkpoint_footprint;    /* state of checkpoint procedure        */ 
  char             checkpoint_time_begin[26]; /* time of last checkpoint begin      */ 
  char             checkpoint_time_begin_complete[26]; /* time of last complete checkpoint begin      */ 
  char             checkpoint_time_end[26]; /* time of last checkpoint end      */ 
  u_int64_t        checkpoint_last_lsn;     /* LSN of last complete checkpoint  */ 
  u_int32_t        checkpoint_count;         /* number of checkpoints taken        */ 
  u_int32_t        checkpoint_count_fail;    /* number of checkpoints failed        */ 
  u_int64_t        txn_begin;               /* number of transactions ever begun             */ 
  u_int64_t        txn_commit;              /* txn commit operations                         */ 
  u_int64_t        txn_abort;               /* txn abort operations                          */ 
  u_int64_t        txn_close;               /* txn completions (should equal commit+abort)   */ 
  u_int64_t        txn_oldest_live;         /* oldest extant txn txnid                            */ 
  char             txn_oldest_live_starttime[26];   /* oldest extant txn start time                      */ 
  u_int64_t        next_lsn;                /* lsn that will be assigned to next log entry   */ 
  u_int64_t        cachetable_lock_taken;   /* how many times has cachetable lock been taken */ 
  u_int64_t        cachetable_lock_released;/* how many times has cachetable lock been released */ 
  u_int64_t        cachetable_hit;          /* how many cache hits   */ 
  u_int64_t        cachetable_miss;         /* how many cache misses */ 
  u_int64_t        cachetable_misstime;     /* how many usec spent waiting for disk read because of cache miss */ 
  u_int64_t        cachetable_waittime;     /* how many usec spent waiting for another thread to release cache line */ 
  u_int64_t        cachetable_wait_reading; /* how many times get_and_pin waits for a node to be read */ 
  u_int64_t        cachetable_wait_writing; /* how many times get_and_pin waits for a node to be written */ 
  u_int64_t        cachetable_wait_checkpoint; /* how many times get_and_pin waits for a node to be written for a checkpoint*/ 
  u_int64_t        cachetable_evictions;    /* how many cache table blocks are evicted */ 
  u_int64_t        puts;                    /* how many times has a newly created node been put into the cachetable */ 
  u_int64_t        prefetches;              /* how many times has a block been prefetched into the cachetable */ 
  u_int64_t        maybe_get_and_pins;      /* how many times has maybe_get_and_pin(_clean) been called */ 
  u_int64_t        maybe_get_and_pin_hits;  /* how many times has get_and_pin(_clean) returned with a node */ 
  u_int64_t        maybe_get_and_pin_if_in_memorys;  /* how many times has get_and_pin_if_in_memory been called */ 
  int64_t          cachetable_size_current; /* sum of the sizes of the nodes represented in the cachetable */ 
  int64_t          cachetable_size_limit;   /* the limit to the sum of the node sizes */ 
  int64_t          cachetable_size_max;     /* the max value (high water mark) of cachetable_size_current */ 
  uint64_t         cachetable_size_leaf;    /* the number of bytes of leaf nodes */ 
  uint64_t         cachetable_size_nonleaf; /* the number of bytes of nonleaf nodes */ 
  int64_t          cachetable_size_writing; /* the sum of the sizes of the nodes being written */ 
  int64_t          get_and_pin_footprint;   /* state of get_and_pin procedure */ 
  int64_t          local_checkpoint;        /* number of times a local checkpoint is taken for commit */ 
  int64_t          local_checkpoint_files;  /* number of files subjec to local checkpoint is taken for commit */ 
  int64_t          local_checkpoint_during_checkpoint;  /* number of times a local checkpoint happens during normal checkpoint */ 
  u_int32_t        range_locks_max;         /* max total number of range locks */ 
  u_int32_t        range_locks_curr;        /* total range locks currently in use */ 
  u_int64_t        range_locks_max_memory;   /* max total bytes of range locks */ 
  u_int64_t        range_locks_curr_memory;  /* total bytes of range locks currently in use */ 
  u_int32_t        range_lock_escalation_successes;       /* number of times range locks escalation succeeded */ 
  u_int32_t        range_lock_escalation_failures;        /* number of times range locks escalation failed */ 
  u_int64_t        range_read_locks;        /* total range read locks taken */ 
  u_int64_t        range_read_locks_fail;   /* total range read locks unable to be taken */ 
  u_int64_t        range_out_of_read_locks; /* total times range read locks exhausted */ 
  u_int64_t        range_write_locks;       /* total range write locks taken */ 
  u_int64_t        range_write_locks_fail;  /* total range write locks unable to be taken */ 
  u_int64_t        range_out_of_write_locks; /* total times range write locks exhausted */ 
  u_int64_t        directory_read_locks;        /* total directory read locks taken */ 
  u_int64_t        directory_read_locks_fail;   /* total directory read locks unable to be taken */ 
  u_int64_t        directory_write_locks;       /* total directory write locks taken */ 
  u_int64_t        directory_write_locks_fail;  /* total directory write locks unable to be taken */ 
  u_int64_t        inserts;                 /* ydb row insert operations              */ 
  u_int64_t        inserts_fail;            /* ydb row insert operations that failed  */ 
  u_int64_t        deletes;                 /* ydb row delete operations              */ 
  u_int64_t        deletes_fail;            /* ydb row delete operations that failed  */ 
  u_int64_t        updates;                 /* ydb row update operations              */ 
  u_int64_t        updates_fail;            /* ydb row update operations that failed  */ 
  u_int64_t        updates_broadcast;       /* ydb row update broadcast operations              */ 
  u_int64_t        updates_broadcast_fail;  /* ydb row update broadcast operations that failed  */ 
  u_int64_t        multi_inserts;           /* ydb multi_row insert operations, dictionaray count             */ 
  u_int64_t        multi_inserts_fail;      /* ydb multi_row insert operations that failed, dictionary count  */ 
  u_int64_t        multi_deletes;           /* ydb multi_row delete operations, dictionary count              */ 
  u_int64_t        multi_deletes_fail;      /* ydb multi_row delete operations that failed, dictionary count  */ 
  u_int64_t        multi_updates;           /* ydb row update operations, dictionary count              */ 
  u_int64_t        multi_updates_fail;      /* ydb row update operations that failed, dictionary count  */ 
  u_int64_t        le_updates;              /* leafentry update operations                        */ 
  u_int64_t        le_updates_broadcast;    /* leafentry update broadcast operations              */ 
  u_int64_t        descriptor_set;          /* descriptor set operations              */ 
  u_int64_t        partial_fetch_hit;        /* node partition is present             */ 
  u_int64_t        partial_fetch_miss;       /* node is present but partition is absent */ 
  u_int64_t        partial_fetch_compressed; /* node partition is present but compressed  */ 
  u_int64_t        msn_discards;             /* how many messages were ignored by leaf because of msn */ 
  u_int64_t        max_workdone;             /* max workdone value of any buffer  */ 
  u_int64_t        dsn_gap;                  /* dsn has detected a gap in continuity of root-to-leaf path (internal node was evicted and re-read) */ 
  u_int64_t        point_queries;           /* ydb point queries                      */ 
  u_int64_t        sequential_queries;      /* ydb sequential queries                 */ 
  u_int64_t        le_max_committed_xr;     /* max committed transaction records in any packed le  */ 
  u_int64_t        le_max_provisional_xr;   /* max provisional transaction records in any packed le   */ 
  u_int64_t        le_max_memsize;          /* max memsize of any packed le     */ 
  u_int64_t        le_expanded;             /* number of times ule used expanded memory     */ 
  u_int64_t        fsync_count;             /* number of times fsync performed        */ 
  u_int64_t        fsync_time;              /* total time required to fsync           */ 
  u_int64_t        logger_ilock_ctr;        /* how many times has logger input lock been taken or released  */ 
  u_int64_t        logger_olock_ctr;        /* how many times has logger output condition lock been taken or released  */ 
  u_int64_t        logger_swap_ctr;         /* how many times have logger buffers been swapped  */ 
  char             enospc_most_recent[26];  /* time of most recent ENOSPC error return from disk write  */ 
  u_int64_t        enospc_threads_blocked;  /* how many threads are currently blocked by ENOSPC */ 
  u_int64_t        enospc_ctr;              /* how many times has ENOSPC been returned by disk write */ 
  u_int64_t        enospc_redzone_ctr;      /* how many times has ENOSPC been returned to user (red zone) */ 
  u_int64_t        enospc_state;            /* state of ydb-level ENOSPC prevention (0 = green, 1 = yellow, 2 = red) */ 
  u_int64_t        loader_create;           /* number of loaders created */ 
  u_int64_t        loader_create_fail;      /* number of failed loader creations */ 
  u_int64_t        loader_put;              /* number of loader puts (success) */ 
  u_int64_t        loader_put_fail;         /* number of loader puts that failed */ 
  u_int64_t        loader_close;            /* number of loaders closed (succeed or fail) */ 
  u_int64_t        loader_close_fail;       /* number of loaders closed with error return */ 
  u_int64_t        loader_abort;            /* number of loaders aborted  */ 
  u_int32_t        loader_current;          /* number of loaders currently existing           */ 
  u_int32_t        loader_max;              /* max number of loaders extant simultaneously    */ 
  u_int64_t        logsuppress;             /* number of times logging is suppressed */ 
  u_int64_t        logsuppressfail;         /* number of times logging cannot be suppressed  */ 
  u_int64_t        indexer_create;          /* number of indexers created successfully */ 
  u_int64_t        indexer_create_fail;     /* number of failed indexer creations */ 
  u_int64_t        indexer_build;           /* number of indexer build calls (succeeded) */ 
  u_int64_t        indexer_build_fail;      /* number of indexers build calls with error return */ 
  u_int64_t        indexer_close;           /* number of indexers closed successfully) */ 
  u_int64_t        indexer_close_fail;      /* number of indexers closed with error return */ 
  u_int64_t        indexer_abort;           /* number of indexers aborted  */ 
  u_int32_t        indexer_current;         /* number of indexers currently existing           */ 
  u_int32_t        indexer_max;             /* max number of indexers extant simultaneously    */ 
  u_int64_t        upgrade_env_status;      /* Was an environment upgrade done?  What was done?  */ 
  u_int64_t        upgrade_header;          /* how many brt headers were upgraded? */ 
  u_int64_t        upgrade_nonleaf;         /* how many brt nonleaf nodes  were upgraded? */ 
  u_int64_t        upgrade_leaf;            /* how many brt leaf nodes were upgraded? */ 
  u_int64_t        optimized_for_upgrade;   /* how many optimized_for_upgrade messages were broadcast */ 
  u_int64_t        original_ver;            /* original environment version  */ 
  u_int64_t        ver_at_startup;          /* environment version at startup */ 
  u_int64_t        last_lsn_v13;            /* last lsn of version 13 environment */ 
  char             upgrade_v14_time[26];    /* timestamp of when upgrade to version 14 environment was done */ 
  u_int64_t        env_panic;               /* non-zero if environment is panicked */ 
  u_int64_t        logger_panic;            /* non-zero if logger is panicked */ 
  u_int64_t        logger_panic_errno;      /* non-zero if environment is panicked */ 
  uint64_t         malloc_count;            /* number of malloc operations */ 
  uint64_t         free_count;              /* number of free operations */ 
  uint64_t         realloc_count;           /* number of realloc operations */ 
  uint64_t         malloc_fail;             /* number of failed malloc operations */ 
  uint64_t         realloc_fail;            /* number of failed realloc operations */ 
  uint64_t         mem_requested;           /* number of bytes requested via malloc/realloc */ 
  uint64_t         mem_used;                /* number of bytes used (obtained from malloc_usable_size()) */ 
  uint64_t         mem_freed;               /* number of bytes freed */ 
  uint64_t         max_mem_in_use;          /* estimated max value of (used - freed) */ 
} ENGINE_STATUS;
typedef enum {
 DB_BTREE=1,
 DB_UNKNOWN=5
} DBTYPE;
#ifndef _TOKUDB_WRAP_H
#define DB_VERB_DEADLOCK 1
#define DB_VERB_RECOVERY 8
#define DB_VERB_REPLICATION 32
#define DB_VERB_WAITSFOR 64
#define DB_ARCH_ABS 1
#define DB_ARCH_LOG 4
#define DB_CREATE 1
#define DB_CXX_NO_EXCEPTIONS 1
#define DB_EXCL 16384
#define DB_PRIVATE 8388608
#define DB_RDONLY 32
#define DB_RECOVER 64
#define DB_RUNRECOVERY -30975
#define DB_THREAD 128
#define DB_TXN_NOSYNC 512
#define DB_LOCK_DEFAULT 1
#define DB_LOCK_OLDEST 7
#define DB_LOCK_RANDOM 8
#define DB_KEYFIRST 13
#define DB_KEYLAST 14
#define DB_NOOVERWRITE 20
#define DB_NODUPDATA 19
#define DB_NOOVERWRITE_NO_ERROR 1
#define DB_OPFLAGS_MASK 255
#define DB_AUTO_COMMIT 33554432
#define DB_INIT_LOCK 131072
#define DB_INIT_LOG 262144
#define DB_INIT_MPOOL 524288
#define DB_INIT_TXN 2097152
#define DB_KEYEXIST -30996
#define DB_LOCK_DEADLOCK -30995
#define DB_LOCK_NOTGRANTED -30994
#define DB_NOTFOUND -30989
#define DB_SECONDARY_BAD -30974
#define DB_DONOTINDEX -30998
#define DB_BUFFER_SMALL -30999
#define DB_BADFORMAT -30500
#define DB_DELETE_ANY 65536
#define DB_TRUNCATE_WITHCURSORS 131072
#define DB_FIRST 7
#define DB_LAST 15
#define DB_CURRENT 6
#define DB_NEXT 16
#define DB_NEXT_NODUP 18
#define DB_PREV 23
#define DB_PREV_NODUP 25
#define DB_SET 26
#define DB_SET_RANGE 27
#define DB_CURRENT_BINDING 253
#define DB_SET_RANGE_REVERSE 252
#define DB_RMW 1073741824
#define DB_IS_RESETTING_OP 0x01000000
#define DB_PRELOCKED 0x00800000
#define DB_PRELOCKED_WRITE 0x00400000
#define DB_PRELOCKED_FILE_READ 0x00200000
#define DB_IS_HOT_INDEX 0x00100000
#define DB_DBT_APPMALLOC 1
#define DB_DBT_DUPOK 2
#define DB_DBT_MALLOC 8
#define DB_DBT_MULTIPLE 16
#define DB_DBT_REALLOC 64
#define DB_DBT_USERMEM 256
#define DB_LOG_AUTOREMOVE 524288
#define DB_TXN_WRITE_NOSYNC 4096
#define DB_TXN_NOWAIT 1024
#define DB_TXN_SYNC 16384
#define DB_TXN_SNAPSHOT 268435456
#define DB_READ_UNCOMMITTED 134217728
#define DB_READ_COMMITTED 67108864
#define DB_INHERIT_ISOLATION 1
#define DB_SERIALIZABLE 2
#endif
/* TOKUDB specific error codes */
#define TOKUDB_OUT_OF_LOCKS -100000
#define TOKUDB_SUCCEEDED_EARLY -100001
#define TOKUDB_FOUND_BUT_REJECTED -100002
#define TOKUDB_USER_CALLBACK_ERROR -100003
#define TOKUDB_DICTIONARY_TOO_OLD -100004
#define TOKUDB_DICTIONARY_TOO_NEW -100005
#define TOKUDB_DICTIONARY_NO_HEADER -100006
#define TOKUDB_CANCELED -100007
#define TOKUDB_NO_DATA -100008
#define TOKUDB_ACCEPT -100009
#define TOKUDB_MVCC_DICTIONARY_TOO_NEW -100010
#define TOKUDB_UPGRADE_FAILURE -100011
#define TOKUDB_TRY_AGAIN -100012
#define TOKUDB_NEEDS_REPAIR -100013
#define TOKUDB_CURSOR_CONTINUE -100014
/* LOADER flags */
#define LOADER_USE_PUTS 1
typedef int (*generate_row_for_put_func)(DB *dest_db, DB *src_db, DBT *dest_key, DBT *dest_val, const DBT *src_key, const DBT *src_val);
typedef int (*generate_row_for_del_func)(DB *dest_db, DB *src_db, DBT *dest_key, const DBT *src_key, const DBT *src_val);
/* in wrap mode, top-level function txn_begin is renamed, but the field isn't renamed, so we have to hack it here.*/
#ifdef _TOKUDB_WRAP_H
#undef txn_begin
#endif
struct __toku_db_env {
  struct __toku_db_env_internal *i;
#define db_env_struct_i(x) ((x)->i)
  int (*checkpointing_set_period)             (DB_ENV*, u_int32_t) /* Change the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_get_period)             (DB_ENV*, u_int32_t*) /* Retrieve the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_postpone)               (DB_ENV*) /* Use for 'rename table' or any other operation that must be disjoint from a checkpoint */;
  int (*checkpointing_resume)                 (DB_ENV*) /* Alert tokudb 'postpone' is no longer necessary */;
  int (*checkpointing_begin_atomic_operation) (DB_ENV*) /* Begin a set of operations (that must be atomic as far as checkpoints are concerned). i.e. inserting into every index in one table */;
  int (*checkpointing_end_atomic_operation)   (DB_ENV*) /* End   a set of operations (that must be atomic as far as checkpoints are concerned). */;
  int (*set_default_bt_compare)  (DB_ENV*,int (*bt_compare) (DB *, const DBT *, const DBT *)) /* Set default (key) comparison function for all DBs in this environment.  Required for RECOVERY since you cannot open the DBs manually. */;
  int (*get_engine_status)                    (DB_ENV*, ENGINE_STATUS*, char*, int) /* Fill in status struct, possibly env panic string */;
  int (*get_engine_status_text)               (DB_ENV*, char*, int)     /* Fill in status text */;
  int (*get_iname)                            (DB_ENV* env, DBT* dname_dbt, DBT* iname_dbt) /* FOR TEST ONLY: lookup existing iname */;
  int (*create_loader)                        (DB_ENV *env, DB_TXN *txn, DB_LOADER **blp,    DB *src_db, int N, DB *dbs[/*N*/], uint32_t db_flags[/*N*/], uint32_t dbt_flags[/*N*/], uint32_t loader_flags);
  int (*create_indexer)                       (DB_ENV *env, DB_TXN *txn, DB_INDEXER **idxrp, DB *src_db, int N, DB *dbs[/*N*/], uint32_t db_flags[/*N*/], uint32_t indexer_flags);
  void *app_private;
  int (*put_multiple)                         (DB_ENV *env, DB *src_db, DB_TXN *txn,
                                             const DBT *src_key, const DBT *src_val,
                                             uint32_t num_dbs, DB **db_array, DBT *keys, DBT *vals, uint32_t *flags_array) /* insert into multiple DBs */;
  int (*set_generate_row_callback_for_put)    (DB_ENV *env, generate_row_for_put_func generate_row_for_put);
  int (*del_multiple)                         (DB_ENV *env, DB *src_db, DB_TXN *txn,
                                             const DBT *src_key, const DBT *src_val,
                                             uint32_t num_dbs, DB **db_array, DBT *keys, uint32_t *flags_array) /* delete from multiple DBs */;
  int (*set_generate_row_callback_for_del)    (DB_ENV *env, generate_row_for_del_func generate_row_for_del);
  int (*update_multiple)                      (DB_ENV *env, DB *src_db, DB_TXN *txn,
                                             DBT *old_src_key, DBT *old_src_data,
                                             DBT *new_src_key, DBT *new_src_data,
                                             uint32_t num_dbs, DB **db_array, uint32_t *flags_array,
                                             uint32_t num_keys, DBT *keys,
                                             uint32_t num_vals, DBT *vals) /* update multiple DBs */;
  int (*get_redzone)                          (DB_ENV *env, int *redzone) /* get the redzone limit */;
  int (*set_redzone)                          (DB_ENV *env, int redzone) /* set the redzone limit in percent of total space */;
  int (*set_lk_max_memory)                    (DB_ENV *env, uint64_t max);
  int (*get_lk_max_memory)                    (DB_ENV *env, uint64_t *max);
  void (*set_update)                          (DB_ENV *env, int (*update_function)(DB *, const DBT *key, const DBT *old_val, const DBT *extra, void (*set_val)(const DBT *new_val, void *set_extra), void *set_extra));
  int (*set_lock_timeout)                     (DB_ENV *env, uint64_t lock_wait_time_usec);
  int (*get_lock_timeout)                     (DB_ENV *env, uint64_t *lock_wait_time_usec);
  void *api1_internal;
  int  (*close) (DB_ENV *, u_int32_t);
  int  (*dbremove) (DB_ENV *, DB_TXN *, const char *, const char *, u_int32_t);
  int  (*dbrename) (DB_ENV *, DB_TXN *, const char *, const char *, const char *, u_int32_t);
  void (*err) (const DB_ENV *, int, const char *, ...);
  int (*get_cachesize) (DB_ENV *, u_int32_t *, u_int32_t *, int *);
  int (*get_flags) (DB_ENV *, u_int32_t *);
  int  (*get_lg_max) (DB_ENV *, u_int32_t*);
  int  (*get_lk_max_locks) (DB_ENV *, u_int32_t *);
  int  (*log_archive) (DB_ENV *, char **[], u_int32_t);
  int  (*log_flush) (DB_ENV *, const DB_LSN *);
  int  (*open) (DB_ENV *, const char *, u_int32_t, int);
  int  (*set_cachesize) (DB_ENV *, u_int32_t, u_int32_t, int);
  int  (*set_data_dir) (DB_ENV *, const char *);
  void (*set_errcall) (DB_ENV *, void (*)(const DB_ENV *, const char *, const char *));
  void (*set_errfile) (DB_ENV *, FILE*);
  void (*set_errpfx) (DB_ENV *, const char *);
  int  (*set_flags) (DB_ENV *, u_int32_t, int);
  int  (*set_lg_bsize) (DB_ENV *, u_int32_t);
  int  (*set_lg_dir) (DB_ENV *, const char *);
  int  (*set_lg_max) (DB_ENV *, u_int32_t);
  int  (*set_lk_detect) (DB_ENV *, u_int32_t);
  int  (*set_lk_max_locks) (DB_ENV *, u_int32_t);
  int  (*set_tmp_dir) (DB_ENV *, const char *);
  int  (*set_verbose) (DB_ENV *, u_int32_t, int);
  int  (*txn_begin) (DB_ENV *, DB_TXN *, DB_TXN **, u_int32_t);
  int  (*txn_checkpoint) (DB_ENV *, u_int32_t, u_int32_t, u_int32_t);
  int  (*txn_stat) (DB_ENV *, DB_TXN_STAT **, u_int32_t);
};
struct __toku_db_key_range {
  double less;
  double equal;
  double greater;
};
struct __toku_db_lsn {
};
struct __toku_dbt {
  void*data;
  u_int32_t size;
  u_int32_t ulen;
  u_int32_t flags;
};
typedef struct __toku_descriptor {
    DBT       dbt;
} *DESCRIPTOR, DESCRIPTOR_S;
//One header is included in 'data'
//One header is included in 'additional for checkpoint'
typedef struct __toku_db_fragmentation {
  uint64_t file_size_bytes;               //Total file size in bytes
  uint64_t data_bytes;                    //Compressed User Data in bytes
  uint64_t data_blocks;                   //Number of blocks of compressed User Data
  uint64_t checkpoint_bytes_additional;   //Additional bytes used for checkpoint system
  uint64_t checkpoint_blocks_additional;  //Additional blocks used for checkpoint system 
  uint64_t unused_bytes;                  //Unused space in file
  uint64_t unused_blocks;                 //Number of contiguous regions of unused space
  uint64_t largest_unused_block;          //Size of largest contiguous unused space
} *TOKU_DB_FRAGMENTATION, TOKU_DB_FRAGMENTATION_S;
struct __toku_db {
  struct __toku_db_internal *i;
#define db_struct_i(x) ((x)->i)
  int (*key_range64)(DB*, DB_TXN *, DBT *, u_int64_t *less, u_int64_t *equal, u_int64_t *greater, int *is_exact);
  int (*stat64)(DB *, DB_TXN *, DB_BTREE_STAT64 *);
  void *app_private;
  DB_ENV *dbenv;
  int (*pre_acquire_table_lock)(DB*, DB_TXN*);
  int (*pre_acquire_fileops_lock)(DB*, DB_TXN*);
  int (*pre_acquire_fileops_shared_lock)(DB*, DB_TXN*);
  const DBT* (*dbt_pos_infty)(void) /* Return the special DBT that refers to positive infinity in the lock table.*/;
  const DBT* (*dbt_neg_infty)(void)/* Return the special DBT that refers to negative infinity in the lock table.*/;
  int (*row_size_supported) (DB*, u_int32_t) /* Test whether a row size is supported. */;
  DESCRIPTOR descriptor /* saved row/dictionary descriptor for aiding in comparisons */;
  int (*change_descriptor) (DB*, DB_TXN*, const DBT* descriptor, u_int32_t) /* change row/dictionary descriptor for a db.  Available only while db is open */;
  int (*getf_set)(DB*, DB_TXN*, u_int32_t, DBT*, YDB_CALLBACK_FUNCTION, void*) /* same as DBC->c_getf_set without a persistent cursor) */;
  int (*flatten)(DB*, DB_TXN*) /* Flatten a dictionary, similar to (but faster than) a table scan */;
  int (*optimize)(DB*) /* Run garbage collecion and promote all transactions older than oldest. Amortized (happens during flattening) */;
  int (*get_fragmentation)(DB*,TOKU_DB_FRAGMENTATION);
  int (*get_readpagesize)(DB*,u_int32_t*);
  int (*set_readpagesize)(DB*,u_int32_t);
  int (*set_indexer)(DB*, DB_INDEXER*);
  void (*get_indexer)(DB*, DB_INDEXER**);
  int (*verify_with_progress)(DB *, int (*progress_callback)(void *progress_extra, float progress), void *progress_extra, int verbose, int keep_going);
  int (*update)(DB *, DB_TXN*, const DBT *key, const DBT *extra, u_int32_t flags);
  int (*update_broadcast)(DB *, DB_TXN*, const DBT *extra, u_int32_t flags);
  void *api_internal;
  int (*close) (DB*, u_int32_t);
  int (*cursor) (DB *, DB_TXN *, DBC **, u_int32_t);
  int (*del) (DB *, DB_TXN *, DBT *, u_int32_t);
  int (*fd) (DB *, int *);
  int (*get) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t);
  int (*get_flags) (DB *, u_int32_t *);
  int (*get_pagesize) (DB *, u_int32_t *);
  int (*key_range) (DB *, DB_TXN *, DBT *, DB_KEY_RANGE *, u_int32_t);
  int (*open) (DB *, DB_TXN *, const char *, const char *, DBTYPE, u_int32_t, int);
  int (*put) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t);
  int (*remove) (DB *, const char *, const char *, u_int32_t);
  int (*rename) (DB *, const char *, const char *, const char *, u_int32_t);
  void (*set_errfile) (DB *, FILE*);
  int (*set_flags) (DB *, u_int32_t);
  int (*set_pagesize) (DB *, u_int32_t);
  int (*stat) (DB *, void *, u_int32_t);
  int (*truncate) (DB *, DB_TXN *, u_int32_t *, u_int32_t);
  int (*verify) (DB *, const char *, const char *, FILE *, u_int32_t);
};
struct __toku_db_txn_active {
  u_int32_t txnid;
  DB_LSN lsn;
};
typedef struct __toku_txn_progress {
  uint64_t entries_total;
  uint64_t entries_processed;
  uint8_t  is_commit;
  uint8_t  stalled_on_checkpoint;
} *TOKU_TXN_PROGRESS, TOKU_TXN_PROGRESS_S;
typedef void(*TXN_PROGRESS_POLL_FUNCTION)(TOKU_TXN_PROGRESS, void*);
struct txn_stat {
  u_int64_t rollback_raw_count;
};
struct __toku_db_txn {
  DB_ENV *mgrp /*In TokuDB, mgrp is a DB_ENV not a DB_TXNMGR*/;
  DB_TXN *parent;
  int (*txn_stat)(DB_TXN *, struct txn_stat **);
  struct { void *next, *prev; } open_txns;
  int (*commit_with_progress)(DB_TXN*, uint32_t, TXN_PROGRESS_POLL_FUNCTION, void*);
  int (*abort_with_progress)(DB_TXN*, TXN_PROGRESS_POLL_FUNCTION, void*);
  void *api_internal;
  int (*abort) (DB_TXN *);
  int (*commit) (DB_TXN*, u_int32_t);
  u_int32_t (*id) (DB_TXN *);
  char iic[0] __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
#define db_txn_struct_i(x) ((struct __toku_db_txn_internal *)(&(x)->iic))
};
struct __toku_db_txn_stat {
  u_int32_t st_nactive;
  DB_TXN_ACTIVE *st_txnarray;
};
struct __toku_dbc {
  DB *dbp;
  int (*c_getf_first)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_last)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current_binding)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range_reverse)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_pre_acquire_range_lock)(DBC*, const DBT*, const DBT*);
  int (*c_close) (DBC *);
  int (*c_count) (DBC *, db_recno_t *, u_int32_t);
  int (*c_del) (DBC *, u_int32_t);
  int (*c_get) (DBC *, DBT *, DBT *, u_int32_t);
  char iic[0] __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
#define dbc_struct_i(x) ((struct __toku_dbc_internal *)(&(x)->iic))
};
#ifdef _TOKUDB_WRAP_H
#define txn_begin txn_begin_tokudb
#endif
int db_env_create(DB_ENV **, u_int32_t) __attribute__((__visibility__("default")));
int db_create(DB **, DB_ENV *, u_int32_t) __attribute__((__visibility__("default")));
char *db_strerror(int) __attribute__((__visibility__("default")));
const char *db_version(int*,int *,int *) __attribute__((__visibility__("default")));
int log_compare (const DB_LSN*, const DB_LSN *) __attribute__((__visibility__("default")));
int db_env_set_func_fsync (int (*)(int)) __attribute__((__visibility__("default")));
int toku_set_trace_file (char *fname) __attribute__((__visibility__("default")));
int toku_close_trace_file (void) __attribute__((__visibility__("default")));
int db_env_set_func_free (void (*)(void*)) __attribute__((__visibility__("default")));
int db_env_set_func_malloc (void *(*)(size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_realloc (void *(*)(void*, size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_pwrite (ssize_t (*)(int, const void *, size_t, toku_off_t)) __attribute__((__visibility__("default")));
int db_env_set_func_full_pwrite (ssize_t (*)(int, const void *, size_t, toku_off_t)) __attribute__((__visibility__("default")));
int db_env_set_func_write (ssize_t (*)(int, const void *, size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_full_write (ssize_t (*)(int, const void *, size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_fdopen (FILE* (*)(int, const char *)) __attribute__((__visibility__("default")));
int db_env_set_func_fopen (FILE* (*)(const char *, const char *)) __attribute__((__visibility__("default")));
int db_env_set_func_open (int (*)(const char *, int, int)) __attribute__((__visibility__("default")));
int db_env_set_func_fclose (int (*)(FILE*)) __attribute__((__visibility__("default")));
int db_env_set_func_pread (ssize_t (*)(int, void *, size_t, off_t)) __attribute__((__visibility__("default")));
void db_env_set_func_loader_fwrite (size_t (*fwrite_fun)(const void*,size_t,size_t,FILE*)) __attribute__((__visibility__("default")));
void db_env_set_checkpoint_callback (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_checkpoint_callback2 (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_recover_callback (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_recover_callback2 (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_loader_size_factor (uint32_t) __attribute__((__visibility__("default")));
void db_env_set_mvcc_garbage_collection_verification(u_int32_t) __attribute__((__visibility__("default")));
void db_env_enable_engine_status(u_int32_t) __attribute__((__visibility__("default")));
#if defined(__cplusplus)
}
#endif
#endif
