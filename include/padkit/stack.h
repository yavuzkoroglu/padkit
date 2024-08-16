#ifndef STACK_H
    #define STACK_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    typedef struct StackBody {
        size_t      element_size_in_bytes;
        uint32_t    cap;
        uint32_t    size;
        char*       array;
    } Stack;

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_stack(
        Stack* const stack,
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_stack(Stack* const stack);

    bool isValid_stack(Stack const* const stack);

    void* peek_stack(Stack const* const stack);

    void* peekBottom_stack(Stack const* const stack);

    void* peekTop_stack(Stack const* const stack);

    void* pop_stack(Stack* const stack);

    void* popBottom_stack(Stack* const stack);

    void* popTop_stack(Stack* const stack);

    void* push_stack(Stack* const stack, void* const ptr);

    void* pushBottom_stack(Stack* const stack, void* const ptr);

    void* pushTop_stack(Stack* const stack, void* const ptr);

    void* pushZeros_stack(Stack* const stack);

    void* pushZerosBottom_stack(Stack* const stack);

    void* pushZerosTop_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    reallocIfNecessary_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotate_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateDown_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateUp_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    reverse_stack(Stack* const stack);

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    swap_stacks(Stack* const stack_A, Stack* const stack_B);
#endif
