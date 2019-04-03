#!/usr/bin/python -B
import unittest

def Strassen2x2(A, B):
    M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1])
    M2 = (A[1][0] + A[1][1]) * (B[0][0])
    M3 = (A[0][0]) * (B[0][1] - B[1][1])
    M4 = (A[1][1]) * (B[1][0] - B[0][0])
    M5 = (A[0][0] + A[0][1]) * (B[1][1])
    M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1])
    M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1])
    C = [[M1+M4-M5+M7,M3+M5],
	 [M2+M4,M1-M2+M3+M6]]
    return C

class Stassen2x2TestCase(unittest.TestCase):

    def test1(self):
        A = [[1,  2],
             [3,  4]]
        B = [[2,  0],
             [1,  2]]
        C = Strassen2x2(A, B)

        self.assertTrue(C[0][0] == 4)
        self.assertTrue(C[0][1] == 4)
        self.assertTrue(C[1][0] ==10)
        self.assertTrue(C[1][1] == 8)

    def test2(self):
        A = [[2,  0],
             [1,  2]]
        B = [[1,  2],
             [3,  4]]
        C = Strassen2x2(A, B)

        self.assertTrue(C[0][0] == 2)
        self.assertTrue(C[0][1] == 4)
        self.assertTrue(C[1][0] == 7)
        self.assertTrue(C[1][1] ==10)

if __name__ == '__main__':
    unittest.main()
