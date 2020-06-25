#include <math.h>

//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     VLADISLAV PASTUSHENKO <xpastu04@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author VLADISLAVASTUSHENKO
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"



TEST(MatrixTest, Constructor) {
    ASSERT_NO_THROW(Matrix());
    ASSERT_NO_THROW(Matrix(1, 1));
    ASSERT_NO_THROW(Matrix(10, 11));
    ASSERT_NO_THROW(Matrix(11, 10));
    ASSERT_NO_THROW(Matrix(10, 10));
    
    ASSERT_ANY_THROW(Matrix(0, 0));
    ASSERT_ANY_THROW(Matrix(0, 10));
    ASSERT_ANY_THROW(Matrix(10, 0));
    
}

TEST(MatrixTest, Setter_1) {
    Matrix m_1 = Matrix();
    
    ASSERT_TRUE(m_1.set(0, 0, 10));
    ASSERT_TRUE(m_1.set(0, 0, -10));
    ASSERT_TRUE(m_1.set(0, 0, 0));
    
    ASSERT_FALSE(m_1.set(0, 1, 0));
    ASSERT_FALSE(m_1.set(1, 0, 0));
    ASSERT_FALSE(m_1.set(-1, -1, 0));
    
    Matrix m_2 = Matrix(10, 10);
    
    ASSERT_TRUE(m_2.set(4, 1, 10));
    ASSERT_TRUE(m_2.set(9, 5, -10));
    ASSERT_TRUE(m_2.set(2, 4, 0));
    
    ASSERT_FALSE(m_2.set(10, 10, 0));
    ASSERT_FALSE(m_2.set(1, 124, 0));
    ASSERT_FALSE(m_2.set(124, 1, 0));
    ASSERT_FALSE(m_2.set(2, -1, 0));
    ASSERT_FALSE(m_2.set(-2, 1, 0));
}

TEST(MatrixTest, Setter_2) {
    Matrix m_1 = Matrix();
    
    ASSERT_TRUE(m_1.set(std::vector<std::vector<double>>{{10}}));

    ASSERT_FALSE(m_1.set(std::vector<std::vector<double>>{{1}, {-1}, {0}}));
    ASSERT_FALSE(m_1.set(std::vector<std::vector<double>>(0, std::vector<double>(0, 0))));
    
    Matrix m_2 = Matrix(3, 3);
    ASSERT_TRUE(m_2.set(std::vector<std::vector<double>>{{1, 2, 3}, {-1, -1, -1}, {0, 1, 2}}));

    ASSERT_FALSE(m_2.set(std::vector<std::vector<double>>{{1}}));
    ASSERT_FALSE(m_2.set(std::vector<std::vector<double>>{{1}, {-1}, {0}}));
    ASSERT_FALSE(m_2.set(std::vector<std::vector<double>>{{1, 1}, {-1, -1, 2}, {0, 2, 2}}));

}

TEST(MatrixTest, Getter){
    Matrix m_1 = Matrix();
    m_1.set(0, 0, 10);
    
    ASSERT_EQ(10, m_1.get(0, 0));
    
    ASSERT_ANY_THROW(m_1.get(0, 1));
    ASSERT_ANY_THROW(m_1.get(1, 0));
    
    
    Matrix m_2 = Matrix(3, 3);
    m_2.set(std::vector<std::vector<double>>{{1, 2, 3}, {-1, -1, -1}, {0, 1, 2}});
    
    ASSERT_EQ(1, m_2.get(0, 0));
    ASSERT_EQ(-1, m_2.get(1, 2));
    ASSERT_EQ(1, m_2.get(2, 1));
    
    ASSERT_ANY_THROW(m_2.get(-1, 0));
    ASSERT_ANY_THROW(m_2.get(10, 2));
    ASSERT_ANY_THROW(m_2.get(2, 3));

}


TEST(MatrixTest, Equality){
    Matrix m_1 = Matrix(3, 3);
    Matrix m_2 = Matrix(3, 3);
    Matrix m_3 = Matrix(3, 6);
    Matrix m_4 = Matrix(6, 3);

    m_1.set(std::vector<std::vector<double>>{{1, 2, 3}, {-1, -1, -1}, {0, 1, 2}});
    m_2.set(std::vector<std::vector<double>>{{1, 2, 3}, {-1, -1, -1}, {0, 1, 2}});
    ASSERT_TRUE(m_1 == m_2);
    
    
    m_2.set(std::vector<std::vector<double>>{{1, 1, 1}, {-1, -1, -1}, {0, 0, 0}});
    ASSERT_FALSE(m_1 == m_2);
    
    
    ASSERT_ANY_THROW(m_1 == m_3);
    ASSERT_ANY_THROW(m_1 == m_4);
    ASSERT_ANY_THROW(m_3 == m_4);
}


TEST(MatrixTest, Addition) {
    Matrix m_1 = Matrix(3, 3);
    Matrix m_2 = Matrix(3, 3);
    Matrix m_3 = Matrix(3, 6);
    Matrix m_4 = Matrix(6, 3);
    
    
    Matrix result = Matrix(3, 3);
    Matrix expected = Matrix(3, 3);
    
    m_1.set(std::vector<std::vector<double>>{{1, 2, 3}, {1, 1, 1}, {0, 0, 0}});
    m_2.set(std::vector<std::vector<double>>{{1, 1, 1}, {-1, -1, -1}, {0, 1, 2}});
    
    // Set the real result of addition
    result = m_1 + m_2;
    
    // Set the expected result
    expected.set(std::vector<std::vector<double>>{{2, 3, 4}, {0, 0, 0}, {0, 1, 2}});
    
    // Compare expected and real result
    ASSERT_TRUE(expected == result);
    
    // Try to add matrixes with different quantity of rows and cols
    ASSERT_ANY_THROW(m_1 + m_3);
    ASSERT_ANY_THROW(m_1 + m_4);
    ASSERT_ANY_THROW(m_3 + m_4);

}


TEST(MatrixTest, Multiplication) {
    Matrix m_1 = Matrix(3, 3);
    Matrix m_2 = Matrix(3, 3);
    Matrix m_3 = Matrix(4, 3);
    Matrix m_4 = Matrix(3, 1);
    Matrix result = Matrix(3, 3);
    Matrix expected = Matrix(3, 3);
    
    m_1.set(std::vector<std::vector<double>>{{15, 10, 20}, {1, 2, 3}, {-2, 3, -4}});
    m_2.set(std::vector<std::vector<double>>{{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
    
    // Set the real result of multiplication
    result = m_1 * m_2;
    
    // Set the expected result
    expected.set(std::vector<std::vector<double>>{{240, 285, 330}, {36, 42, 48}, {-21, -24, -27}});
    
    // Compare expected and real result
    ASSERT_TRUE(expected == result);
    
    // Try to multiply matrixes with improper quantity of rows and cols 
    ASSERT_ANY_THROW(m_1 * m_3);
    ASSERT_ANY_THROW(m_4 * m_1);
    
    // Try to add matrixes with different, but proper quantity of rows and cols
    ASSERT_NO_THROW(m_1 * m_4);
    
    
    // Test of multiplying of matrixes 2x1 and 1x2
    m_1 = Matrix(2, 1);
    m_2 = Matrix(1, 2);
    m_1.set(std::vector<std::vector<double>>{{3}, {4}});
    m_2.set(std::vector<std::vector<double>>{{5, 6}});
    
    result = m_1 * m_2;
    expected = Matrix(2, 2);
    expected.set(std::vector<std::vector<double>>{{15, 18}, {20, 24}});

    ASSERT_TRUE(expected == result);
    

}


TEST(MatrixTest, MultiplicationByConst) {

    Matrix m_1 = Matrix();
    Matrix m_2 = Matrix(3, 3);
    Matrix m_3 = Matrix(2, 1);
    Matrix m_4 = Matrix(1, 2);
    Matrix expected = Matrix();
    
     // Test with 1x1 matrix
    m_1.set(0, 0, 3);
    
    // Set the real result
    Matrix result = m_1 * 2;
    
    // Set the expexted reuslt
    expected.set(0, 0, 6);
    
    // Compare expected and real result
    ASSERT_TRUE(expected == result);
    
    // Test with 3x3 matrix
    m_2.set(std::vector<std::vector<double>>{{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
    
    result = m_2 * -2;
    
    expected = Matrix(3, 3);
    expected.set(std::vector<std::vector<double>>{{-4, -6, -8}, {-10, -12, -14}, {-16, -18, -20}});
    
    ASSERT_TRUE(expected == result);
    
    
    // Test with 2x1 matrix
    m_3.set(std::vector<std::vector<double>>{{3}, {4}});
    
    result = m_3 * 3;
    
    expected = Matrix(2, 1);
    expected.set(std::vector<std::vector<double>>{{9}, {12}});
    
    ASSERT_TRUE(expected == result);
    
    // Test with 1x2 matrix
    m_4.set(std::vector<std::vector<double>>{{5, 6}});
    
    result = m_4 * -3;
    
    expected = Matrix(1, 2);
    expected.set(std::vector<std::vector<double>>{{-15, -18}});
    
    ASSERT_TRUE(expected == result);
}

TEST(MatrixTest, Equation) {
    
    // Test with 3x3 matrix
    
    // Set the expected result 
    std::vector<double> expected = {1, 2, 3};
    
    Matrix m_1 = Matrix(3, 3);
    m_1.set(std::vector<std::vector<double>>{{1, 1, 1}, {2, 1, 1}, {3, 4, 5}});
    
    // Set the real result 
    std::vector<double> result = m_1.solveEquation(std::vector<double> {6, 7, 26});
    
    // Compare real and expected results
    ASSERT_TRUE(expected == result);
    
    // Try to solve equation wtih improper quantity of roots of the equation
    ASSERT_ANY_THROW(m_1.solveEquation(std::vector<double> {6, 7, 26, 0}));
    
    
    // Test with 1x1 matrix
    
    Matrix m_2 = Matrix();
    m_2.set(0, 0, 42);
    
    // Solve the equation 
    result = m_2.solveEquation(std::vector<double> {126});
    
    // Set the expected result
    expected = {3};
    
    // Compare real and expexted results
    ASSERT_TRUE(expected == result);
    
    
    // Test with 5x5 matrix 
    Matrix m_3 = Matrix(5, 5);
    
    m_3.set(std::vector<std::vector<double>>{{1, 2, 3, 4, 5}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}, {1, 0, 0, 0, 0}, {0, 0, 1, 0, 0}});
    
    // Try to solve the equation
    ASSERT_NO_THROW(m_3.solveEquation(std::vector<double> {55, 15, 5, 1, 3}));
    
    
    // Test matrix with improper quantity of cells (1x2)
    Matrix m_4 = Matrix(1, 2);
    ASSERT_ANY_THROW(m_4.solveEquation(std::vector<double> {0}));
    
    // Test matrix with improper quantity of cells (4x5)
    Matrix m_5 = Matrix(4, 5);
    ASSERT_ANY_THROW(m_5.solveEquation(std::vector<double> {0, 0, 0, 0, 0}));
                     
    // Test with not regular matrix                  
    Matrix m_6 = Matrix(2, 2);
    m_6.set(std::vector<std::vector<double>>{{2, 4}, {1, 2}});
    ASSERT_ANY_THROW(m_6.solveEquation(std::vector<double> {0, 0}));
    
}


/*** Konec souboru white_box_tests.cpp ***/
