#include "filters.hpp"

class FiltersKustikova : public Filters
{
 public:
    virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
    {
        
    }

    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        
    }

    virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3)
    {
        dst = src;
        medianFilterInternalPoints(src, dst, kSize);
        medianFilterTopPoints(src, dst, kSize);
        medianFilterBottomPoints(src, dst, kSize);
        medianFilterLeftBorderPoints(src, dst, kSize);
        medianFilterRightBorderPoints(src, dst, kSize);
        medianFilterCornersPoints(src, dst, kSize);
    }

    virtual void SobelOx(const Matrix &src, Matrix &dst)
    {
        
    }
private:
    void sort(uchar *neigbors, int size)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (neigbors[i] > neigbors[j])
                {
                    uchar tmp = neigbors[i];
                    neigbors[i] = neigbors[j];
                    neigbors[j] = tmp;
                }
            }
        }
    }

    void medianFilterInternalPoints(const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, 
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        for (int i = kSize2; i < src.rows() - kSize2; i++)
        {
            for (int j = kSize2; j < src.cols() - kSize2; j++)
            {
                idx = 0;
                for (int k = -kSize2; k <= kSize2; k++)
                {
                    for (int s = -kSize2; s <= kSize2; s++)
                    {
                        neigbors[idx++] = src[i + k][j + s];
                    }
                }
                sort(neigbors, size);
                dst[i][j] = neigbors[medIdx];
            }
        }
        delete []neigbors;
    }

    void medianFilterTopPoints(const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, 
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        for (int j = kSize2; j < src.cols() - kSize2; j++)
        {
            idx = 0;
            // 0 0 0
            // 1 1 1
            // 0 0 0
            for (int s = -kSize2; s <= kSize2; s++)
            {
                neigbors[idx++] = src[0][j + s];
            }
            // 1 1 1
            // 0 0 0
            // 0 0 0
            for (int l = 0; l < kSize2; l++)
            {
                for (int s = -kSize2; s <= kSize2; s++)
                {
                    neigbors[idx++] = src[0][j + s];
                }
            }
            // 0 0 0
            // 0 0 0
            // 1 1 1
            for (int k = 1; k <= kSize2; k++)
            {
                for (int s = -kSize2; s <= kSize2; s++)
                {
                    neigbors[idx++] = src[k][j + s];
                }
            }
            sort(neigbors, size);
            dst[0][j] = neigbors[medIdx];
        }
        delete []neigbors;
    }

    void medianFilterBottomPoints(const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kRows = src.rows(),
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        for (int j = kSize2; j < src.cols() - kSize2; j++)
        {
            idx = 0;
            // 0 0 0
            // 1 1 1
            // 0 0 0
            for (int s = -kSize2; s <= kSize2; s++)
            {
                neigbors[idx++] = src[kRows - 1][j + s];
            }
            // 1 1 1
            // 0 0 0
            // 0 0 0
            for (int l = 0; l < kSize2; l++)
            {
                for (int s = -kSize2; s <= kSize2; s++)
                {
                    neigbors[idx++] = src[kRows - 1][j + s];
                }
            }
            // 0 0 0
            // 0 0 0
            // 1 1 1
            for (int k = -kSize2; k <= -1; k++)
            {
                for (int s = -kSize2; s <= kSize2; s++)
                {
                    neigbors[idx++] = src[kRows + k - 1][j + s];
                }
            }
            sort(neigbors, size);
            dst[kRows - 1][j] = neigbors[medIdx];
        }
        delete []neigbors;
    }

    void medianFilterLeftBorderPoints(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kRows = src.rows(),
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        for (int i = kSize2; i < src.rows() - kSize2; i++)
        {
            idx = 0;
            // 0 1 0
            // 0 1 0
            // 0 1 0
            for (int k = -kSize2; k <= kSize2; k++)
            {
                neigbors[idx++] = src[i + k][0];
            }
            // 1 0 0
            // 1 0 0
            // 1 0 0
            for (int l = 0; l < kSize2; l++)
            {
                for (int k = -kSize2; k <= kSize2; k++)
                {
                    neigbors[idx++] = src[i + k][0];
                }
            }
            // 0 0 1
            // 0 0 1
            // 0 0 1
            for (int k = -kSize2; k <= kSize2; k++)
            {
                for (int s = 1; s <= kSize2; s++)
                {
                    neigbors[idx++] = src[i + k][s];
                }
            }
            sort(neigbors, size);
            dst[i][0] = neigbors[medIdx];
        }
        delete []neigbors;
    }

    void medianFilterRightBorderPoints(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kCols = src.cols(),
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        for (int i = kSize2; i < src.rows() - kSize2; i++)
        {
            idx = 0;
            // 0 1 0
            // 0 1 0
            // 0 1 0
            for (int k = -kSize2; k <= kSize2; k++)
            {
                neigbors[idx++] = src[i + k][kCols - 1];
            }
            // 1 0 0
            // 1 0 0
            // 1 0 0
            for (int l = 0; l < kSize2; l++)
            {
                for (int k = -kSize2; k <= kSize2; k++)
                {
                    neigbors[idx++] = src[i + k][kCols - 1];
                }
            }
            // 0 0 1
            // 0 0 1
            // 0 0 1
            for (int k = -kSize2; k <= kSize2; k++)
            {
                for (int s = -kSize2; s <= -1; s++)
                {
                    neigbors[idx++] = src[i + k][kCols + s - 1];
                }
            }
            sort(neigbors, size);
            dst[i][kCols - 1] = neigbors[medIdx];
        }
        delete []neigbors;
    }

    void medianFilterCorner00(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0,
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        idx = 0;        
        // 0 0 0
        // 0 1 1
        // 0 1 1
        for (int k = 0; k <= kSize2; k++)
        {
            for (int s = 0; s <= kSize2; s++)
            {
                neigbors[idx++] = src[k][s];
            }
        }
        // 0 0 0
        // 1 0 0
        // 1 0 0
        for (int k = 0; k <= kSize2; k++)
        {
            neigbors[idx++] = src[k][0];
        }
        // 0 1 1
        // 0 0 0
        // 0 0 0
        for (int s = 0; s <= kSize2; s++)
        {
            neigbors[idx++] = src[0][s];
        }
        // 1 0 0
        // 0 0 0
        // 0 0 0
        for (int k = -kSize2; k <= -1; k++)
        {
            for (int s = -kSize2; s <= -1; s++)
            {
                neigbors[idx++] = src[0][0];
            }
        }
        sort(neigbors, size);
        dst[0][0] = neigbors[medIdx];
        delete []neigbors;
    }

    void medianFilterCorner01(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kCols = src.cols(),
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        idx = 0;        
        // 0 0 0
        // 1 1 0
        // 1 1 0
        for (int k = 0; k <= kSize2; k++)
        {
            for (int s = kCols - kSize2 - 1; s <= kCols - 1; s++)
            {
                neigbors[idx++] = src[k][s];
            }
        }
        // 0 0 0
        // 0 0 1
        // 0 0 1
        for (int k = 0; k <= kSize2; k++)
        {
            neigbors[idx++] = src[k][kCols - 1];
        }
        // 1 1 0
        // 0 0 0
        // 0 0 0
        for (int s = kCols - kSize2 -1; s <= kCols - 1; s++)
        {
            neigbors[idx++] = src[0][s];
        }
        // 0 0 1
        // 0 0 0
        // 0 0 0
        for (int k = 1; k <= kSize2; k++)
        {
            for (int s = 1; s <= kSize2; s++)
            {
                neigbors[idx++] = src[0][kCols - 1];
            }
        }
        sort(neigbors, size);
        dst[0][kCols - 1] = neigbors[medIdx];
        delete []neigbors;
    }

    void medianFilterCorner10(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kRows = src.rows(),
            size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        idx = 0;        
        // 0 1 1
        // 0 1 1
        // 0 0 0
        for (int k = kRows - kSize2 - 1; k <= kRows - 1; k++)
        {
            for (int s = 0; s <= kSize2; s++)
            {
                neigbors[idx++] = src[k][s];
            }
        }
        // 1 0 0
        // 1 0 0
        // 0 0 0
        for (int k = kRows - kSize2 - 1; k <= kRows - 1; k++)
        {
            neigbors[idx++] = src[k][0];
        }
        // 0 0 0
        // 0 0 0
        // 0 1 1
        for (int s = 0; s <= kSize2; s++)
        {
            neigbors[idx++] = src[kRows - 1][s];
        }
        // 0 0 0
        // 0 0 0
        // 1 0 0
        for (int k = 1; k <= kSize2; k++)
        {
            for (int s = -kSize2; s <= -1; s++)
            {
                neigbors[idx++] = src[kRows - 1][0];
            }
        }
        sort(neigbors, size);
        dst[kRows - 1][0] = neigbors[medIdx];
        delete []neigbors;
    }

    void medianFilterCorner11(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        int kSize2 = kSize / 2, idx = 0, kRows = src.rows(), 
            kCols = src.cols(), size = kSize * kSize, medIdx = size / 2;
        uchar *neigbors = new uchar[size];
        idx = 0;        
        // 1 1 0
        // 1 1 0
        // 0 0 0
        for (int k = kRows - kSize2 - 1; k <= kRows - 1; k++)
        {
            for (int s = kCols - kSize2 - 1; s <= kCols - 1; s++)
            {
                neigbors[idx++] = src[k][s];
            }
        }
        // 0 0 1
        // 0 0 1
        // 0 0 0
        for (int k = kRows - kSize2 - 1; k <= kRows - 1; k++)
        {
            neigbors[idx++] = src[k][kCols - 1];
        }
        // 0 0 0
        // 0 0 0
        // 1 1 0
        for (int s = kCols - kSize2 - 1; s <= kCols - 1; s++)
        {
            neigbors[idx++] = src[kRows - 1][s];
        }
        // 0 0 0
        // 0 0 0
        // 0 0 1
        for (int k = 1; k <= kSize2; k++)
        {
            for (int s = 1; s <= kSize2; s++)
            {
                neigbors[idx++] = src[kRows - 1][kCols - 1];
            }
        }
        sort(neigbors, size);
        dst[kRows - 1][kCols - 1] = neigbors[medIdx];
        delete []neigbors;
    }

    void medianFilterCornersPoints(const Matrix &src, Matrix &dst, const int kSize)
    {
        medianFilterCorner00(src, dst, kSize);
        medianFilterCorner01(src, dst, kSize);
        medianFilterCorner10(src, dst, kSize);
        medianFilterCorner11(src, dst, kSize);
    }
};

Filters* createFiltersKustikova()
{
    Filters* filters = new FiltersKustikova();
    return filters;
}
