#include "Spect.hh"

    bool Spect::UpdateCoord(const std::vector<Coordinates> & Vec, int UpdatedID) {
        std::cout << "Updated: " << UpdatedID << " x value: " << Vec[UpdatedID-1]._x
		  << " y value: " << Vec[UpdatedID-1]._y << std::endl;
        return true;
    }

#ifdef CREATE_LIBRARY
SpectBase * CreateSpect() {
  return new Spect();
}
#endif
