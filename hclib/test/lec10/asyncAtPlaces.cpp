#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hclib_cpp.h"

int main(int argc, char ** argv) {	
	hclib::launch([&]() {
        int numPlaces = hclib::get_num_places(hclib::place_type_t::CACHE_PLACE);
        hclib::place_t ** cachePlaces = (hclib::place_t**) malloc(
                sizeof(hclib::place_t*) * numPlaces);
        hclib::get_places(cachePlaces, hclib::place_type_t::CACHE_PLACE);

        hclib::finish([=]() {
            for(int i=0; i<numPlaces; i++) {
                hclib::asyncAtHpt(cachePlaces[i], [=]() {
                    printf("Hello from place %d\n",i);
                });

            }
        });
    });
    return 0;
}
