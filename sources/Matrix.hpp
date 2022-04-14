/**
 * @file Matrix.hpp
 * @author Ohad Maday (maday.ohad.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <bits/stdc++.h>

namespace zich{ 
    const int UPPER = 57; // Ascii number below equal are digits
    const int LOWER = 48; // Ascii number above equal are digits
    /**
     * @brief Matrix class which uses vector as it data structure to store data (numbers within the matrix)
     * ROWS - dimension of the matrix
     * COLS - dimension of the matrix
     * Therefore, matrix size of ROWSxCOLS
     * 
     * The class holds various legal operations that done between matrice (or the matrix itself):
     * Let a,b matrice, num - a random whole/real number in R such that:     
     * 
     * list of operators -
     *      a + b
     *      a += b
     *      a + (unary)
     * 
     *      a - b
     *      a -= b
     *      a - (unary)
     * 
     *      a++
     *      ++a
     *      a--
     *      --a
     * 
     *      a*num
     *      num*a
     *      a*b
     *      a*=b
     * 
     * 
     */
    
    class Matrix{
        // Private type is class default
        std::vector<double> MAT; // Data structure which holds double
        int ROW;                 // Integer - ROWS of the matrix
        int COL;                 // Integer - COLumns of the matrix

        public:
        Matrix(const std::vector<double> &v, int row, int col);


        //Arithmetic Operators
        Matrix operator+(const Matrix& mat);   // a + b
        Matrix operator+=(const Matrix& mat);  // a = a + b 
        Matrix operator+();                    // Unary +
        Matrix operator-(const Matrix& mat);   // a - b
        Matrix operator-=(const Matrix& mat);  // a = a - b
        Matrix operator-();                    // Unary -


        /*
        * Boolean Operators
        * I do not want to mess with the result of the function, that's why the functions below are const 
        */
        bool operator< (const Matrix& mat)  const; // a <  b 
        bool operator<= (const Matrix& mat) const; // a <= b
        bool operator> (const Matrix& mat)  const; // a >  b
        bool operator>= (const Matrix& mat) const; // a >= b
        friend bool operator==(const Matrix &a, const Matrix &b); // a == b
        friend bool operator!= (const Matrix &a, const Matrix &b); // a != b

        /*
        *  Prefix Operators
        */
        Matrix& operator++ (); // ++a
        Matrix& operator-- (); // --a
        
        /*
        *  Postfix Operators
        */
        Matrix operator++ (int); // a++
        Matrix operator-- (int); // a--

        /*
        *  Multipication Operators - scalar multipication + another matrix
        */
        Matrix operator* (const Matrix &mat) const;                // a * b
        Matrix operator* (double num1);                            // num * a
        Matrix operator*= (double num1);                           // a = a * num
        Matrix operator*= (const Matrix &mat);                     // a = a * b
        friend Matrix operator*= (double num1, Matrix & mat);      // a = b * num 
        friend Matrix operator*(double number, const Matrix &mat); // a * num


        /*
        * Stream Operators: 
        * cin >> [1 0 0], [0 1 0], [0 0 1] 
        * cout << "[3 0 0]\n[0 3 0]\n[0 0 3]";
        */
        friend std::ostream& operator<<( std::ostream& os, const Matrix& mat);
        friend std::istream& operator>>( std::istream &source, Matrix &mat);

        /**
         * @brief Getters for rows colums and matrix itself
         * 
         * @return int 
         */
        int getRows() const;
        int getCols() const;
        std::vector<double> getMat() const;

        /**
         * @brief An helping function which check if the dimensions are ok -
         *  coin : true  -> normal arithmetic operations (addition,subtraction) -> a.col == b.col && a.row == b.row
         *         false -> for multipication -> a.col == b.row 
         * @param a 
         * @param b 
         * @param coin 
         */
        friend void ValidateDimensions(const Matrix& a,const Matrix& b,bool coin);
    };

    // ---------- Helping functions -----------
    /**
     * @brief Sum the numbers within the vector, used in functions such as +,-,-=,+=
     * 
     * @param mat 
     * @return sum of the variables 
     */
    double SumMatrix(const Matrix& mat);

    /**
     * @brief Turns the istream into a string with getline function
     * --------------used in >> opeartor overloading---------------
     * @param input 
     * @return string
     */
    std::string toString(std::istream& input);

    /**
     * @brief Turns a string with a special delimiter into a vector of doubles
     * --------------used in >> opeartor overloading---------------
     * @param s 
     * @param delim 
     * @return vector<double> 
     */
    std::vector<double> split(const std::string &s, char delim);


    

    
}