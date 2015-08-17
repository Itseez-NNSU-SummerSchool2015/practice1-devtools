#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


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

			   for (int i= 0 - deth ; i< deth+1 ; i++)
			   {
				   for (int j = 0 - deth ; j< deth+1 ; j++)
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

			   for (int i= 0 - deth ; i< deth+1; i++)
			   {
				   for (int j = 0 - deth ; j< deth+1 ; j++)
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
			  
			   for (int i= 0 - deth ; i< deth+1; i++)
			   {
				   for (int j = 0 - deth ; j< deth+1 ; j++)
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
	   /*
	   matrix Sobel 
	   -1 0 1
	   -2 0 2
	   -1 0 1
	   */


	   Matrix sobel(3,3);
	   sobel[0][0]=sobel[0][2] = -1;
	   sobel[1][0] = sobel[1][1] = sobel[1][2] = 0;
	   sobel[0][1]=-2;
	   sobel[2][0] = sobel[2][2]= 1;
	   sobel[2][1] = 2;


	   dst = Matrix(src.rows(),src.cols());

	   int deth = 1;
	   
	   for (int x=0; x< src.rows(); x++)
	   {
		   for (int y=0; y<src.cols();y++)
		   {
			   double intens = 0.0;

			   for (int i= 0 - deth ; i< deth+1 ; i++)
			   {
				   for (int j = 0 - deth ; j< deth+1 ; j++)
				   {
					   
					   if (x+i< 0 || y+j <0)
					   {
						   if (x+i<0 && y+j<0)
						   {
							   intens += src[x-i][y-j] * sobel[i +deth][j+deth];
						   }
						   else
						   {
							   if (x+i<0 )
							   {
								   intens += src[x-i][y+j]* sobel[i +deth][j+deth];
							   }
							   else
							   {
								   intens +=src [x+i][y-j]* sobel[i +deth][j+deth];

							   }
						   }

					   }
					   else
					   {
						   intens += src [x+i][y+j]* sobel[i +deth][j+deth] ;
					   }
					   
				   }
			   }
	
			   dst[x][y] =  intens;
		   }
	   }


   }
};


Filters* createFiltersEkaterina_Maljutina()
{
   Filters* filters = new FiltersEkaterinaMaljutina();
   return filters;
}