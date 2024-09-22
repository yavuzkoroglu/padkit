#ifndef PADKIT_STACK_H
    #define PADKIT_STACK_H
    #include "padkit/arraylist.h"

    #define NOT_A_STACK                     NOT_AN_ALIST

    #define STACK_RECOMMENDED_INITIAL_CAP   ALIST_RECOMMENDED_INITIAL_CAP

    typedef ArrayList Stack;

    void construct_stack(void* const p_stack, ...);

    void constructEmpty_stack(
        Stack stack[static const 1],
        size_t const sz_elem,
        uint32_t const init_cap
    );

    void destruct_stack(void* const p_stack);

    void flush_stack(Stack stack[static const 1]);

    bool isAllocated_stack(void const* const p_stack);

    bool isValid_stack(void const* const p_stack);

    void* peek_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* peekBottom_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* peekTop_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* pop_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* popBottom_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* popTop_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* push_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushBottom_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushIndeterminates_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* pushIndeterminatesBottom_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* pushIndeterminatesTop_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* pushTop_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushZeros_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* pushZerosBottom_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* pushZerosTop_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void rotate_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void rotateDown_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void rotateUp_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void vconstruct_stack(
        void* const p_stack,
        va_list args
    );
#endif
