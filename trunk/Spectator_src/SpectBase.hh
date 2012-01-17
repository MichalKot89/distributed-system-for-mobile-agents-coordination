/*
 * AgentBase.hh
 *
 */

#ifndef SPECT_BASE_HH
#define SPECT_BASE_HH

#include "Coordinates.hh"
#include <iostream>
#include <string>
#include <vector>


class SpectBase {
public:
int _NumberOfAgents;

        SpectBase() {
                _NumberOfAgents = 0;
	}
        virtual ~SpectBase() {}
        virtual bool UpdateCoord(const std::vector<Coordinates> &, int) = 0;
};

#endif /* SPECT_BASE_HH */
