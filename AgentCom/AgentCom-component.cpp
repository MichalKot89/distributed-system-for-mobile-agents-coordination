#include <rtt/Component.hpp>
#include <rtt/os/main.h>



#include "Spectator-component.hpp"
#include "AgentCom-component.hpp"

#include <QtGui/QApplication>

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

string ConnecStrs(string const & Str1, string const & Str2) {
    string ResoultStr(Str1);
    ResoultStr.append(Str2);
    cout << "Polaczono stringi w ciag: " << ResoultStr;
    return ResoultStr;
}

// This define allows to compile the hello world component as a library
// AgentsCom.so or as a program (AgentsCommunication). Your component
// should only be compiled as a library.
#ifndef OCL_COMPONENT_ONLY

int ORO_main(int argc, char** argv)
{
    RTT::Logger::In in("main()");

		QApplication a(argc, argv);
    // Tell the RTT the name and type of this struct:
    types::Types()->addType( new CoordinatesTypeInfo() );


    SpectatorCom Spectator(SPECT_NAME);
    //Spectator.show();

    /*if (  !AgentsVec[0]->SendFundamentalMessage(AgentsVec[0]->getName())  ) {
        ErrorMesg("Error didn't manage to send message: ", AgentsVec[0]->getName().c_str());
        return -1;
    }*/
                //Spectator.show();
    sleep(1);
    //Spectator.stop();
    //Spectator.cleanup();
//.show();
		//app.exec();
    return a.exec();
    Spectator.stop();
    Spectator.cleanup();
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
