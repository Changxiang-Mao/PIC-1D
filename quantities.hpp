#pragma once
#include<cassert>
using namespace std;

#include "vec3.hpp"

template<typename T>
class Field
{
private:
    T* data;
    int Nx;
public:
    Field(){}
    Field(int nx)
    {
        this->ini(nx);
    }
    ~Field()
    {
        if(data!=nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }
    Field(const Field<T>& f)
    {
        Nx = f.getNx();
        data = new T [Nx];
        for(int i=0;i<Nx;i++)
        {
            data[i] = f[i];
        }
    }
    void ini(int nx)
    {
        Nx = nx;
        data = new T [Nx];
        T ele;
        ele = 0;
        for(int i=0;i<Nx;i++)
        {
            data[i] = ele;
        }
    }
    int getNx() const {return Nx;}
    T& operator[] (int i) const
    {
        return data[i];
    }
    void operator= (const T& s)
    {
        for(int i=0;i<Nx;i++)
        {
            data[i] = s;
        }
    }
    void operator+=(const Field<T>& f)
    {
        assert(Nx==f.getNx());
        for(int i=0;i<Nx;i++)
        {
            data[i] += f[i];
        }
    }
    Field<T> operator*(double s)
    {
        Field<T> f(Nx);
        for(int i=0;i<Nx;i++)
        {
            f[i] = data[i]*s;
        }
        return f;
    }
    Field<T> operator+(const Field<T>& f)
    {
        assert(Nx==f.getNx());
        Field<T> field(Nx);
        for(int i=0;i<Nx;i++)
        {
            field[i] = data[i] + f[i];
        }
        return field;
    }
    void operator= (const Field<T>& f)
    {
        for(int i=0;i<Nx;i++)
        {
            data[i] = f[i];
        }
    }
};

template<typename T>
class Point
{
private:
    T* data; //position,velocity,momentum,E_field,B_field,for particles
    int Np; //number of particles
public:
    Point(){}
    Point(int np)
    {
        this->ini(np);
    }
    ~Point()
    {
        if(data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }
    Point(const Point<T>& pa)
    {
        Np = pa.getNp();
        data = new T [Np];
        for(int p=0;p<Np;p++)
        {
            data[p] = pa[p];
        }
    }
    void ini(int np)
    {
        Np = np;
        data = new T [Np];
        T ele;
        ele = 0;
        for(int p=0;p<Np;p++)
        {
            data[p] = ele;
        }
    }
    int getNp() const{
        return Np;
    }
    T& operator[] (int i) const
    {
        return data[i];
    }
    void operator= (const Point<T>& pa)
    {
        assert(Np == pa.getNp());
        for(int p=0;p<Np;p++)
        {
            data[p] = pa[p];
        }
    }
};


