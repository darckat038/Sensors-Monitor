#include "MagneticData.h"

#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>

namespace Sensors {

    MagneticData::MagneticData()
    {
        generateRandomData();
    }

    MagneticData::MagneticData(const MagneticData &eData)
        : X(eData.getXval()), Y(eData.getYval()), Z(eData.getZval())
    {

    }

    MagneticData::MagneticData(double XVal, double YVal, double ZVal)
        : X(XVal), Y(YVal), Z(ZVal)
    {

    }

    double MagneticData::getXval() const
    {
        return X;
    }

    double MagneticData::getYval() const
    {
        return Y;
    }

    double MagneticData::getZval() const
    {
        return Z;
    }

    void MagneticData::setXVal(double xval)
    {
        X = xval;
    }

    void MagneticData::setYVal(double yval)
    {
        Y = yval;
    }

    void MagneticData::setZVal(double zval)
    {
        Z = zval;
    }

    MagneticData MagneticData::operator-(const MagneticData &mData)
    {
        return MagneticData(X-mData.getXval(), Y-mData.getYval(), Z-mData.getZval());
    }

    MagneticData MagneticData::operator+(const MagneticData &mData)
    {
        return MagneticData(X+mData.getXval(), Y+mData.getYval(), Z+mData.getZval());
    }

    MagneticData MagneticData::operator*(const MagneticData &mData)
    {
        return MagneticData(X*mData.getXval(), Y*mData.getYval(), Z*mData.getZval());
    }

    bool MagneticData::operator==(const MagneticData &mData)
    {
        if(X == mData.getXval() && Y == mData.getYval() && Z == mData.getZval())
            return true;
        else
            return false;
    }

    MagneticData& MagneticData::operator=(const MagneticData &mData)
    {
        if(this == &mData)
            return *this;

        X = mData.getXval();
        Y = mData.getYval();
        Z = mData.getZval();
        return *this;
    }

    MagneticData MagneticData::operator/(int val)
    {
        return MagneticData(X/val, Y/val, Z/val);
    }

    void MagneticData::generateRandomData() {
        //GENERAZIONE NUMERI CASUALI CON LIBRERIE C++
        std::random_device rd;            //The random seed
        std::mt19937 gen(rd());            //The Mersenne Twister engine
        std::uniform_real_distribution<double> dis(-100, 100);         //Uniform Distribution from -50 to 100
        X = dis(gen);
        Y = dis(gen);
        Z = dis(gen);
    }

}

