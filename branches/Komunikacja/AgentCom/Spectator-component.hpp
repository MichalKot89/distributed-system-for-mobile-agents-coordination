#ifndef OROCOS_SPECTATOR_COMPONENT_HPP
#define OROCOS_SPECTATOR_COMPONENT_HPP

#define PLUGINS_DIR            "../plugins/"
#define SPECT_PLUGIN            "libSpect"
#define TECH_INPUT_NAME         "TechInput_"
#define AGENTS_NAME             "Agent"

#include <rtt/RTT.hpp>
#include <rtt/Component.hpp>
#include <rtt/InputPort.hpp>
#include <rtt/OutputPort.hpp>
#include <rtt/Logger.hpp>
#include <rtt/types/StructTypeInfo.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <dlfcn.h>
#include <cmath>

#include "AgentCom-component.hpp"
#include "SpectBase.hh"
#include "Coordinates.hh"
#include "Common.hh"

using namespace std;
using namespace RTT;

/**********************************************/
/**
'AgentCom' class implements component for Agent
****************Periodic task******************
*/
class SpectatorCom
        : public RTT::TaskContext
{
    SpectBase * _SpectPtr;          // Pointer to Agent object
    void* _LibHnd;                  // Handler to plugin library

    int _NumberOfAgents;            // Counts number of updateHook execution since last _TechOutput send
    double _Range;                  // The range of message transmitted from each Agent

    AgentCom ** _AgentsVec;
    InputPort< Coordinates > * _TechInputs;   // Vector of input ports
    InputPort< string > * _FundamentalInputs;   // Vector of input ports
    OutputPort< string > * _FundamentalOutputs;   // Vector of output ports
    vector< Coordinates > _AgentsCoord;                   // Vector of agents coordinates

public:
    SpectatorCom(string const& name): TaskContext(name) {
        _NumberOfAgents = 0;
        _LibHnd = 0;
        _SpectPtr = 0;
    }

    /**
       * This function is for the configuration code.
       * Return false to abort configuration.
       */
    bool SetParameters(int NumOfAgents, double Range) {
        if (NumOfAgents < 0 || Range < 0) return ErrorMesg(getName().c_str(), " bad parameters at SetParameters.");

        if ( !this->isRunning()) {
            _NumberOfAgents = NumOfAgents;  _Range = Range;
        } else return ErrorMesg(this->getName().c_str(), " should not be active!");

        return true;
    }

    /**
       * This function is for the configuration code.
       * Return false to abort configuration.
       */
    /*bool SendFundamentalMessage(string Message) {
        if (_AgentID <= 0 || !this->isConfigured()) return ErrorMesg("Bad Agent ID or Agent not configured!");
        OperationCaller<bool(string)> SendFundOper
                = _ACT.getOperation("SendMessage");

        if ( !SendFundOper(Message) ) {stop ();    cleanup();      return ErrorMesg ("Can't send message, EXIT: ", getName().c_str()); }
        return true;
    }*/




    /** *******************************CONFIGURE*******************************************
       * This function is for the configuration code.
       * Creates all Agents
       * Return false to abort configuration.
       */
    bool configureHook() {
        if (_NumberOfAgents <= 0 || _Range <= 0) return ErrorMesg(getName().c_str(), " bad parameters at configureHook.");
        if ( !AddPlugin(SPECT_PLUGIN) ) return false;



        // Set log level more verbose than default, such that we can see output :
        if ( log().getLogLevel() < RTT::Logger::Info )
            log().setLogLevel( RTT::Logger::Info );



        ///////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////Initializing all ports/////////////////////////////////////
        ostringstream inPortName;
        ostringstream outPortName;

        _FundamentalInputs = new InputPort< string >[_NumberOfAgents];
        _FundamentalOutputs = new OutputPort< string >[_NumberOfAgents];
        _TechInputs = new InputPort< Coordinates >[_NumberOfAgents];
        _AgentsCoord.resize(_NumberOfAgents);

        _SpectPtr->_NumberOfAgents = _NumberOfAgents;


        for (int i = 0; i < _NumberOfAgents; ++i) {

            // INPUT PORTS INITIALISATION //
            inPortName.str("");    inPortName << i+1 << "_" << FUND_INPUT_NAME << getName();
            this->ports()->addEventPort( inPortName.str(), _FundamentalInputs[i] ).doc
                    ( "Input port from Agent to Spectator" );

            // OUTPUT PORTS INITIALISATION //
            outPortName.str("");    outPortName << i+1 << "_" << FUND_OUTPUT_NAME << getName();
            this->ports()->addPort( outPortName.str(), _FundamentalOutputs[i]).doc
                    ( "Output port from Spectator to Agent" );

            // TECH INPUTS INITIALISATION //
            inPortName.str("");    inPortName << i+1 << "_" << TECH_INPUT_NAME << getName();
            this->ports()->addEventPort( inPortName.str(), _TechInputs[i]).doc
                    ( "Output port from Spectator to Agent" );

            // COORDINATIONS VECTOR INITIALISATION //
            Coordinates Tmp(0, 0);
            _AgentsCoord.push_back(Tmp);
        }
        ////////////////////////////////Initializing all ports/////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////



        ///////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////Agents creating and initializing//////////////////////////////////
        _AgentsVec = new AgentCom * [_NumberOfAgents];
        log(Info) << "**** Creating the 'AgentCom' component ****" <<endlog();
        for (int i = 0; i < _NumberOfAgents; ++i) {
            ostringstream AgentsName;     AgentsName << AGENTS_NAME;     AgentsName << i + 1;
            _AgentsVec[i] = new AgentCom(AgentsName.str());
        }



        log(Info) << "**** Setting parameters to the Agent's components'    ****" <<endlog();
        for (int i = 0; i < _NumberOfAgents; ++i)
            if ( !_AgentsVec[i]->SetParameters(i + 1, 0.01, 4)  ) {
                ErrorMesg("Error during setting parameters for ", _AgentsVec[i]->getName().c_str());
                return -1;
            }

        log(Info) << "**** Configuring Agents ****" <<endlog();
        for (int i = 0; i < _NumberOfAgents; ++i)
            if ( !_AgentsVec[i]->configure() ) {
                ErrorMesg("Error during configure of ", _AgentsVec[i]->getName().c_str());
                return -1;
            }

        log(Info) << "**** Connecting Fundamental ports ****" <<endlog();
        ConnPolicy policy = ConnPolicy::buffer(2 * _NumberOfAgents);

        for (int i = 0; i < _NumberOfAgents; ++i) {
            int SenderID = i;   int ReceiverID;
            if (i == _NumberOfAgents - 1) ReceiverID = 0;
            else ReceiverID = SenderID + 1;

            TaskContext & ACT = _AgentsVec[i]->getCommunicationTask();

            ostringstream outPortName;     outPortName << FUND_OUTPUT_NAME;  outPortName << ACT.getName();
            ostringstream inPortName;     inPortName << FUND_INPUT_NAME;     inPortName << ACT.getName();
            ostringstream techPortName;     techPortName << TECH_OUTPUT_NAME;     techPortName << _AgentsVec[i]->getName();

            std::cout << "Con: " << outPortName.str() << " -> " << _FundamentalInputs[i].getName() << std::endl;
            // Agents -> Spectator: Fundamental
            if (   !ACT.ports()->getPort(outPortName.str())->connectTo( (RTT::base::PortInterface *) &_FundamentalInputs[i], policy )   )
                return ErrorMesg("Error during attempting to connect port: ", outPortName.str().c_str());

            std::cout << "Con: " << _FundamentalOutputs[i].getName() << " -> " << inPortName.str() << std::endl;
            // Spectator -> Agents: Fundamental
            if (   !_FundamentalOutputs[i].connectTo( ACT.ports()->getPort(inPortName.str()), policy )   )
                return ErrorMesg("Error during attempting to connect port: ", inPortName.str().c_str());

            std::cout << "Con: " << techPortName.str() << " -> " << _TechInputs[i].getName() << std::endl;
            std::cout << "***************************************************" << std::endl;
            // Agents -> Spectator: Technical
            if (!_AgentsVec[i]->ports()->getPort(techPortName.str())->connectTo( (RTT::base::PortInterface *) &_TechInputs[i], policy )   )
                return ErrorMesg("Error during attempting to connect port: ", techPortName.str().c_str());
        }


        /////////////////////////Agents creating and initializing//////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////


        return this->setPeriod(0); // set to non periodic
    }
    /*********************************\CONFIGURE*******************************************/


    /**
       * This function is for the application's start up code.
       * Return false to abort start up.
       */
    bool startHook() {
        if (!this->isConfigured()) return ErrorMesg("Spectator is not configured, at startHook:", getName().c_str());

        for (int i = 0; i < _NumberOfAgents; ++i) {

            /* INPUT PORTS CHECKING */
            if ( !_FundamentalInputs[i].connected() ) {
                cout << _FundamentalInputs[i].getName() << " is not connected: " << getName() << endl;
                return false;
            }

            /* OUTPUT PORTS CHECKING */
            if ( !_FundamentalOutputs[i].connected() ) {
                cout << _FundamentalOutputs[i].getName() << " is not connected: " << getName() << endl;
                return false;
            }

            /* TECH INPUT PORTS CHECKING */
            if ( !_TechInputs[i].connected() ) {
                cout << _TechInputs[i].getName() << " is not connected: " << getName() << endl;
                return false;
            }
        }

        log(Info) << "**** Starting Agents ****" <<endlog();
        for (int i = 0; i < _NumberOfAgents; ++i) {
            if (  !_AgentsVec[i]->start()  )
                return  ErrorMesg("Error couldn't start: ", _AgentsVec[i]->getName().c_str());
        }
        return true;
    }

    /**
       * Note: use updateHook(const vector<PortInterface*>&)
       * instead for having information about the updated event
       * driven ports.
       */
    void updateHook() {
        if (!this->isConfigured()) {ErrorMesg("Spectator not configured: ", getName().c_str()); return;}

        Coordinates TmpCoord;
        string TmpStr;
        for (int i = 0; i < _NumberOfAgents; ++i) {
            while ( _TechInputs[i].read(TmpCoord) == RTT::NewData ) {
                _AgentsCoord[i] = TmpCoord;
                _SpectPtr->UpdateCoord(_AgentsCoord, i+1);
            }

            while ( _FundamentalInputs[i].read(TmpStr) == RTT::NewData ) {

                // If message can not be sent stop everything
                if ( !SendToAgentsInRange(TmpStr, i) ) { stop(); cleanup(); return; }
                //_SpectPtr->UpdateCoord(_AgentsCoord, i+1);
            }
        }
    }



    /**
       * This function is called when the task is stopped.
       */
    void stopHook() {
    }

    /**
       * This function is called when the task is being deconfigured.
       */
    void cleanupHook() {
        disconnect();
        for (int i = 0; i < _NumberOfAgents; ++i) {
            _AgentsVec[i]->stop();
            _AgentsVec[i]->cleanup();
            delete _AgentsVec[i];
        }
        delete [] _AgentsVec;

        dlclose(_LibHnd);
    }


    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    const string getFundamentalInputName(int id) {
        if (id > 0 && id < _NumberOfAgents)
            return _FundamentalInputs[id].getName();

        return "FAIL";
    }

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    const string getFundamentalOutputName(int id) {
        if (id > 0 && id < _NumberOfAgents)
            return _FundamentalOutputs[id].getName();

        return "FAIL";
    }


    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    const string getTechInputsName(int id) {
        if (id > 0 && id < _NumberOfAgents)
            return _TechInputs[id].getName();

        return "FAIL";
    }

private:
    /**
       * Method finds Agents in range of transmission and send message to them
       */
    bool SendToAgentsInRange(string Mesg, int TransmitterID) {
        for (int i = 0; i < _NumberOfAgents; ++i) {
            if (i == TransmitterID) continue;

            double Distance = sqrt(pow(_AgentsCoord[TransmitterID]._x - _AgentsCoord[i]._x, 2) +
                                   pow(_AgentsCoord[TransmitterID]._y - _AgentsCoord[i]._y, 2));
            if (Distance <= _Range) {
                if (!_FundamentalOutputs[i].connected())
                    return ErrorMesg("Spectator can not send message through: ", _FundamentalOutputs[i].getName().c_str());
                _FundamentalOutputs[i].write(Mesg);
            }
        }
        return true;
    }


    /*!
        * \brief Dodaje nową wtyczkę do listy narzędzi
        *
        * \param sCmdName - nazwa wtyczki
        * \retval true - jeżeli wtyczka istnieje
        * \retval false - w przypadku przeciwnym
        */
    bool AddPlugin(const char* sCmdName) {
        char FilePath[50] = PLUGINS_DIR;
        strcat(FilePath, sCmdName);
        strcat(FilePath, ".so");
        _LibHnd = dlopen(FilePath, RTLD_LAZY);
        if(_LibHnd == NULL) {
            return ErrorMesg("Error during opening plugin. dlerror: ", dlerror());
        }

        SpectBase* (*CreateSpectFunPtr)() = (SpectBase* (*)()) dlsym(_LibHnd, "CreateSpect");
        if (CreateSpectFunPtr == NULL)
            return ErrorMesg("Error during getting handler to the function CreateSpect");

        cout << "Wtyczka zostala dolaczona poprawnie: " << getName() << endl;
        _SpectPtr = (*CreateSpectFunPtr)();
        return true;
    }
};

#endif
