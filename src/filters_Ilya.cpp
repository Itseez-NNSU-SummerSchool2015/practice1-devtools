#include "filters.hpp"

class FiltersYourName : public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   { }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { }
   virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   { }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { }
};