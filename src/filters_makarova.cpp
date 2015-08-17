#include <vector>
#include "filters.hpp"

std::vector<unsigned char>;


class FiltersMakarova: public Filters
{
public:
   virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
   {
       Matrix new_src(src.rows()+kSize/2, src.cols()+kSize/2);
       for(int i = kSize/2; i < src.rows()+kSize/2-1; i++)
       {
           for(int j = kSize/2; j < src.cols()+kSize/2-1; j++){
           new_src[i][j] = src[i-kSize/2][j-kSize/2];

           }
       }
   }
   virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
   { }
   virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
   {
       Matrix filter(kSize, kSize);
       Matrix new_src(src.rows()+kSize/2, src.cols()+kSize/2);
       new_src.Zeros();
       for(int i=1; i<src.rows()-1; i++){
           for(int j = 1; j<src.cols()-1; j++){

           }
       }
       for(int x = 0; x<src.rows(); x++)
       {
           for(int y = 0; y<src.cols(); y++){
         
               dst[x][y] = apply_filters(kSize, src);
               
             
           }
       }
   }
   virtual void SobelOx(const Matrix &src, Matrix &dst)
   { }

   Filters* createFiltersMakarova()
{
   Filters* filters = new FiltersMakarova();
   return filters;
}

     int apply_filters(const int kSize, const Matrix &src){
        std:: vector<unsigned char> vector_sort;
         for(int i=0; i<kSize; i++){
            for(int j=0; j<kSize; j++){
                vector_sort.push_back(src[i][j]);
            }
        }
         for(size_t i =0; i<vector_sort.size()-1; i++){
             for(size_t j =i; j<vector_sort.size()-i-1; j++){
                 if(vector_sort[i]<vector_sort[j]){
                 std::swap(vector_sort[i], vector_sort[j]);
                 }
             }
         }
         unsigned char result = vector_sort.size()/2;
         return result;
     }
};