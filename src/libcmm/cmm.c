#include "cmm.h"

#define DO_NULL_CHECKS(tb)                              \
do {                                                    \
        if (!tb) {                                      \
                return CMM_TB_STATUS_NULL_REFERENCE;    \
        }                                               \
        if (!tb->base) {                                \
                return CMM_TB_STATUS_NULL_BASE;         \
        }                                               \
} while (0)

CMM_TB_Status cmm_tb_alloc(struct tagged_buffer **tb, size_t type, size_t n)
{
        if (!tb) {
                return CMM_TB_STATUS_NULL_VAL_PASSED;
        }

        DO_NULL_CHECKS(*tb);

        *tb = malloc(sizeof(struct tagged_buffer) + type*n);

        (*tb)->width = type;
        (*tb)->count = n;

        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_free(struct tagged_buffer *tb)
{
        DO_NULL_CHECKS(tb);

        free(tb);
        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_set(struct tagged_buffer *tb, size_t i, const void *src)
{
        DO_NULL_CHECKS(tb);

        if (!src) {
                return CMM_TB_STATUS_NULL_VAL_PASSED;
        }

        if (tb->width * tb->count < i) {
                return CMM_TB_STATUS_WOULD_OVERFLOW;
        }

        size_t offset = tb->width * i;
        memcpy(tb->base + offset, src, tb->width);

        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_get(struct tagged_buffer *tb, size_t i, const void *dst)
{
        DO_NULL_CHECKS(tb);

        if (!src) {
                return CMM_TB_STATUS_NULL_VAL_PASSED;
        }

        if (tb->width * tb->length < i) {
                return CMM_TB_STATUS_OUT_OF_BOUNDS;
        }

        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_push(struct tagged_buffer *tb, void *src)
{
        tb->length++;
        tb->base = realloc(tb->base, tb->width * tb->length);

        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_pop(struct tagged_buffer *tb, void *dst)
{
        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_copy_area(struct tagged_buffer *dst, struct tagged_buffer *src, size_t start, size_t count)
{
        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_shrink(struct tagged_buffer *src, size_t size)
{
        return CMM_TB_STATUS_SUCCESS;
}

CMM_TB_Status cmm_tb_grow(struct tagged_buffer *src, size_t size)
{
        return CMM_TB_STATUS_SUCCESS;
}
