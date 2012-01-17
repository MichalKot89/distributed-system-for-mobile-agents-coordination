/*
 * Agent.hh
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#ifndef SPECT_HH_
#define SPECT_HH_

#include "SpectBase.hh"
#include "Segment.hh"
#include <iostream>
#include <string>
#include <vector>


class Spect
        :public SpectBase
{
public:
    Spect() {
            _NumberOfAgents = 0;
    }
     ~Spect() {}
    bool UpdateCoord(const std::vector<Coordinates> & Vec, int UpdatedID);
};

#ifdef CREATE_LIBRARY
/// Funkcja tworząca obiekt Agent
extern "C" SpectBase * CreateSpect();
#endif

#endif /* SPECT_HH_ */

