#pragma once

class Vec3
{
private:
    double* data;
public:
    Vec3()
    {
        data = new double [3];
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }
    ~Vec3()
    {
        if(data!=nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }
    Vec3(double x,double y,double z)
    {
        data = new double [3];
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    Vec3(const Vec3& v)
    {
        data = new double [3];
        data[0] = v[0];
        data[1] = v[1];
        data[2] = v[2];
    }
    double& operator[] (int i) const
    {
        return data[i];
    }
    Vec3 operator*(const double s) // number product
    {
        Vec3 v;
        v[0] = data[0]*s;
        v[1] = data[1]*s;
        v[2] = data[2]*s;
        return v;
    }
    double operator*(const Vec3& vec) //dot product
    {
        double r = 0;
        r = data[0]*vec[0] + data[1]*vec[1] + data[2]*vec[2];
        return r;
    }
    Vec3 cross(const Vec3& vec)
    {
        Vec3 v;
        v[0] = data[1]*vec[2] - data[2]*vec[1];
        v[1] = data[2]*vec[0] - data[0]*vec[2];
        v[2] = data[0]*vec[1] - data[1]*vec[0];
        return v;
    }
    void operator=(double s)//set number
    {
        data[0] = s;
        data[1] = s;
        data[2] = s;
    }
    void operator=(const Vec3& v)
    {
        data[0] = v[0];
        data[1] = v[1];
        data[2] = v[2];
    }
    void operator+=(const Vec3& v)
    {
        data[0] += v[0];
        data[1] += v[1];
        data[2] += v[2];
    }
    Vec3 operator+(const Vec3& vec)
    {
        Vec3 v;
        v[0] = data[0] + vec[0];
        v[1] = data[1] + vec[1];
        v[2] = data[2] + vec[2];
        return v;
    }
    double L2()
    {
        double r2 = 0;
        r2 = data[0]*data[0] + data[1]*data[1] +data[2]*data[2];
        return r2;
    }
    void setvalue(double x,double y,double z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
};
