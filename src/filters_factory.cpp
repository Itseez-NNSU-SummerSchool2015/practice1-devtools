#include "filters.hpp"

Filters* createFiltersOpenCV();
// Declare your implementation here
Filters* createFiltersShchedrin();

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl)
{
    switch (impl) {
        case OPENCV:
            return createFiltersOpenCV();
        // Add case for your implementation
        case SHCHEDRIN:
            return createFiltersShchedrin();
        default:
            return 0;
    }
}
