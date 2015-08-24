#include "filters.hpp"

class FiltersKustikova : public Filters
{
 public:
    virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3)
    {
        
    }

    virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        if (kernel.rows() != kernel.cols())
        {
            std::cout << "Kernel should have square sizes." << std::endl;
            return;
        }
        filter2dInternalPoints(src, dst, kernel);
        filter2dTopBorderPoints(src, dst, kernel);
        filter2dButtomBorderPoints(src, dst, kernel);
        filter2dLeftBorderPoints(src, dst, kernel);
        filter2dRightBorderPoints(src, dst, kernel);
        filter2dCornersPoints(src, dst, kernel);
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

    void medianFilterCornersPoints(
        const Matrix &src, Matrix &dst, const int kSize)
    {
        medianFilterCorner00(src, dst, kSize);
        medianFilterCorner01(src, dst, kSize);
        medianFilterCorner10(src, dst, kSize);
        medianFilterCorner11(src, dst, kSize);
    }

    void filter2dInternalPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2;
        for (int i = kSize; i < src.rows() - kSize; i++)
        {
            for (int j = kSize; j < src.cols() - kSize; j++)
            {
                int conv = 0;
                for (int k = -kSize; k <= kSize; k++)
                {
                    for (int s = -kSize; s <= kSize; s++)
                    {
                        conv += kernel[k + kSize][s + kSize] * src[i + k][j + s];
                    }
                }
                dst[i][j] = (conv > 255) ? 255 : (uchar)conv;
            }
        }
    }

    void filter2dTopBorderPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2;
        for (int j = kSize; j < src.cols() - kSize; j++)
        {
            int conv = 0;
            for (int k = 0; k <= kSize; k++)
            {
                for (int s = -kSize; s <= kSize; s++)
                {
                    conv += kernel[k + kSize][s + kSize] * src[k][j + s];
                }
            }
            dst[0][j] = (conv > 255) ? 255 : (uchar)conv;
        }
    }

    void filter2dButtomBorderPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2;
        for (int j = kSize; j < src.cols() - kSize; j++)
        {
            int conv = 0;
            for (int k = -kSize; k <= 0; k++)
            {
                for (int s = -kSize; s <= kSize; s++)
                {
                    conv += kernel[k + kSize][s + kSize] * src[src.rows() - 1 + k][j + s];
                }
            }
            dst[src.rows() - 1][j] = (conv > 255) ? 255 : (uchar)conv;
        }
    }

    void filter2dLeftBorderPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2;
        for (int i = kSize; i < src.rows() - kSize; i++)
        {
            int conv = 0;
            for (int k = -kSize; k <= kSize; k++)
            {
                for (int s = 0; s <= kSize; s++)
                {
                    conv += kernel[k + kSize][s + kSize] * src[i + k][s];
                }
            }
            dst[i][0] = (conv > 255) ? 255 : (uchar)conv;
        }
    }

    void filter2dRightBorderPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2;
        for (int i = kSize; i < src.rows() - kSize; i++)
        {
                int conv = 0;
                for (int k = -kSize; k <= kSize; k++)
                {
                    for (int s = -kSize; s <= 0; s++)
                    {
                        conv += kernel[k + kSize][s + kSize] * src[i + k][src.cols() - 1 + s];
                    }
                }
                dst[i][src.cols() - 1] = (conv > 255) ? 255 : (uchar)conv;
        }
    }    

    void filter2dCornersPoints(
        const Matrix &src, Matrix& dst, const Matrix &kernel)
    {
        int kSize = kernel.rows() / 2, conv = 0;
        for (int k = 0; k <= kSize; k++)
        {
            for (int s = 0; s <= kSize; s++)
            {
                conv += kernel[k + kSize][s + kSize] * src[k][s];
            }
        }
        dst[0][0] = (conv > 255) ? 255 : (uchar)conv;
                
        conv = 0;
        for (int k = 0; k <= kSize; k++)
        {
            for (int s = -kSize; s <= 0; s++)
            {
                conv += kernel[k + kSize][s + kSize] * src[k][src.cols() - 1 + s];
            }
        }
        dst[0][src.cols() - 1] = (conv > 255) ? 255 : (uchar)conv;

        conv = 0;
        for (int k = -kSize; k <= 0; k++)
        {
            for (int s = 0; s <= kSize; s++)
            {
                conv += kernel[k + kSize][s + kSize] * src[src.rows() - 1 + k][s];
            }
        }
        dst[src.rows() - 1][0] = (conv > 255) ? 255 : (uchar)conv;

        conv = 0;
        for (int k = -kSize; k <= 0; k++)
        {
            for (int s = -kSize; s <= 0; s++)
            {
                conv += kernel[k + kSize][s + kSize] * src[src.rows() - 1 + k][src.cols() - 1 + s];
            }
        }
        dst[src.rows() - 1][src.cols() - 1] = (conv > 255) ? 255 : (uchar)conv;
    }
};

Filters* createFiltersKustikova()
{
    Filters* filters = new FiltersKustikova();
    return filters;
}
