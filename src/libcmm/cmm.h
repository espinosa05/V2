#ifndef __LIB_CMM_H__
#define __LIB_CMM_H__

/* TODO: move this to a utility file */
#define __inline__ __attribute__((always_inline))

struct tagged_buffer {
        size_t count;
        size_t width;
        void *base;
};

typedef size_t CMM_TB_Status;

enum {
        CMM_TB_STATUS_ALLOC_FAILED_ENOMEM = 0,
        CMM_TB_STATUS_FREE_FAILED_DOUBLE_FREE,
        CMM_TB_STATUS_BUFFER_WOULD_OVERFLOW,
        CMM_TB_STATUS_BUFFER_WOULD_UNDERFLOW,
        CMM_TB_STATUS_BUFFER_INDEX_OVERSHOT,
        CMM_TB_STATUS_BUFFER_INDEX_UNDERSHOT,
        CMM_TB_STATUS_GROWN_BUFFER_ACTUALLY_SMALLER,
        CMM_TB_STATUS_SHRUNK_BUFFER_ACTUALLY_BIGGER,
        CMM_TB_STATUS_NULL_REFERENCE,
        CMM_TB_STATUS_NULL_BASE,
        CMM_TB_STATUS_NULL_VAL_PASSED,

        CMM_TB_STATUS_N_STATUS,
        CMM_TB_STATUS_SIZE_GUARD = (SIZE_MAX),
};

TB_Status cmm_tb_alloc(struct tagged_buffer **tb, size_t type, size_t n);
TB_Status cmm_tb_free(struct tagged_buffer *tb);

__inline__ CMM_TB_Status cmm_tb_push(struct tagged_buffer *tb, void *src);
__inline__ CMM_TB_Status cmm_tb_pop(struct tagged_buffer *tb, void *dst);

__inline__ CMM_TB_Status cmm_tb_copy_area(struct tagged_buffer *dst, struct tagged_buffer *src, size_t start, size_t count);

__inline__ CMM_TB_Status cmm_tb_shrink(struct tagged_buffer *src, size_t size);
__inline__ CMM_TB_Status cmm_tb_grow(struct tagged_buffer *src, size_t size);

#endif /* __LIB_CMM_H__ */
