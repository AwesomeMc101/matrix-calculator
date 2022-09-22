/*
* MatrixCalculator.cpp
* 9/21/2022
* Written by AwesomeMc101 for LunarGuard LLC
* Licensed under MIT
*/
#include "Matrix.h"

#include <iostream>
#include <string.h>
#include <string>
#include <map>

#define ADD 1 //add
#define SUB 2 //subtract
#define MUL 3 //multiply
#define SCA 4 //scalar

std::vector<Matrix> matrices;


namespace IO {
    namespace Drawing
    {
        void drawMatrix(Matrix matrix)
        {
            //only draws, no built-in clear function
            int pos = 0;


            /* Anti-crash checker, WILL BE USED OFTEN
            FOR DRAWER WHILE ENTERING VALUES!!*/

            if (matrix.vals.size() != (matrix.rows * matrix.cols))
            {
                std::cout << "size mismatch\n";
                while(matrix.vals.size() != (matrix.rows * matrix.cols))
                {
                    matrix.vals.push_back(0);
                }
            }

            for (int i = 0; i < matrix.rows; i++)
            {
                std::vector<double> senders;

                for (int z = 0; z < matrix.cols; z++)
                {
                    senders.push_back(matrix.vals[pos + z]); //pushback z + current position (looping + correct starting spot)
                }

                std::cout << "[";
                for (double z : senders)
                {
                    std::cout << "  " << z;
                }
                std::cout << "  ]\n";

                pos += matrix.cols;
            }
        }
    }

    namespace Mathematics
    {
        //works by generating a new matrix lol
        void add(Matrix A, Matrix B)
        {
            system("cls");
            if (A.cols != B.cols || A.rows != B.rows || A.vals.size() != B.vals.size())
            {
                std::cout << "[MATHLIB] size mismatch between two matrix (ADDITION)" << std::endl;
            }

            Matrix C;
            C.rows = A.rows;
            C.cols = A.cols;

            for (int i = 0; i < A.vals.size(); i++)
            {
                C.vals.push_back((A.vals[i] + B.vals[i]));
            }

            std::cout << "- Your Result -\n";
            IO::Drawing::drawMatrix(C);
        }
        void sub(Matrix A, Matrix B)
        {
            system("cls");
            if (A.cols != B.cols || A.rows != B.rows || A.vals.size() != B.vals.size())
            {
                std::cout << "[MATHLIB] size mismatch between two matrix (SUBTRACTION)" << std::endl;
            }

            Matrix C;
            C.rows = A.rows;
            C.cols = A.cols;

            for (int i = 0; i < A.vals.size(); i++)
            {
                C.vals.push_back((A.vals[i] - B.vals[i]));
            }

            std::cout << "- Your Result -\n";
            IO::Drawing::drawMatrix(C);
        }
        void mul(Matrix A, Matrix B)
        {
            // 2 x 3 && 3 x 5
            system("cls");
            if (A.vals.size() != B.vals.size() || A.cols != B.rows)
            {
                std::cout << "[MATHLIB] size mismatch between two matrix (MULTIPLICATION)" << std::endl;
            }

            Matrix C;
            C.cols = B.cols;
            C.rows = A.rows;

            float a_set = 0;
            int b_start = 0;
            int a_counter = 0;
            for (int i = 0; i < (C.rows * C.cols); i++)
            {
                //A cols == how many in the row
                //B rows == how many asre being multiplied (use rows)
                //C.vals.push_back((A.vals[i] - B.vals[i]));
                int posA = (floor(a_set) * A.cols), posB = (floor(a_set) * B.rows); //MAYBE a.cols/a.rows IF BREAKING !!!!
                std::vector<double> sendersA, sendersB;
                

                int begin = (floor(a_set) * A.cols);
                if (begin >= (C.cols * C.rows))
                {
                    continue;
                }
                for (int z = 0; z < A.cols; z++)
                {
                    sendersA.push_back(A.vals[begin + z]); //pushback z + current position (looping + correct starting spot)
                }

              
                int ourPos = b_start;
                for (int non = 0; non < B.rows; non++)
                {
                    sendersB.push_back(B.vals[ourPos]);
                    ourPos += B.cols;
                }

                double finalSum = 0;
                for (int t = 0; t < sendersA.size(); t++)
                {
                    
                    finalSum += (sendersA[t] * sendersB[t]);
                }
                C.vals.push_back(finalSum);
                a_counter++;
                if (a_counter == A.cols)
                {
                    a_set++;
                    a_counter = 0;
                }
                
                b_start++;
                if ((b_start + 1) > B.cols)
                {
                    b_start = 0;
                }
            }



            std::cout << "- Your Result -\n";
            IO::Drawing::drawMatrix(C);
        }
        void scale(Matrix A, double scale)
        {
            system("cls");

            Matrix C = A;
            C.vals.clear();


            for (int i = 0; i < A.vals.size(); i++)
            {
                C.vals.push_back((A.vals[i]) * scale);
            }

            std::cout << "- Your Result -\n";
            IO::Drawing::drawMatrix(C);
        }

    }

    Matrix getNewMatrix()
    {
        Matrix m;
        std::cout << "\nHow many rows? Integer only. ";
        int rows = 0;
        std::cin >> rows;
        m.rows = rows;

        std::cout << "\nHow many columns? Integer only. ";
        int cols = 0;
        std::cin >> cols;
        m.cols = cols;
        
        for (int i = 0; i < (rows * cols); i++)
        {
            system("cls");
            Drawing::drawMatrix(m);
            std::cout << "\n\nEnter a value (" << i << "/" << (rows * cols) << "): ";
            double x;
            std::cin >> x;
            m.vals.push_back(x);
        }
        system("cls");
        Drawing::drawMatrix(m);
        std::cout << "What would you like to name your matrix? Case-sensitive in the future. No spaces. ";
        std::string name = "";
        std::cin >> name;

        m.name = name;

        matrices.push_back(m);
        return m;
    }
    void listMatrices()
    {
        for (Matrix matrix : matrices)
        {
            std::cout << "--------------------------\n";
            std::cout << "Matrix Name: " << matrix.name << std::endl;
            std::cout << "Dimensions: " << matrix.rows << " x " << matrix.cols << std::endl;
            std::cout << "\n";
            Drawing::drawMatrix(matrix);
            std::cout << "\n\n";
        }
    }
    int mathType()
    {
        //return ADD;
        std::cout << "Would you like to ADD, SUB[tract], MUL[tiply], or SCA[le] (Only type the caps)? ";
        std::string type = "";
        std::cin >> type;
        if (type == "ADD")
        {
            std::cout << "What two matrices would you like to add? Use their names. ";
            std::string matrixA = "";
            std::cin >> matrixA;
            std::cout << "\nAnd the other: ";
            std::string matrixB = "";
            std::cin >> matrixB;

            Matrix A, B;
            for (Matrix ma : matrices)
            {
                if (ma.name == matrixA)
                {
                    A = ma;
                }
                if (ma.name == matrixB)
                {
                    B = ma;
                }
            }
            Mathematics::add(A, B);
        }
        if (type == "SUB")
        {
            std::cout << "What two matrices would you like to subtract? Use their names. ";
            std::string matrixA = "";
            std::cin >> matrixA;
            std::cout << "\nAnd the other: ";
            std::string matrixB = "";
            std::cin >> matrixB;

            Matrix A, B;
            for (Matrix ma : matrices)
            {
                if (ma.name == matrixA)
                {
                    A = ma;
                }
                if (ma.name == matrixB)
                {
                    B = ma;
                }
            }
            Mathematics::sub(A, B);
        }
        if (type == "MUL")
        {
            std::cout << "What two matrices would you like to multiply? Use their names. ";
            std::string matrixA = "";
            std::cin >> matrixA;
            std::cout << "\nAnd the other: ";
            std::string matrixB = "";
            std::cin >> matrixB;

            Matrix A, B;
            for (Matrix ma : matrices)
            {
                if (ma.name == matrixA)
                {
                    A = ma;
                }
                if (ma.name == matrixB)
                {
                    B = ma;
                }
            }
            Mathematics::mul(A, B);
        }
        if (type == "SCA")
        {
            std::cout << "What matrix would you like to scale? Enter the name. ";
            std::string matrixA = "";
            std::cin >> matrixA;
            std::cout << "\nBy how much? ";
            double scalar = 0;
            std::cin >> scalar;

            Matrix A;
            for (Matrix ma : matrices)
            {
                if (ma.name == matrixA)
                {
                    A = ma;
                }
            }
            Mathematics::scale(A, scalar);
        }
        return 0;
    }

    void getInput()
    {
        entry:
        std::cout << "What would you like to do?\nNEW - new matrix\nLIST - list matrices\nMATH - perform math\n";
        std::string type = "";
        std::cin >> type;


        if (type == "NEW")
        {
            getNewMatrix();
        }
        else if (type == "LIST")
        {
            listMatrices();
        }
        else if (type == "MATH")
        {
            mathType();
        }
        else
        {
            std::cout << "Couldn't understand '" + type + "' Try again.\n";
            goto entry;
        }
    }
}

void fakeMatrices()
{
    for (int i = 0; i < 2; i++)
    {
        Matrix m;
        m.cols = 4;
        m.rows = 4;
        m.vals = { 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
        switch (i)
        {
        case 0:
            m.name = "A";
            break;
        case 1:
            m.name = "B";
            break;
        }
        matrices.push_back(m);
    }
}

int main()
{
    /*
    std::vector<double> vec = { 1,2,3,4,5};
    Matrix m = newMatrix(3, 2, vec);
    IO::Drawing::drawMatrix(m);
    */
    fakeMatrices();

    for (;;)
    {
        IO::getInput();
    }
}

