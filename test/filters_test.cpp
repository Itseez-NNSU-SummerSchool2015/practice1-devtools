#include "filters.hpp"

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void cvMat2matrix(const Mat &src, Matrix &dst);
void matrix2cvMat(const Matrix &src, Mat &dst);

class FiltersTest : public ::testing::TestWithParam<int>
{
 public:
    virtual void SetUp()
    {
        filters = createFilters(static_cast<FILTERS_IMPLEMENTATIONS>(GetParam()));
    }
    virtual void TearDown()
    {
        delete filters;
    }

    Filters* filters;
};

TEST_P(FiltersTest, DISABLED_box_filter_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), dstExp(5, 5);
    src.Zeros();
    dstExp.Zeros();

    filters->boxFilter(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, DISABLED_box_filter_on_ones_mat)
{
    Matrix src(4, 4), dst(4, 4), expDst(4, 4);
    src.Ones();
    expDst.Ones();

    filters->boxFilter(src, dst);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, DISABLED_box_filter_on_correct_mat)
{
    const std::string input = "./testdata/image.png";
    const std::string expOutput = "./testdata/image_box_filter.png";

    Mat srcMat, expDstMat;
    srcMat = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
    if (srcMat.empty())
    {
        FAIL() << "Can't read" + input + " image";
    }
    expDstMat = imread(expOutput, CV_LOAD_IMAGE_GRAYSCALE);
    if (expDstMat.empty())
    {
        FAIL() << "Can't read" + expOutput + " image";
    }
    Matrix src(srcMat.rows, srcMat.cols),
           expDst(expDstMat.rows, expDstMat.cols),
           dst(src.rows(), src.cols());
    cvMat2matrix(srcMat, src);
    cvMat2matrix(expDstMat, expDst);

    filters->boxFilter(src, dst);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, DISABLED_filter2d_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), kernel(3, 3);
    src.Zeros();
    dst.Zeros();
    kernel.Random();

    filters->filter2d(src, dst, kernel);

    EXPECT_EQ(src, dst);
}

TEST_P(FiltersTest, DISABLED_filter2d_on_ones_mat)
{
    Matrix src(4, 4), dst(4, 4), kernel(3, 3), dstExp(4, 4);
    src.Ones();
    kernel.Ones();
    dstExp[1][1] = dstExp[1][2] = dstExp[2][1] = dstExp[2][2] = 9;
    dstExp[0][0] = dstExp[0][3] = dstExp[3][0] = dstExp[3][3] = 4;
    dstExp[0][1] = dstExp[0][2] = dstExp[3][1] = dstExp[3][2] = 6;
    dstExp[1][0] = dstExp[2][0] = dstExp[1][3] = dstExp[2][3] = 6;

    filters->filter2d(src, dst, kernel);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, DISABLED_filter2d_on_correct_mat)
{
    const std::string input = "./testdata/image.png";
    const std::string expOutput = "./testdata/image_filter2d.png";
    const int kSize = 3;

    Mat srcMat, expDstMat, kernelMat;
    srcMat = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
    if (srcMat.empty())
    {
        FAIL() << "Can't read" + input + " image";
    }
    expDstMat = imread(expOutput, CV_LOAD_IMAGE_GRAYSCALE);
    if (expDstMat.empty())
    {
        FAIL() << "Can't read" + expOutput + " image";
    }

    Matrix src(srcMat.rows, srcMat.cols),
           expDst(expDstMat.rows, expDstMat.cols),
           dst(src.rows(), src.cols()), kernel(kSize, kSize);
    kernel.Ones();

    cvMat2matrix(srcMat, src);
    cvMat2matrix(expDstMat, expDst);

    filters->filter2d(src, dst, kernel);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, median_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), dstExp(5, 5);
    src.Zeros();
    dstExp.Zeros();

    filters->median(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, median_on_simple_mat)
{
    const int size = 4;
    int elem = 0;
    Matrix src(size, size), dst(size, size), dstExp(size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            src[i][j] = elem++;
        }
    }
    dstExp[0][0] = 1;
    dstExp[0][1] = 2;
    dstExp[0][2] = 3;
    dstExp[0][3] = 3;

    dstExp[1][0] = 4;
    dstExp[1][1] = 5;
    dstExp[1][2] = 6;
    dstExp[1][3] = 7;

    dstExp[2][0] = 8;
    dstExp[2][1] = 9;
    dstExp[2][2] = 10;
    dstExp[2][3] = 11;

    dstExp[3][0] = 12;
    dstExp[3][1] = 12;
    dstExp[3][2] = 13;
    dstExp[3][3] = 14;

    filters->median(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, median_on_correct_mat)
{
    const std::string input = "./testdata/image.png";
    const std::string expOutput = "./testdata/image_median_3.png";

    Mat srcMat, expDstMat;
    srcMat = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
    if (srcMat.empty())
    {
        FAIL() << "Can't read" + input + " image";
    }
    expDstMat = imread(expOutput, CV_LOAD_IMAGE_GRAYSCALE);
    if (expDstMat.empty())
    {
        FAIL() << "Can't read" + expOutput + " image";
    }

    Matrix src(srcMat.rows, srcMat.cols),
           expDst(expDstMat.rows, expDstMat.cols),
           dst(src.rows(), src.cols());

    cvMat2matrix(srcMat, src);
    cvMat2matrix(expDstMat, expDst);

    filters->median(src, dst);

    EXPECT_EQ(expDst, dst);
}

TEST_P(FiltersTest, DISABLED_SobelOx_on_zero_mat)
{
    Matrix src(5, 5), dst(5, 5), dstExp(5, 5);
    src.Zeros();
    dstExp.Zeros();

    filters->SobelOx(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, DISABLED_SobelOx_on_ones_mat)
{
    Matrix src(4, 4), dst(4, 4), dstExp(4, 4);
    src.Ones();
    dstExp.Zeros();

    filters->SobelOx(src, dst);

    EXPECT_EQ(dstExp, dst);
}

TEST_P(FiltersTest, DISABLED_sobel_ox_on_correct_mat)
{
    const std::string input = "./testdata/image.png";
    const std::string expOutput = "./testdata/image_sobel_ox.png";

    Mat srcMat, expDstMat;
    srcMat = imread(input, CV_LOAD_IMAGE_GRAYSCALE);
    if (srcMat.empty())
    {
        FAIL() << "Can't read" + input + " image";
    }
    expDstMat = imread(expOutput, CV_LOAD_IMAGE_GRAYSCALE);
    if (expDstMat.empty())
    {
        FAIL() << "Can't read" + expOutput + " image";
    }

    Matrix src(srcMat.rows, srcMat.cols),
           expDst(expDstMat.rows, expDstMat.cols),
           dst(src.rows(), src.cols());

    cvMat2matrix(srcMat, src);
    cvMat2matrix(expDstMat, expDst);

    filters->SobelOx(src, dst);

    EXPECT_EQ(expDst, dst);
}

INSTANTIATE_TEST_CASE_P(Instance,
                        FiltersTest,
                        ::testing::Range<int>((int)OPENCV, (int)NUM_IMPLS));
