#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>

using namespace cv;

class FiltersEkaterinaMaljutina : public Filters
{
	
public:

   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   {
	   dst = Matrix(src.rows(),src.cols());

	   int deth = kSize/2;
	   
	   for (int x=0; x< src.rows(); x++)
	   {
		   for (int y=0; y<src.cols();y++)
		   {
			   double intens = 0.0;

			   for (int i= 0 - deth ; i< deth; i++)
			   {
				   for (int j = 0 - deth ; j< deth ; j++)
				   {
					   
					   if (x+i< 0 || y+j <0)
					   {
						   if (x+i<0 && y+j<0)
						   {
							   intens += src[x-i][y-j]/ (kSize * kSize);
						   }
						   else
						   {
							   if (x+i<0 )
							   {
								   intens += src[x-i][y+j]/ (kSize * kSize);
							   }
							   else
							   {
								   intens +=src [x+i][y-j]/ (kSize * kSize);

							   }
						   }

					   }
					   else
					   {
						   intens += src [x+i][y+j] / (kSize * kSize);
					   }
					   
				   }
			   }
			   //intens =   intens / (kSize * kSize) ;
			   dst[x][y] =  intens;
		   }
	   }


   }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   {
	   dst = Matrix(src.rows(),src.cols());

	   int kSize  =  kernel.rows();
	   int deth = kSize/2;
	   
	   for (int x=deth; x< src.rows(); x++)
	   {
		   for (int y=deth; y<src.cols();y++)
		   {
			   double intens = 0.0;

			   for (int i= 0 - deth ; i< deth; i++)
			   {
				   for (int j = 0 - deth ; j< deth ; j++)
				   {

						intens += src [x+i][y+j]*kernel[i + deth][j  + deth];

					   
				   }
			   }

			   dst[x][y] =  intens;
		   }
	   }


   }
   virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   { 

	   dst = Matrix(src.rows(),src.cols());
	   int deth = kSize/2;
	   double* intens  = new double[kSize*kSize];
	   for (int x=deth; x< src.rows(); x++)
	   {
		   for (int y=deth; y<src.cols();y++)
		   {
			   int n=0;
			  
			   for (int i= 0 - deth ; i< deth; i++)
			   {
				   for (int j = 0 - deth ; j< deth ; j++)
				   {
					   				   
						   intens[n] = src [x+i][y+j];
						   n++;					   
				   }
			   }
			   for (int i = kSize*kSize - 1; i >= 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if (intens[j] > intens[j+1])
						{
							int tmp = intens[j];
							intens[j] = intens[j + 1];
							intens[j + 1] = tmp;
						}
					}
			   }

			   dst[x][y] =  intens[kSize/2];
		   }
	   }



   }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { 
   }
};


Filters* createFiltersEkaterina_Maljutina()
{
   Filters* filters = new FiltersEkaterinaMaljutina();
   return filters;
}