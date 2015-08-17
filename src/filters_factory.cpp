#include "filters.hpp"

Filters* createFiltersOpenCV();

Filters* createFiltersSemichev();

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl)
{
    switch (impl) {
        case OPENCV:
            return createFiltersOpenCV();
        case SEMICHEV:
            return createFiltersSemichev();
        default:
            return 0;
    }
}
