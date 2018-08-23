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
    LineSegement(std::string label, Eigen::ArrayX2d data);
    ~LineSegement();

    void Update(Eigen::ArrayX2d data);
    std::vector<LineSegement> Split(Eigen::ArrayXi keyInd);
    std::pair<LineSegement, Eigen::ArrayXi> Join(std::vector<LineSegement> lineSegs, std::string label);
    void Interp(unsigned int number); //number is the number of segments


    std::string label;
    Eigen::ArrayX2d data;
    Eigen::ArrayXd arcLength, cumArcLength;
    unsigned int pointNum;

private:
    void getArcLength();
    Eigen::ArrayX2d CombineArrayV(Eigen::ArrayX2d M1, Eigen::ArrayX2d M2);
};

#endif // LINESEGEMENT_H
