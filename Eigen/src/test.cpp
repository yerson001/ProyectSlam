#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
void test0()
{
    //------------------------
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << "Here is the matrix m:\n" << m << endl;

    VectorXd v(2);
    v(0) = 4;
    v(1) = v(0) - 1;
    cout << "Here is the vector v:\n" << v << endl;

    //------------------------
    Matrix3f m2;
    m2 << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    cout << m2 << endl;
}

void test1()
{
    // stats
    Eigen::Matrix2d mat;
    mat << 1, 2,
            3, 4;
    cout << "Here is mat.sum():       " << mat.sum()       << endl;
    cout << "Here is mat.prod():      " << mat.prod()      << endl;
    cout << "Here is mat.mean():      " << mat.mean()      << endl;
    cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl; // min value = 1
    cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl; // max value = 4
    cout << "Here is mat.trace():     " << mat.trace()     << endl; // 
}

/*
Here is mat.sum():       10
Here is mat.prod():      24
Here is mat.mean():      2.5
Here is mat.minCoeff():  1
Here is mat.maxCoeff():  4
Here is mat.trace():     5
*/

void test2()
{ 
    // l1-norm = |v1|+|v2|+...|vn|
    // l2-norm = v1*v1 + v2*v2+...vn*vn     squareNorm(), Norm()
    //  lpNorm< p >():  lpNorm< 1 >()   lpNorm< 2 >()

    VectorXf v(2);
    MatrixXf m(2,2), n(2,2);

    v << -1,
        2;

    m << 1,-2,
        -3,4;
    cout << "v.squaredNorm() = " << v.squaredNorm() << endl;
    cout << "v.norm() = " << v.norm() << endl;
    cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << endl;
    cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Infinity>() << endl; // max value
    cout << endl;
    cout << "m.squaredNorm() = " << m.squaredNorm() << endl;
    cout << "m.norm() = " << m.norm() << endl;
    cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << endl;
    cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Infinity>() << endl;  // max value


    n << 1,-2,
        -3,4;
    cout << "1-norm(n)     = " << n.cwiseAbs().colwise().sum().maxCoeff()
        << " == "             << n.colwise().lpNorm<1>().maxCoeff() << endl;
    cout << "infty-norm(n) = " << n.cwiseAbs().rowwise().sum().maxCoeff()
        << " == "             << n.rowwise().lpNorm<1>().maxCoeff() << endl;
}
/*
v.squaredNorm() = 5
v.norm() = 2.23607
v.lpNorm<1>() = 3
v.lpNorm<Infinity>() = 2

m.squaredNorm() = 30
m.norm() = 5.47723
m.lpNorm<1>() = 10
m.lpNorm<Infinity>() = 4


1-norm(n)     = 6 == 6
infty-norm(n) = 7 == 7
*/


void test3()
{
    // bool
    ArrayXXf a(2,2);

    a << 1,2,
        3,4;
    cout << "(a > 0).all()   = " << (a > 0).all() << endl; // bool 
    cout << "(a > 0).any()   = " << (a > 0).any() << endl; // bool
    cout << "(a > 0).count() = " << (a > 0).count() << endl; // int
    cout << endl;
    cout << "(a > 2).all()   = " << (a > 2).all() << endl;
    cout << "(a > 2).any()   = " << (a > 2).any() << endl;
    cout << "(a > 2).count() = " << (a > 2).count() << endl;
}
/*
(a > 0).all()   = 1
(a > 0).any()   = 1
(a > 0).count() = 4

(a > 2).all()   = 0
(a > 2).any()   = 1
(a > 2).count() = 2
*/

void test4()
{
    // get min/max index
    Eigen::MatrixXf m(2,2);

    m << 1, 2,
        3, 4;

    //get location of maximum
    MatrixXf::Index maxRow, maxCol;
    float max = m.maxCoeff(&maxRow, &maxCol);

    //get location of minimum
    MatrixXf::Index minRow, minCol;
    float min = m.minCoeff(&minRow, &minCol);

    cout << "Max: " << max <<  ", at: " << maxRow << "," << maxCol << endl;
    cout << "Min: " << min <<  ", at: " << minRow << "," << minCol << endl;
}
/*
Max: 4, at: 1,1
Min: 1, at: 0,0
*/

void test5()
{
    // colwise rowwise
    Eigen::MatrixXf mat(2,4);
    mat << 1, 2, 6, 9,
            3, 1, 7, 2;

    std::cout << "Column's maximum: " << std::endl
    << mat.colwise().maxCoeff() << std::endl;

    std::cout << "Row's maximum: " << std::endl
    << mat.rowwise().maxCoeff() << std::endl;
}
/*
Column's maximum: 
3 2 7 9
Row's maximum: 
9
7
*/

void test6()
{
    // colwise + max/min
    MatrixXf mat(2,4);
    mat << 1, 2, 6, 9,
            3, 1, 7, 2;

    MatrixXf::Index   maxIndex;
    float maxSum = mat.colwise().sum().maxCoeff(&maxIndex);

    std::cout << "Maximum sum at position " << maxIndex << std::endl;
    std::cout << "The corresponding vector is: " << std::endl;
    std::cout << mat.col( maxIndex ) << std::endl;
    std::cout << "And its sum is is: " << maxSum << std::endl;
}
/*
Maximum sum at position 2
The corresponding vector is: 
6
7
And its sum is is: 13
*/

void test7()
{
    // broadcast with vector
    Eigen::MatrixXf mat(2,4);
    Eigen::VectorXf v(2);

    mat << 1, 2, 6, 9,
            3, 1, 7, 2;

    v << 0,
        1;

    //add v to each column of m
    mat.colwise() += v;
    //mat += v; // ERROR

    std::cout << "Broadcasting result: " << std::endl;
    std::cout << mat << std::endl;
}
/*
Broadcasting result: 
1 2 6 9
4 2 8 3
*/

void test8()
{
    Eigen::MatrixXf m(2,4);
    Eigen::VectorXf v(2);

    m << 1, 23, 6, 9,
        3, 11, 7, 2;

    v << 2,
        3;
    MatrixXf::Index index;
    // find nearest neighbour
    (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
    cout << "Nearest neighbour is column " << index << ":" << endl;
    cout << m.col(index) << endl;
}
/*
Nearest neighbour is column 0:
1
3
*/

void test_eigen3()
{
    //test0();
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    //test6();
    //test7();
    test8();
}
int main(){
    test_eigen3();
    cout<<"como estas"<<endl;
    return 0;
}
