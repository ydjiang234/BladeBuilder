#ifndef LINESEGEMENT_H
#define LINESEGEMENT_H

#include <Dense>
#include <string>
#include <vector>
#include <utility>

class LineSegement
{
public:
    LineSegement();
    LineSegement(std::string label, Eigen::MatrixX2d data);
    ~LineSegement();

    std::vector<LineSegement> Split(Eigen::VectorXi keyInd);
    std::pair<LineSegement, Eigen::VectorXi> Join(std::vector<LineSegement> lineSegs, std::string label);

    std::string label;
    Eigen::MatrixX2d data;
    unsigned int pointNum;

private:
    Eigen::MatrixX2d CombineMatrixV(Eigen::MatrixX2d M1, Eigen::MatrixX2d M2);
};

#endif // LINESEGEMENT_H
