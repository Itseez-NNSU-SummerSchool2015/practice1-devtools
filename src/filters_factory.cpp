#include "filters.hpp"

Filters* createFiltersOpenCV();
// Declare your implementation here
// Filters* createFiltersYourName();
Filters* createFiltersEkaterina_Maljutina();

Filters* createFilters(FILTERS_IMPLEMENTATIONS impl)
{
    switch (impl) {
        case OPENCV:
            return createFiltersOpenCV();
        // Add case for your implementation
        // case YOUR_NAME:
        //     return createFiltersYourName();
		case Ekaterina_Maljutina:
			return createFiltersEkaterina_Maljutina();
        default:
            return 0;
    }
}

