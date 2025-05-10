#ifndef MAGNETICDATA_H
#define MAGNETICDATA_H

namespace Sensors {

class MagneticData
{
private:
    //Valori
    double X;
    double Y;
    double Z;
public:
    //Costruttore standard
    MagneticData();
    //Costruttore di copia
    MagneticData(const MagneticData &mData);
    //Costruttore con valori
    MagneticData(double XVal, double YVal, double ZVal);

    ~MagneticData() = default;

    //Gestione attributi
    double getXval() const;
    double getYval() const;
    double getZval() const;
    void setXVal(double xval);
    void setYVal(double yval);
    void setZVal(double zval);

    //Ridefinizione operatori
    MagneticData operator-(const MagneticData &mData);
    MagneticData operator+(const MagneticData &mData);
    MagneticData operator*(const MagneticData &mData);
    bool operator==(const MagneticData &mData);
    MagneticData& operator=(const MagneticData &mData);
    MagneticData operator/(int val);


    //Generazione dati casuali
    void generateRandomData();

};

}

#endif // MAGNETICDATA_H
