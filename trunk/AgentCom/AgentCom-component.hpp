#ifndef OROCOS_AGENTCOM_COMPONENT_HPP
#define OROCOS_AGENTCOM_COMPONENT_HPP

//#define PLUGINS_DIR            "./"
#define PLUGINS_DIR            "../plugins/"
#define AGENT_PLUGIN            "libAgent"
#define TIMER_INPUT_NAME         "TimerInput_"
#define FUND_INPUT_NAME         "FundamentalInput_"
#define FUND_OUTPUT_NAME         "FundamentalOutput_"
#define TECH_OUTPUT_NAME         "TechOutput_"
#define AGENT_COMMUNICATION_TASK_NAME "AgentCommunicationCom"

#include <rtt/RTT.hpp>
#include <ocl/OCL.hpp>
#include <ocl/TimerComponent.hpp>
#include <iostream>
#include <rtt/Component.hpp>
#include <rtt/InputPort.hpp>
#include <rtt/OutputPort.hpp>
#include <rtt/Logger.hpp>
#include <rtt/os/Timer.hpp>
#include <rtt/os/TimeService.hpp>
#include <rtt/types/StructTypeInfo.hpp>
#include <list>
#include <string>
#include <sstream>
#include <dlfcn.h>

//#include <QtGui/QApplication>
#include "mainwindow.h"
#include "agentwindow.h"
#include "simulationwindow.h"
#include "scenewindow.h"

#include "AgentBase.hh"
#include "Coordinates.hh"
#include "Common.hh"
#include "Segment.hh"


using namespace std;
using namespace RTT;
using namespace Orocos;


//Connect two strings into one
string ConnecStrs(string const & Str1, string const & Str2);


/**********************************************/
/**
'AgentCommunicationCom' class implements tools for Agents
 to communicate.
 Task starts it's work when it receives message or when
 we want to send message saved in buffer (triggering)
 *************NonPeriodic task******************
*/
class AgentCommunicationCom
    : public RTT::TaskContext
{
    AgentBase * _AgentPtr;                  // Pointer to Agent object

    TimerComponent _TimerComponent;    // Timer component

    double _InterestTimerVal;               // Interest Timer wait time
    double _PlaceTimerVal;                  // Place Timer wait time

    list <string> _OutputBuffer;

    InputPort<RTT::os::Timer::TimerId> _TimerInput;    // Input port: We'll let this one wake up our thread
    InputPort<string> _FundamentalInput;    // Input port: We'll let this one wake up our thread
    OutputPort<string> _FundamentalOutput;       // Input port: We will poll this one
    bool _FlagTmp;

 public:
    AgentCommunicationCom(string const& name)
        : TaskContext(name), _TimerComponent(ConnecStrs(name, "_Timer"))
    {
        ErrorMesg("Constructor: ", name.c_str());
        _AgentPtr = 0;

        _InterestTimerVal = 0;
        _PlaceTimerVal = 0;
        _FlagTmp = true;

        _TimerInput;
        ostringstream inPortName;     inPortName << TIMER_INPUT_NAME ;     inPortName << name;
        // an 'EventPort' is an InputPort which wakes our task up when data arrives.
        this->ports()->addEventPort( inPortName.str(), _TimerInput ).doc
                ( "Input Port that raises an event." );


        inPortName.str("");     inPortName << FUND_INPUT_NAME;     inPortName << name;
        // an 'EventPort' is an InputPort which wakes our task up when data arrives.
        this->ports()->addEventPort( inPortName.str(), _FundamentalInput ).doc
                                   ( "Input Port that raises an event." );

        ostringstream outPortName;      outPortName << FUND_OUTPUT_NAME;     outPortName << name;
        // an 'EventPort' is an InputPort which wakes our task up when data arrives.
        this->ports()->addPort( outPortName.str(), _FundamentalOutput ).doc
                              ( "Output port from Agent to Agent" );

        ConnPolicy policy = ConnPolicy::buffer(10);
        if (   !_TimerInput.connectTo ( _TimerComponent.ports()->getPort("timeout"), policy )   )
            ErrorMesg("Error during attempting to connect port _TimerInput");

//        this->addOperation( "getInputName", &AgentCommunicationCom::ConnectInput, this, OwnThread)
//                .doc("Return input port name");
        this->addOperation( "SendMessage", &AgentCommunicationCom::SendMessage, this, OwnThread)
                .doc("Send message via output port").arg("Message", "String message to send");
        this->addOperation( "getInputName", &AgentCommunicationCom::getInputName, this, OwnThread)
                .doc("Returns input port name.");
        this->addOperation( "getOutputName", &AgentCommunicationCom::getOutputName, this, OwnThread)
                .doc("Returns output port name.");
    }
		~AgentCommunicationCom(){}

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool configureHook() {
        return this->setPeriod(0); // set to non periodic.
    }

    /**
   * This function is for the application's start up code.
   * Return false to abort start up.
   */
    bool startHook() {
        // Check validity of (all) Ports:
        if ( !_FundamentalInput.connected() ) {
            return ErrorMesg("_FundamentalInput is not connected: ", this->getName().c_str());
        }

        if ( !_FundamentalOutput.connected() ) {
            return ErrorMesg("_FundamentalOutput is not connected: ", this->getName().c_str());
        }

        if ( !_TimerInput.connected() ) {
            return ErrorMesg("_FundamentalOutput is not connected: ", this->getName().c_str());
        }
        _AgentPtr->LoadParams();
        return true;
    }

    /**
   * Note: use updateHook(const vector<PortInterface*>&)
   * instead for having information about the updated event
   * driven ports.
   */
    void updateHook() {
        if (!this->isConfigured() || _AgentPtr == 0) {ErrorMesg(this->getName().c_str(), " not configured!"); return;}

        // Event
        RTT::os::Timer::TimerId T_ID;
        string Command;
        OperationCaller<bool(string)> SendMessageOper = this->getOperation("SendMessage");

        //cout << "updateHook: " << _TimerComponent.timeRemaining (0) << ": " << getName() << endl;
        while ( _FundamentalInput.read(Command) == RTT::NewData ) {
            //cout << "updateHook Got message " << Command << ": " << getName() << endl;
            if ( !_AgentPtr->ProcessMessage(Command, _OutputBuffer) )
            {ErrorMesg("Bad command received: ", this->getName().c_str()); return;}
        }

        while ( _TimerInput.read(T_ID) == RTT::NewData ) {
            //cout << "updateHook Got message " << Command << ": " << getName() << endl;
            if ( !_AgentPtr->TimerTimeout(T_ID, _OutputBuffer) )
            {ErrorMesg("Wrong timer ID: ", this->getName().c_str()); return;}
        }

        //cout << "updateHook BuffSize: " << _OutputBuffer.size() << ": " << getName() << endl;
        while ( !_OutputBuffer.empty() ) {
            //cout << "updateHook: " << _OutputBuffer.front() << ": " << getName() << endl;
            _FlagTmp = false;
            SendMessage(_OutputBuffer.front());
            //if ( !SendMessageOper(_OutputBuffer.front()) ) {ErrorMesg("Couldn't send message: ", this->getName().c_str()); return;}
            _OutputBuffer.pop_front();
        }
    }

    /**
   * This function is called when the task is being deconfigured.
   */
    void cleanupHook() {
        disconnect();
        _TimerComponent.cleanup();
    }


    /**
   * This function is called when the task is stopped.
   */
    void stopHook() {
        _TimerComponent.stop();
    }

    /* This function is called each time an armed or periodic timer expires.  */
    /*void timeout (os::Timer::TimerId timer_id) {
        ostringstream MessageStream;
        cout << "Dupa" << endl;
        switch (timer_id) {
        case 0:
            cout << "Finished Interest Timer" << endl;
            MessageStream << "INTEREST_TIMER_FINISHED" << endl;    // is there anybody who is interested in sector
            MessageStream << _AgentPtr->_MyID << endl;        // Agents ID
            MessageStream << _AgentPtr->_MyID << endl;        // Row number
            MessageStream << "END" << endl;
            _InputBuffer.push_front(MessageStream.str());
            trigger();
            break;
        case 1:
            cout << "Finished Place Timer" << endl;
            MessageStream << "PLACE_TIMER_FINISHED" << endl;    // is there anybody who is interested in sector
            MessageStream << _AgentPtr->_MyID << endl;        // Agents ID
            MessageStream << _AgentPtr->_MyID << endl;        // Row number
            MessageStream << "END" << endl;
            _InputBuffer.push_front(MessageStream.str());
            trigger();
            break;
        default:
            ErrorMesg("Wrong timer ID");
            killTimer (timer_id);
            break;

        }

    }*/

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool NewAgentObject(AgentBase* AgentPtr) {
        if (AgentPtr == 0)
            return ErrorMesg("Agent object is NULL: ", this->getName().c_str());
        _AgentPtr = AgentPtr;
        return true;
    }


    /**
   * This function arms timer of ID = 'TimerID'
   * for wait time = 'TimeStep'
   */
    bool SetTimerValue (int TimerID, double TimerVal) {
        if (TimerVal <= 0) return ErrorMesg("Wrong timer value");

        if (TimerID == 0)   _InterestTimerVal = TimerVal;
        else if (TimerID == 1)   _PlaceTimerVal = TimerVal;
        else return ErrorMesg("Bad timer ID: ");

        return true;
    }

/*********************PRIVATE**************************/
private:

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    const string & getInputName() {
        return _FundamentalInput.getName();
    }

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    const string & getOutputName() {
        return _FundamentalOutput.getName();
    }

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool SendMessage(string Message) {

        if ( !_FundamentalOutput.connected() ) {
            return ErrorMesg("_FundamentalOutput is not connected: ", this->getName().c_str());
        }

        string CommandName;
        int AgentID, ReceiverID;
        int RowNum;
        int ColumnNum;
        OperationCaller<bool(RTT::os::Timer::TimerId, double)> TimerArmOper = _TimerComponent.getOperation("arm");


        _AgentPtr->MessageFitsToAgent(Message, CommandName, AgentID, RowNum, ColumnNum);
        if (CommandName == "INTEREST" && AgentID == _AgentPtr->_MyID) {
            if ( _InterestTimerVal > 0 ) {
                cout << "Started Interest Timer, value: " << _InterestTimerVal << endl;
                if ( !TimerArmOper(0, _InterestTimerVal) ) return ErrorMesg("Place timer couldn't be set");
            }
            else return ErrorMesg("Interest timer val is not set")   ;
        }

        if (CommandName == "PLACE" && AgentID == _AgentPtr->_MyID) {
            if ( _PlaceTimerVal > 0 ) {
                cout <<  "Started Place Timer, value: " << _PlaceTimerVal << endl;
                if ( !TimerArmOper(1, _PlaceTimerVal) ) return ErrorMesg("Place timer couldn't be set");
            }
            else return ErrorMesg("Place timer val is not set")   ;
        }
        //cout << "SendMessage: " << Message << ": " << getName() << endl;
        //if (_FlagTmp == true) {
        _FundamentalOutput.write( Message );
        //} else _FundamentalOutput.write( "Dupa" );
        return true;
    }


};






/**********************************************/
/**
'AgentCom' class implements component for Agent
****************Periodic task******************
*/
class AgentCom
    : public RTT::TaskContext
{
public:
    AgentCommunicationCom _ACT;   // Pointer to AgentCommunicationCom object
    AgentBase * _AgentPtr;          // Pointer to Agent object
    void* _LibHnd;                  // Handler to plugin library

    double _Time;                   // Actual time
    int _AgentID;                   // Agent's number
    double _TimeStep;               // Coordinates refreshing step time
    int _FreqPrescaler;             // Prescaler for technical message frequency
    int _UpdateCount;               // Counts number of updateHook execution since last _TechOutput send
    Coordinates _PrevCoord;         // Previous coordinates of Agent


    OutputPort< Coordinates > _TechOutput;   // Output ports are allways 'send and forget'

 public:
    AgentCom(string const& name)
        : TaskContext(name), _ACT(ConnecStrs(name, "_Communication"))
    {
        ErrorMesg("Constructor: ", name.c_str());
        _AgentID = 0;         _TimeStep = 0;
        _FreqPrescaler = 0;   _UpdateCount = 0;     _Time = 0;
        _PrevCoord._x = 0;      _PrevCoord._y = 0;


        ostringstream outPortName;      outPortName << TECH_OUTPUT_NAME;     outPortName << name;
        // an 'EventPort' is an InputPort which wakes our task up when data arrives.
        this->ports()->addPort( outPortName.str(), _TechOutput ).doc
                              ( "Output port from Agent to Spectator" );

        this->addOperation( "SetParameters", &AgentCom::SetParameters, this, OwnThread)
                .doc("Change a parameter, return the old value.")
                .arg("AgentID", "Agent's number.")
                .arg("TimeStep", "Time to the next coordinate refresh.")
                .arg("FreqPrescaler", "Prescaler for updateHook periodical freqency.");
    }

    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool SetParameters(int AgentID, double TimeStep, int FreqPrescaler) {
        if (AgentID < 0 || TimeStep <= 0 || FreqPrescaler < 0) return ErrorMesg(getName().c_str(), " bad parameters at SetParameters.");

        if ( !this->isRunning()) {
            _AgentID = AgentID;               _TimeStep = TimeStep;
            _FreqPrescaler = FreqPrescaler;   _UpdateCount = 0;
            _ACT.SetTimerValue (0, 0.1*TimeStep); _ACT.SetTimerValue (1, 0.1*TimeStep);
        } else return ErrorMesg(this->getName().c_str(), " should not be active!");
        return true;
    }



    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool configureHook() {

        if ( !AddPlugin(AGENT_PLUGIN) ) return false;


        _AgentPtr->_MyID = _AgentID;
        _AgentPtr->_TimeStep = _TimeStep;

        _ACT.configure();

        return this->setPeriod(_TimeStep); // set to 1000Hz execution mode.
    }

    /**
   * This function is for the application's start up code.
   * Return false to abort start up.
   */
    bool startHook() {
        if (!this->isConfigured()) return ErrorMesg("Agent is not configured, at startHook:", getName().c_str());
        if ( !_TechOutput.connected() ) {
            cout << "_TechOutput is not connected: Agent" << _AgentID << endl;
        }
        _ACT.start();
        return true;
    }

    /**
   * Note: use updateHook(const vector<PortInterface*>&)
   * instead for having information about the updated event
   * driven ports.
   */
    void updateHook() {
        if (_AgentID <= 0 || !this->isConfigured()) {ErrorMesg("Bad Agent ID or Agent not configured!"); return;}

        // RUN 1 STEP TIME
        _AgentPtr->Run();
        // Inform spectator about actual position
        ++_UpdateCount;
        if (_UpdateCount > _FreqPrescaler) {
            Coordinates ActualCoord = _AgentPtr->GetActualPosition();
            if (!(ActualCoord == _PrevCoord)) {
               _TechOutput.write( ActualCoord );
                _PrevCoord = ActualCoord;
                _UpdateCount = 0;
            }
        }
        cout<<"updateHook2"<<endl;
        // perform the operation adequate to actual status
        AgentBase::Status AgentStatus = _AgentPtr->GetStatus();
        //cout << AgentStatus << endl;
        if (AgentStatus != AgentBase::Moving && AgentStatus != AgentBase::Finished) {
            if (AgentStatus == AgentBase::ERROR) {ErrorMesg ("ERROR state, EXIT"); stop(); cleanup(); return;}
            else    SendFundamentalMessage( _AgentPtr->StateMessage() );
        }

        _Time += _TimeStep;
    }


    /**
   * This function is called when the task is stopped.
   */
    void stopHook() {
        _ACT.stop();
    }

    /**
   * This function is called when the task is being deconfigured.
   */
    void cleanupHook() {
        disconnect();
        _ACT.cleanup();
        dlclose(_LibHnd);
    }


    /**
   * Returns fundamental input name
   */
    const string & getFundamentalInputName () {
        OperationCaller<const string &(void)> GetNameOper
               = _ACT.getOperation("getInputName");
        return GetNameOper();
    }

    /**
   * Returns fundamental output name
   */
    const string & getFundamentalOutputName () {
        OperationCaller<const string &(void)> GetNameOper
               = _ACT.getOperation("getOutputName");
        return GetNameOper();
    }

    /**
   * Returns fundamental output name
   */
    TaskContext & getCommunicationTask () {
        return _ACT;
    }

private:
    /**
   * This function is for the configuration code.
   * Return false to abort configuration.
   */
    bool SendFundamentalMessage(string Message) {
        if (_AgentID <= 0 || !this->isConfigured()) return ErrorMesg("Bad Agent ID or Agent not configured!");
        OperationCaller<bool(string)> SendFundOper
               = _ACT.getOperation("SendMessage");

        if ( !SendFundOper(Message) ) {stop ();    cleanup();      return ErrorMesg ("Can't send message, EXIT: ", getName().c_str()); }
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

        AgentBase* (*CreateAgentFunPtr)() = (AgentBase* (*)()) dlsym(_LibHnd, "CreateAgent");
        if (CreateAgentFunPtr == NULL)
            return ErrorMesg("Error during getting handler to the function CreateAgent");

        cout << "Wtyczka zostala dolaczona poprawnie: " << getName() << endl;
        _AgentPtr = (*CreateAgentFunPtr)();

        _ACT.NewAgentObject(  _AgentPtr  );
        return true;
    }
};

#endif
