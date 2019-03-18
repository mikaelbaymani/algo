#!/usr/bin/python -B
from math import log
from random import choice
Booleans = lambda N: [choice([True, False]) for _ in range(N+1)]
Literal = lambda L, AoB: not AoB[-L] if L < 0 else AoB[L]# AoB=Array Of Bools
# Papadimitriou's 2-SAT Algorithm
# Repeat log2 n times:                                    (n = number
# - choose random initial assignment                       of variables)
# - repeat 2n^2 times:
#   - if current assignment satifies all clauses, halt + report this
#   - else, pick arbitrary unsatisfied clause and flip the value of
#     one of its variables [choose between the two uniformly at random].
# Report "unsatisfiable"
def papadimitriou(no_of_variables, no_of_clauses, set_of_clauses):
    # Each entry in the set_of_clauses specifies a clause via its two literals,
    # (the literals are represented as a tuple) with a number denoting the
    # variable and a "-" sign denoting logical "not". For example, one entry
    # in the set can look like: (-16808, 75250), which indicates the clause
    # !x_16808 V x_75250.
    for _ in xrange(0, int( log(no_of_variables)/log(2) )):# Repeat log2 n times:
        booleans = Booleans(no_of_variables)               # - choose random initial assignment
        for __ in xrange(0, 2*(no_of_clauses**2)):         # - repeat 2n^2 times:
            satisfies_all_clauses = True
            for clause in set_of_clauses:
                literal_1 = Literal(clause[0], booleans)
                literal_2 = Literal(clause[1], booleans)

                if literal_1 or literal_2:
                    pass
                else:
                    satisfies_all_clauses = False
                    break

            if satisfies_all_clauses:                      #   - if current asignment satisfies all
                return True, booleans                      #     clauses, halt + report this
            else:                                          #   - else, pick arbitrary unsatisfied
                i = abs(choice([clause[0],clause[1]]))     #     clause and flip the value of one of
                booleans[i] = not booleans[i]              #     its variable

    return False, []                                       # Report "unsatisfiable"
# EOF
