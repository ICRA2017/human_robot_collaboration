#ifndef __ARM_CONTROLLER_H__
#define __ARM_CONTROLLER_H__

#include "robot_interface/ros_thread.h"
#include "robot_interface/gripper.h"

#include "baxter_collaboration/DoAction.h"

class ArmCtrl : public ROSThread, public Gripper
{
private:
    std::string      name;
    
    std::string    action;
    int         marker_id;

    ros::ServiceServer service;

protected:
    /*
     * This function is still virtual in this class because it will be
     * implemented in its children
     */
    virtual void InternalThreadEntry() = 0;

    /**
     * Recovers from errors during execution. It provides a basic interface,
     * but it is advised to specialize this function in the ArmCtrl's children.
     */
    void recoverFromError();

    /**
     * Hovers above table at a specific x-y position. 
     * @param  height the z-axis value of the end-effector position
     * @return        true/false if success/failure
     */
    bool hoverAboveTable(double height);

    /**
     * Goes to the home position
     * @return        true/false if success/failure
     */
    bool goHome();

public:
    // CONSTRUCTOR
    ArmCtrl(std::string _name, std::string _limb);

    // DESTRUCTOR
    ~ArmCtrl();

    /**
     * Callback for the service that requests actions
     * @param  req the action request
     * @param  res the action response (res.success either true or false)
     * @return     true always :)
     */
    bool serviceCb(baxter_collaboration::DoAction::Request  &req,
                   baxter_collaboration::DoAction::Response &res);

    /* Self-explaining "setters" */
    void setName  (std::string _name)   { name      =   _name; };
    void setAction(std::string _action) { action    = _action; };
    void setMarkerID(int _id)           { marker_id =     _id; };

    /* Self-explaining "getters" */
    std::string getName()     { return      name; };
    std::string getAction()   { return    action; };
    int         getMarkerID() { return marker_id; };
};

#endif