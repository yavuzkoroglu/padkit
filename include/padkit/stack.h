#ifndef PADKIT_STACK_H
    #define PADKIT_STACK_H
    #include "padkit/arraylist.h"

    #define NOT_A_STACK                     NOT_AN_ALIST

    #define STACK_RECOMMENDED_INITIAL_CAP   ALIST_RECOMMENDED_INITIAL_CAP

    typedef ArrayList Stack;

    void constructEmpty_stack(
        Stack stack[static const 1],
        size_t const sz_element,
        uint32_t const initial_cap
    );

    void flush_stack(Stack stack[static const 1]);

    void free_stack(Stack stack[static const 1]);

    bool isValid_stack(Stack const stack[static const 1]);

    void* peek_stack(Stack const stack[static const 1], uint32_t const n);

    void* peekBottom_stack(Stack const stack[static const 1], uint32_t const n);

    void* peekTop_stack(Stack const stack[static const 1], uint32_t const n);

    void* pop_stack(Stack stack[static const 1], uint32_t const n);

    void* popBottom_stack(Stack stack[static const 1], uint32_t const n);

    void* popTop_stack(Stack stack[static const 1], uint32_t const n);

    void* push_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    void* pushBottom_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    void* pushIndeterminate_stack(Stack stack[static const 1], uint32_t const n);

    void* pushIndeterminateBottom_stack(Stack stack[static const 1], uint32_t const n);

    void* pushIndeterminateTop_stack(Stack stack[static const 1], uint32_t const n);

    void* pushTop_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    void* pushZeros_stack(Stack stack[static const 1], uint32_t const n);

    void* pushZerosBottom_stack(Stack stack[static const 1], uint32_t const n);

    void* pushZerosTop_stack(Stack stack[static const 1], uint32_t const n);

    void rotate_stack(Stack stack[static const 1], uint32_t n);

    void rotateDown_stack(Stack stack[static const 1], uint32_t n);

    void rotateUp_stack(Stack stack[static const 1], uint32_t n);
#endif
