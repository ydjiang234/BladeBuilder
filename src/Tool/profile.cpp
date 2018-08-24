#include "profile.h"
#include <cmath>
#include <limits>
#include <iostream>

//std::cout<<"OK"<<std::endl;

Profile::Profile() {}

Profile::Profile(std::string label, Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist) :
    LineSegement (label, data)
{
    this->UpdateData(chordLen, leadCoord, twist);
}

Profile::~Profile() {}

void Profile::UpdateData(double chordLen, Eigen::Array3d leadCoord, double twist)
{
    Eigen::ArrayX2d temp, dataU, dataL;
    //data length
    Eigen::Index len = data.rows();

    //Check if the profile is open or close
    if (this->IsEqual(data(0,0), data(len-1,0)) && this->IsEqual(data(0,1), data(len-1,1))) {
        temp = data.topRows(len-1);
        data = temp;
    }
    this->Update(this->ReOrder(data));
    this->chordLen = chordLen;
    this->leadCoord = leadCoord;
    this->twist = twist;
    //Separate data
    std::pair<Eigen::ArrayX2d, Eigen::ArrayX2d> temp1 = this->SeparateUL(this->data);
    dataU = temp1.first;
    dataL = temp1.second;
    this->lineU = LineSegement(this->label+"-"+"U", dataU);
    this->lineL = LineSegement(this->label+"-"+"L", dataL);
}

Eigen::ArrayX2d Profile::getData(unsigned int meshNum)
{
    Eigen::ArrayX2d out;

    out = this->Interp(meshNum);
    out = this->Scale(out, this->chordLen);
    out = this->Rotate(out, this->twist);
    out = this->Transfer(out, this->leadCoord.tail(2));

    return out;
}

std::pair<Eigen::ArrayX2d, Eigen::ArrayX2d> Profile::SeparateUL(Eigen::ArrayX2d data)
{
    std::pair<Eigen::ArrayX2d, Eigen::ArrayX2d> out;

    Eigen::Index len;
    Eigen::ArrayX2d temp1, temp2, newData, temp;

    //data length
    len = data.rows();

    //Find the index of the tail where y is close to zero
    Eigen::Index curInd, splitInd;
    curInd = 0;
    while (!((data(curInd,1)>=0) && (data(curInd+1,1)<=0))) {
        ++curInd;
    }
    //Find the index which is closest to zero

    if (std::abs(data(curInd,1)) > std::abs(data(curInd+1,1))) {
        splitInd = curInd+1;
    } else {
        splitInd = curInd;
    }
    //Split the data according to splitInd
    Eigen::ArrayX2d dataU, dataL;
    dataU = data.topRows(splitInd+1);
    temp = this->CombineArrayV(data.bottomRows(len-splitInd), data.row(0));
    dataL = temp.colwise().reverse();

    out.first = dataU;
    out.second = dataL;

    return out;
}

Eigen::ArrayX2d Profile::ReOrder(Eigen::ArrayX2d data)
{
    Eigen::Index minInd, len;
    Eigen::ArrayX2d temp1, temp2, newData, temp;

    //data length
    len = data.rows();
    //Reset the start point of data
    //Find the index of the Xmin
    data.col(0).minCoeff(&minInd);
    //Separate the data at the Xmin
    temp2 = data.topRows(minInd);
    temp1 = data.bottomRows(data.rows() - minInd);
    //Combine the temp1 and temp2 to reset the Xmin to the start point
    data = this->CombineArrayV(temp1, temp2);

    //Check and change the data order
    if (data(1,1)-data(0,1)<0.0) {
        //data is counter clock wise, should reverse the order of data
        //Put the first row to tail
        temp1 = data.bottomRows(len-1);
        temp2 = data.row(0);
        data = this->CombineArrayV(temp1, temp2);
        //Reverse it
        temp = data.colwise().reverse();
        data = temp;
    }
    return data;
}

Eigen::ArrayX2d Profile::Rotate(Eigen::ArrayX2d data, double angle)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayXd tempX, tempY;
    Eigen::ArrayX2d out(len, 2);

    tempX = data.col(0);
    tempY = data.col(1);

    out.col(0) = tempX * cos(angle) - tempY * sin(angle);
    out.col(1) = tempX * sin(angle) + tempY * cos(angle);

    return out;
}

Eigen::ArrayX2d Profile::Scale(Eigen::ArrayX2d data, double factor)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayX2d out(len, 2);

    out = data * factor;

    return out;
}

Eigen::ArrayX2d Profile::Transfer(Eigen::ArrayX2d data, Eigen::Array2d vec)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayX2d out(len, 2);

    out.col(0) = data.col(0) + vec(0);
    out.col(1) = data.col(1) + vec(1);

    return out;
}

bool Profile::IsEqual(double a, double b)
{
    bool out;
    if (abs(a-b)<std::numeric_limits<double>::epsilon()) {
        out = true;
    } else {
        out = false;
    }
    return out;
}
