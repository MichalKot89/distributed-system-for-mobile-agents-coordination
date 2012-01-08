#include "Spect.hh"

    bool Spect::UpdateCoord(const std::vector<Coordinates> & Vec, int UpdatedID) {
        //std::cout << "Updated: " << UpdatedID << " x value: " << Vec[UpdatedID]._x
	//	  << " y value: " << Vec[UpdatedID]._y << std::endl;
        return true;
    }

#ifdef CREATE_LIBRARY
SpectBase * CreateSpect() {
  return new Spect();
}
#endif
