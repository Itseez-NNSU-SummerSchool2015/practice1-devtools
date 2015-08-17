#include "filters.hpp"

uchar* Sort(uchar* A, int N)
{
    return 0;
}

class FiltersSemichev : public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   {
       dst = Matrix(src.rows(),src.cols());
       int sdvig = kSize / 2;
       double F = 1.0 / (kSize * kSize);

       for (int x = 0; x < src.cols(); x++)
           for(int y = 0; y < src.rows(); y++)
           {
                double tmp = 0;
                for (int i = 0 - sdvig; i <= sdvig; i++)
                    for (int j = 0 - sdvig; j <= sdvig; j++)
                    {
                        if (x + i < 0) 
                            tmp += 0;
                        else
                            if (y + j < 0)
                                tmp += 0;
                            else
                                tmp += F * src[x+i][y+j];
                    }
                if (tmp > 255) tmp = 255;
                dst[x][y] = tmp;
           }
   }

   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { 
       dst = Matrix(src.rows(),src.cols());
       int kSize = kernel.cols();
       int sdvig = kSize / 2;

       for (int x = 0; x < src.cols(); x++)
           for(int y = 0; y < src.rows(); y++)
           {
                dst[x][y] = 0;
                for (int i = 0 - sdvig; i <= sdvig; i++)
                    for (int j = 0 - sdvig; j <= sdvig; j++)
                    {
                        if (x + i < 0) 
                            if (y + j < 0)
                                dst[x][y] += kernel[i + sdvig][j + sdvig] * src[x-i][y-j];
                            else
                                dst[x][y] += kernel[i + sdvig][j + sdvig] * src[x-i][y+j];
                        else
                            if (y + j < 0)
                                dst[x][y] += kernel[i + sdvig][j + sdvig] * src[x+i][y-j];
                            else
                                dst[x][y] += kernel[i + sdvig][j + sdvig] * src[x+i][y+j];
                    }
           }
   }
  virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   {
       /*uchar* intensity = new uchar[kSize*kSize];
       dst = Matrix(src.rows(),src.cols());
       int sdvig = kSize / 2;

       for (int x = 0; x < src.cols(); x++)
           for(int y = 0; y < src.rows(); y++)
           {
                dst[x][y] = 0;
                int k = 0;
                for (int i = 0 - sdvig; i <= sdvig; i++)
                    for (int j = 0 - sdvig; j <= sdvig; j++)
                    {
                        if ((x + i >= 0) && (y + j >= 0))
                        {
                            intensity[k] = src[x+i][y+j];
                        }
                    }
                
           }*/
   }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { }
};


Filters* createFiltersSemichev()
{
   Filters* filters = new FiltersSemichev;
   return filters;
}

