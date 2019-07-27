#define _GNU_SOURCE
#include "maputils.h"
#include <stdlib.h>
#include <string.h>
#undef _GNU_SOURCE

/* put key and value to hashmap */
hashentry_t* hashmap_put(hashmap_t **hashmap, uint16_t unique_msgid, uint16_t origin_msgid, int query_timerfd, const inet6_skaddr_t *source_addr) {
    hashentry_t *hashentry = malloc(sizeof(hashentry_t));
    hashentry->unique_msgid = unique_msgid;
    hashentry->origin_msgid = origin_msgid;
    hashentry->query_timerfd = query_timerfd;
    memcpy(&hashentry->source_addr, source_addr, sizeof(inet6_skaddr_t));
    HASH_ADD(hh, *hashmap, unique_msgid, sizeof(uint16_t), hashentry);
    return hashentry;
}

/* get entry_ptr by unique_msgid */
hashentry_t* hashmap_get(hashmap_t *hashmap, uint16_t unique_msgid) {
    hashentry_t *hashentry = NULL;
    HASH_FIND(hh, hashmap, &unique_msgid, sizeof(uint16_t), hashentry);
    return hashentry;
}

/* delete and free the entry from hashmap */
void hashmap_del(hashmap_t **hashmap, hashentry_t *hashentry) {
    HASH_DEL(*hashmap, hashentry);
    free(hashentry);
}