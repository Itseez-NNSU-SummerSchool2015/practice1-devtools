#include "filters.hpp"

class FiltersGrishinSergey : public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   { 
		Matrix mask = Matrix(kSize, kSize);
		mask.Ones();

		for(int i = 0; i < src.cols(); i++)
		{
			for(int j = 0; j < src.cols(); j++)
			{
				dst[i][j]=get_middle(src, mask, i, j, kSize);
			}
		}
   }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { }
   virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   { }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { }

   int get_middle(const Matrix &src, Matrix& mask, int i, int j, const int kSize)
   {
	   int middle = 0;
	   
		for(int x = -kSize/2; x < kSize/2; x++)
		{
			for(int y = -kSize/2; y < -kSize/2; y++)
			{
				if(x < 0) x*=-1;
				if(y < 0) y*=-1;
				middle+=src[i+x][j+y];
			}	
		}

	   return middle/(kSize*kSize);
   }

   Filters* createFiltersGrishinSergey()
	{
    Filters* filters = new FiltersGrishinSergey();
    return filters;
	}
};