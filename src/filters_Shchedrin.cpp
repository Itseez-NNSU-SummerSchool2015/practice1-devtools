#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <iostream>

using namespace cv;
using namespace std;

class FiltersShchedrin : public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   { }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { 
        //dst = src; 
        //return;
        int cols, rows;
        cols = src.cols();
        rows = src.rows();
        int centerC = kernel.cols()/2;
        int centerR = kernel.rows()/2;
        for(int i = 0; i < dst.rows(); i++){
            for(int j = 0; j < dst.cols(); j++){
                unsigned int sum = 0;
                for(int kr = 0; kr < kernel.rows(); kr++){
                     for(int kc = 0; kc < kernel.cols(); kc++){
                        unsigned char srcElem, kerElem;
                        int srcCol = i - centerC + kc;
                        int srcRow = j - centerR + kr;
                        if(srcCol < 0 || srcRow < 0 || srcCol >= cols || srcRow >= rows){
                            srcElem = 0;
                        }else{
                            assert(srcCol >= 0 && srcRow >= 0 && srcCol < src.cols() && srcRow < src.rows());
                            srcElem = src[srcRow][srcCol];
                        }
                        assert(kc >=0);
                        assert(kr >= 0);
                        assert(kc < kernel.cols());
                        assert(kr < kernel.rows());
                        kerElem = kernel[kc][kr];
                        sum += kerElem * srcElem;
                    }
                }
                //cout<<i<<" "<<j<<endl; // TODO:remove
                assert(i >= 0 && j >= 0 && i < dst.rows() && j < dst.cols());
                if(sum < 256){
                    dst[i][j] = sum;
                }
                else{
                    dst[i][j] = 255;
                }
                //cout<<"OK"<<endl; // TODO:remove
            }
        }
        std::cout<<"end"<<std::endl;
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