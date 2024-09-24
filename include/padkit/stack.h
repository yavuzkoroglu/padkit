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

    void* peek_stack(Stack const stack[static const 1]);

    void* peekBottom_stack(Stack const stack[static const 1]);

    void* peekBottomN_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* peekN_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* peekTop_stack(Stack const stack[static const 1]);

    void* peekTopN_stack(
        Stack const stack[static const 1],
        uint32_t const n
    );

    void* pop_stack(Stack stack[static const 1]);

    void* popBottom_stack(Stack stack[static const 1]);

    void* popBottomN_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* popN_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* popTop_stack(Stack stack[static const 1]);

    void* popTopN_stack(
        Stack stack[static const 1],
        uint32_t const n
    );

    void* push_stack(
        Stack stack[static const 1],
        void const* const p
    );

    void* pushBottom_stack(
        Stack stack[static const 1],
        void const* const p
    );

    void* pushBottomN_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushIndeterminate_stack(Stack stack[static const 1]);

    void* pushIndeterminateBottom_stack(Stack stack[static const 1]);

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

    void* pushIndeterminateTop_stack(Stack stack[static const 1]);

    void* pushN_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushTop_stack(
        Stack stack[static const 1],
        void const* const p
    );

    void* pushTopN_stack(
        Stack stack[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* pushZero_stack(Stack stack[static const 1]);

    void* pushZeroBottom_stack(Stack stack[static const 1]);

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

    void* pushZeroTop_stack(Stack stack[static const 1]);

    void rotate_stack(Stack stack[static const 1]);

    void rotateDown_stack(Stack stack[static const 1]);

    void rotateDownN_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void rotateN_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void rotateUp_stack(Stack stack[static const 1]);

    void rotateUpN_stack(
        Stack stack[static const 1],
        uint32_t n
    );

    void vconstruct_stack(
        void* const p_stack,
        va_list args
    );
#endif
