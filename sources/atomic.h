#ifndef OD_ATOMIC_H
#define OD_ATOMIC_H

/*
 * Odissey.
 *
 * Advanced PostgreSQL connection pooler.
*/

typedef volatile uint32_t od_atomic_u32_t;
typedef volatile uint64_t od_atomic_u64_t;

static inline void
od_atomic_u32_inc(od_atomic_u32_t *atomic)
{
	__sync_fetch_and_add(atomic, 1);
}

static inline void
od_atomic_u32_dec(od_atomic_u32_t *atomic)
{
	__sync_fetch_and_sub(atomic, 1);
}

static inline void
od_atomic_u32_add(od_atomic_u32_t *atomic, uint32_t value)
{
	__sync_add_and_fetch(atomic, value);
}

static inline void
od_atomic_u32_sub(od_atomic_u32_t *atomic, uint32_t value)
{
	__sync_sub_and_fetch(atomic, value);
}

static inline void
od_atomic_u64_inc(od_atomic_u64_t *atomic)
{
	__sync_fetch_and_add(atomic, 1);
}

static inline void
od_atomic_u64_dec(od_atomic_u64_t *atomic)
{
	__sync_fetch_and_sub(atomic, 1);
}

static inline void
od_atomic_u64_add(od_atomic_u64_t *atomic, uint64_t value)
{
	__sync_add_and_fetch(atomic, value);
}

static inline void
od_atomic_u64_sub(od_atomic_u64_t *atomic, uint64_t value)
{
	__sync_sub_and_fetch(atomic, value);
}

#endif /* OD_ATOMIC_H */