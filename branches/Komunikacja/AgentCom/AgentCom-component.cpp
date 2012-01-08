#include "AgentCom-component.hpp"
#include "Spectator-component.hpp"
#include <rtt/Component.hpp>
#include <rtt/os/main.h>

#define SPECT_NAME      "Spectator"



namespace boost {
    namespace serialization {
      // The helper function which you write yourself:
      template<class Archive>
      void serialize( Archive & a, Coordinates & Coord, unsigned int) {
         using boost::serialization::make_nvp;
         a & make_nvp("_x", Coord._x);
         a & make_nvp("_y", Coord._y);
      }
    }
  }

// The RTT helper class which uses the above function behind the scenes:
struct CoordinatesTypeInfo
        : public RTT::types::StructTypeInfo<Coordinates>
{
    CoordinatesTypeInfo()
        : RTT::types::StructTypeInfo<Coordinates>("Coordinates")
    {}
};



// This define allows to compile the hello world component as a library
// AgentsCom.so or as a program (AgentsCommunication). Your component
// should only be compiled as a library.
#ifndef OCL_COMPONENT_ONLY

int ORO_main(int argc, char** argv)
{
    RTT::Logger::In in("main()");

    // Tell the RTT the name and type of this struct:
    types::Types()->addType( new CoordinatesTypeInfo() );

    SpectatorCom Spectator(SPECT_NAME);
    if ( !Spectator.SetParameters(3,5) ) return -1;
    if ( !Spectator.configure() ) return -1;
    if ( !Spectator.start() ) return -1;


    /*if (  !AgentsVec[0]->SendFundamentalMessage(AgentsVec[0]->getName())  ) {
        ErrorMesg("Error didn't manage to send message: ", AgentsVec[0]->getName().c_str());
        return -1;
    }*/

    sleep(5);
    Spectator.stop();
    Spectator.cleanup();

    return 0;
}

#else

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use 
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(AgentCom)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(AgentCom)

#endif
