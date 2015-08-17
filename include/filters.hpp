#pragma once

#include "matrix.hpp"

class Filters
{
 public:
    virtual ~Filters() {}

    virtual void boxFilter(const Matrix &src, Matrix &dst, const int kSize = 3) = 0;
    virtual void filter2d(const Matrix &src, Matrix &dst, const Matrix &kernel) = 0;
    virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3) = 0;
    virtual void SobelOx(const Matrix &src, Matrix &dst) = 0;
};

enum FILTERS_IMPLEMENTATIONS {
    OPENCV,
	Ekaterina_Maljutina,
    // Add your enum value here
    // YOUR_NAME,
    NUM_IMPLS
};

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl);
