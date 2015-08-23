#include "filters.hpp"

Filters* createFiltersOpenCV();
Filters* createFiltersKustikova();

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl)
{
    switch (impl) {
        case OPENCV:
            return createFiltersOpenCV();
        case KUSTIKOVA:
             return createFiltersKustikova();
        default:
            return 0;
    }
}
