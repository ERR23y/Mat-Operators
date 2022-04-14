/**
 * @file Matrix.cpp
 * @author Ohad Maday (maday.ohad.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Matrix.hpp"
/**
 * @brief General documentation is written in the header file ("Matrix.hpp")
 *        Deep documentation is written here :)
 * 
 */
namespace zich{
    Matrix::Matrix(const std::vector<double> &v, int row, int col){
        // Validate amount of numbers within the vector against rows & col 
        if (row*col != v.size())
        {
            throw std::invalid_argument("Amount of Numbers does not match the Rows and Cols");
        }

        // Validates that the cols/rows aren't negative (ever seen a matrix with negative rows/cols????)
        if ((row < 0 || col < 0 ) || (row < 0 && col < 0 ))
        {
            throw std::invalid_argument("Matrice cannot have negative rows/cols");
        }
         
        this->ROW = row;
        this->COL = col;
        this->MAT = v;
    }


    /**
    * @brief Basic arithmetic operators===--- 
    */
    Matrix Matrix::operator+(const Matrix& mat){
        ValidateDimensions(*this,mat,true); // Validates same rows & cols
        std::vector<double> v;
        size_t size = this->MAT.size();
        size_t i = 0;
        while(i < size){
            v.push_back(this->MAT.at(i) + mat.getMat().at(i));
            i++;
        } 
        
        return Matrix(v,ROW, COL);
    }

    Matrix Matrix::operator+=(const Matrix& mat){
        ValidateDimensions(*this,mat,true); // Validates same rows & cols
        std::vector<double> v;
        size_t size = this->MAT.size();
        size_t i = 0;
        while(i < size){
            this->MAT.at(i) += mat.getMat().at(i); // Addition
            i++;
        }
        
        return *this;
    }

    Matrix Matrix::operator+(){
        return Matrix(this->MAT, this->ROW,this->COL);
    }

    Matrix Matrix::operator-(const Matrix& mat){
        ValidateDimensions(*this,mat,true); // Validates same rows & cols
        std::vector<double> v;
        size_t size = this->MAT.size();
        size_t i = 0;
        while(i < size){
            v.push_back(this->MAT.at(i)-mat.getMat().at(i)); // Subtracting
            i++;
        } 

        return Matrix(v,ROW,COL);
    }

    Matrix Matrix::operator-=(const Matrix& mat){
        ValidateDimensions(*this,mat,true); // Validates same rows & cols
        std::vector<double> v;
        size_t size = this->MAT.size();
        size_t i = 0;
        while(i < size){ // Subtracting every number within the matrix
            this->MAT.at(i) -= mat.getMat().at(i); 
            i++; 
        }

        return *this;
    }

    Matrix Matrix::operator-(){
        return (*this)*(-1); // Multiply the whole matrix with a -1
    }

    /**
    * @brief Booleanic operators===----
    */

    bool Matrix::operator<(const Matrix& mat) const{
        ValidateDimensions(*this,mat,true); // cols and rows must be the same
        
        // Since The matrice dimensions is equal we just have to check for the sizes in both vectors 
        return SumMatrix(*this)<SumMatrix(mat); 
    }

    bool Matrix::operator<=(const Matrix& mat) const{
        ValidateDimensions(*this,mat,true); // cols and rows must be the same

        // Since The matrice dimensions is equal we just have to check for the sizes in both vectors
        return SumMatrix(*this)<=SumMatrix(mat);;
    }

    bool Matrix::operator>(const Matrix& mat) const{
        ValidateDimensions(*this,mat,true); // cols and rows must be the same
        
        // Since The matrice dimensions is equal we just have to check for the sizes in both vectors
        return SumMatrix(*this)>SumMatrix(mat);;
    }

    bool Matrix::operator>=(const Matrix& mat) const{
        ValidateDimensions(*this,mat,true); // cols and rows must be the same

        // Since The matrice dimensions is equal we just have to check for the sizes in both vectors
        return SumMatrix(*this)>=SumMatrix(mat);;
    }

    bool operator==(const Matrix &a, const Matrix &b){
        ValidateDimensions(a,b,true); // cols and rows must be the same
        size_t ROW_A = (unsigned) a.ROW;
        size_t COL_A = (unsigned) a.COL;
        size_t i = 0;
        while (i < ROW_A){
            size_t j = 0;
            while(j < COL_A){
                if(a.MAT[i*COL_A+j] != b.MAT[i*COL_A+j]){ // Does not match
                    return false;
                }
                j++;
            }
            i++;
        }
        
        return true;
    }

    bool operator!=(const Matrix &a, const Matrix &b){
        return(!(a==b)); // Uses the == operator (just not)
    }


    /**
    *  @brief Increment Decrement operators - Prefix/Postfix===----
    */

    Matrix& Matrix::operator++(){ // Prefix
        for (auto& idx : this->MAT){
            idx++;
        }
        
        return *this;
    }

    Matrix& Matrix::operator--(){ // Prefix
        for (auto& idx : this->MAT){
            idx--;
        }

        return *this;
    }


    Matrix Matrix::operator++(int){ // Postfix
        Matrix answer = *this;
        for (auto& idx : this->MAT){
            idx++;
        }

        return answer;
    }

    Matrix Matrix::operator--(int){ // Postfix
        Matrix answer = *this;
        for (auto& idx : this->MAT){
            idx--;
        }

        return answer;
    }
    
    /** 
    * @brief Multipication operators====----- 
    */
    Matrix Matrix::operator* (const Matrix &mat) const{ 
        ValidateDimensions(*this,mat,false); // Validates dimension - a.COL != b.ROW -> error
        size_t ROW_A = (unsigned) this->ROW;
        size_t COL_A = (unsigned) this->COL;
        size_t COL_B = (unsigned) mat.getCols();
        double add = 0;
        std::vector<double> ans;
        ans.resize(ROW_A * COL_B); // MUST initialize with size, else would throw segmentation fault (spent 20 hours on that problem)

        // O(n^3) - Starssen algorithm too long to implement + will cause ugly code duplication (the tc of n^2.7x really worth it?)
        // https://www.tutorialspoint.com/cplusplus-program-to-perform-matrix-multiplication
	    size_t i = 0;
        while(i < ROW_A){
            size_t j = 0;
            while(j < COL_B){
                add = 0;
                size_t k = 0;
                while(k < COL_A){   
                    add += this->MAT[(COL_A * i + k)] * mat.MAT[(COL_B * k + j)];
                    ++k;
                }
                ans[i*COL_B+j] = add;
                ++j;
            }
            ++i;
	    }

        return Matrix(ans,ROW_A,COL_B); // matrix A is a 2 × 3 matrix and matrix B is a 3 × 4 matrix, then AB is a 2 × 4 matrices.

    }

    Matrix Matrix::operator*(double num1){
        std::vector<double> v;
        for (auto& data : this->MAT){
            v.push_back(data*num1); 
        }
        return Matrix(v,this->ROW,this->COL);
    }

    Matrix Matrix::operator*=(double num1){
        *this = *this*num1; // Uses * operator so it won't need another check throws
        return *this;
    }

    Matrix Matrix::operator*=(const Matrix &mat){
        *this = *this*mat; // Uses * operator so it won't need another check throws
        return *this;
    }

    Matrix operator*=(double num1, Matrix &mat){
        mat = mat*num1;
        return mat;
    }

    Matrix operator*(double number, const Matrix &mat){
        std::vector<double> vec;
        for (const auto& data : mat.MAT){
            vec.push_back(data*number);
        }
        
        return Matrix(vec,mat.ROW,mat.COL);
    }


    /**
    * @brief Outstream Instream operators====-----
    */

    std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        size_t ROWS = (unsigned) mat.ROW;
        size_t COLS = (unsigned) mat.COL;
        size_t i = 0;
        while (i < ROWS){
            os << '['; // Add first
            size_t j = 0;
            while(j < COLS-1){
                os << mat.MAT[i*COLS +j] << ' '; // 0_ whereas 0 is the number at and _ is the ' '
                j++;
            }
            os << mat.MAT[i*COLS + COLS-1] << ']'; // Else it would have a gap
            if (!(ROWS-1 == i)){ // Not reached the end
                os << '\n';
            }
            i++;
            
        }
        return os;
    }

    // [1 0 0], [0 1 0], [0 0 1] > 
    std::istream &operator>>(std::istream &source, Matrix &mat) {
        // 10 hours here :(
        //  https://stackoverflow.com/questions/4754011/c-string-to-double-conversion
        //  https://stackoverflow.com/questions/13424265/convert-a-char-to-double
        //  https://reactgo.com/cpp-string-to-double/
        //  https://stackoverflow.com/questions/29485194/how-to-convert-user-input-char-to-double-c
        //  https://www.tutorialspoint.com/how-can-i-convert-string-to-double-in-c-cplusplus
        //  https://stackoverflow.com/questions/2158943/split-string-into-array-of-chars
        //  https://stackoverflow.com/questions/4533652/how-to-split-string-using-istringstream-with-other-delimiter-than-whitespace
        //  https://social.msdn.microsoft.com/Forums/en-US/d64d9398-b052-4f1e-95fc-661be9a6957f/how-to-convert-istreamc-to-systemiostreamc-and-vice-versa
        std::string str = toString(source); // Turn the input istream in a string
        int numbers = 0;
        int rows = 0;
        int blank = 0;
        unsigned long idx_b = 1;
        
        std::string ans;
        if(str[0] != '[' || str[str.size()-1] != ']'){ // base cases where the input does not start with a '[' or end with a ']'
            throw std::invalid_argument("bad input");
        }
        for (const auto& idx : str){ // Search for invalid characters that aren't the allowed ones 
            if (!(idx >= LOWER && idx <= UPPER) && !(idx == ']' || idx == ',' || idx == '[' || idx == ' ' || idx == '-' || idx == '.')){
                throw std::invalid_argument("bad input - only numbers & '[' ',' ']' ' ' allowed");
            }
        }
        while(str[idx_b] != ']' || idx_b+1 != str.size()){ 
            if((str[idx_b] >= LOWER && str[idx_b] <= UPPER)){ // Only digits here
                if(str[idx_b - 1] == '-'){ // In case we see a minus before the number so we add it
                    ans += '-';
                }
                if(str[idx_b - 1] == '.'){ // In case we see a double number aka 0.543
                    ans += '.';
                }
                ans += str[idx_b]; // Regular digit
                numbers++;
                idx_b++;
            }else if(str[idx_b] == ' '){ // We notice space so we incrememnt the "Blank" variable (as blank space)
                ans += ',';
                blank++;
                idx_b++;
            }else{
                idx_b++;

            }
            if(blank > numbers){ // In case we have more blank spaces in the middle of the matrix AKA [  0 0 0 1] 5>4 -> should throw an error  
                throw std::invalid_argument("bad input - more spaces than numbers");
            }
            // The good case where we notice "], ["
            if (str[idx_b] == ']' && str[idx_b+1] == ',' && str[idx_b+2] == ' ' && str[idx_b+3] == '['){ 
                ans += ',';
                blank = 0;
                idx_b += 3; // Because we chase 3 spaces after
                rows++;
            }

            // When we have a case like that not near the end of the input : ]X...,[ -> invalid 
            if ((str[idx_b] == ']' && str[idx_b+1] != ',') && (idx_b+1 != str.size())){ 
                throw std::invalid_argument("bad input");
            }

            // When there is an endling like "]," but after the ',' we don't see any space
            if ((str[idx_b] == ']' && str[idx_b+1] == ',' && str[idx_b+1] != ' ')){ //
                throw std::invalid_argument("bad input");
            }

        }
        rows++;
        std::vector<double> array = split(ans, ','); // returns a vector of "arranged 1D array" without the chars '[' ',' ']'
        int size = 0;
        for (size_t i = 0; i < array.size(); i++)
        {
            size++;;
        }
        
        mat.MAT = array;
        mat.COL = size/rows; // size of the column is the amount of numbers/rows
        mat.ROW = rows;

        return source;
    }


    
    std::string toString(std::istream& input){ 
        std::string line;
        std::getline(input, line); // Turn the input into a string


        return line;
    } 

    std::vector<double> split(const std::string &s, char delim) { // Used in the >> operator
        // https://stackoverflow.com/questions/20755140/split-string-by-a-character
        std::vector<double> elems;
        std::stringstream ss(s);
        std::string number;
        while(std::getline(ss, number, delim)) { // Used for the 
            elems.push_back(std::stod(number)); // Convert strings into double 
        }
        return elems;
    }


    /**
     * @brief Getters====-----
     * 
     */

    int Matrix::getRows() const{
        return this->ROW;
    }

    int Matrix::getCols() const{
        return this->COL;
    }

    std::vector<double> Matrix::getMat() const{
        return this->MAT;
    }


    /*
    *   -----====Helping functions====-----
    */
    void ValidateDimensions(const Matrix& a,const Matrix& b,bool coin){
        if(coin){ // Basic arithmetic dimension validation
            if((a.COL != b.COL || a.ROW != b.ROW)|| (a.COL != b.COL && a.ROW != b.ROW)){
                throw std::invalid_argument("Invalid Dimension of both matrices (have to be the same), unable to basic arithmetic");
            }
        }else{ // Validates multipication dimension 
            if ((a.COL != b.ROW)){
                throw std::invalid_argument("Column of first matrix should be equal to row of second matrix, unable to multiply");
            }     
        }
    }

    double SumMatrix(const Matrix& mat){
        double answer = 0;
        for(auto& ch : mat.getMat()){
            answer += ch;
        }
        return answer;
    }

}
