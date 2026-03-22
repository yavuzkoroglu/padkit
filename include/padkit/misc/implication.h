/**
 * @file implication.h
 * @brief A macro for logical implication.
 * @author Yavuz KÖROĞLU
 * @see Law of Implication.
 */
#ifndef PADKIT_MISC_IMPLICATION_H
    #define PADKIT_MISC_IMPLICATION_H

    /**
     * @brief <tt>(p -> q) = (!p || q) </tt>.
     * @param p The antecedant as a Boolean.
     * @param q The consequent as a Boolean.
     * @returns <tt>(p -> q) = (!p || q) </tt>.
     * @see Law of Implication.
     */
    #define IMPLIES(p,q) (!(p) || (q))
#endif
