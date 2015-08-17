#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>

using namespace cv;

class FiltersShchedrin : public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   { }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { 
        //dst = src; //TODO: remove
        int cols, rows;
        cols = src.cols();
        rows = src.rows();
        int centerC = kernel.cols()/2;
        int centerR = kernel.rows()/2;
        for(int i = 0; i < dst.cols(); i++){
            for(int j = 0; j < dst.rows(); j++){
                int sum = 0;
                for(int kc = 0; kc < kernel.cols(); kc++){
                    for(int kr = 0; kr < kernel.rows(); kr++){
                        unsigned char srcElem, kerElem;
                        int srcCol = i - centerC + kc;
                        int srcRow = j - centerR + kr;
                        if(srcCol < 0 || srcRow < 0 || srcCol >= cols || srcRow >= rows){
                            srcElem = 0;
                        }else{
                            assert(srcCol >= 0 && srcRow >= 0 && srcCol < src.cols() && srcRow < src.rows());
                            srcElem = src[srcCol][srcRow];
                        }
                        assert(kc>=0);
                        assert(true&& kr >= 0);
                        assert(true&& kc < kernel.cols() );
                        assert(true&& kr < kernel.rows());
                        kerElem = kernel[kc][kr];
                        sum += kerElem * srcElem;
                    }
                }
                assert(i >= 0 && j >= 0 && i < dst.cols() && j < dst.rows());
                if(sum < 256){
                    dst[i][j] = sum;
                }
                else{
                    dst[i][j] = 255;
                }
            }
        }
   }
   virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   { }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { }
};

Filters* createFiltersShchedrin()
{
    Filters* filters = new FiltersShchedrin();
    return filters;
}