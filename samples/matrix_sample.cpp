#include "matrix.hpp"
#include "filters.hpp"


using namespace std;

int main()
{
    cout << "---------------------------" << endl;

    Matrix m(3, 4);
    m.Random();
    cout << m;

    cout << "---------------------------" << endl;

    Filters* filters = createFilters(OPENCV);

    Matrix mf(3, 4);
    m.Zeros();
    filters->boxFilter(m, mf);
    cout << mf;

    cout << "---------------------------" << endl;

    return 0;
}
