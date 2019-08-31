/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/WPILib.h>
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "commands/driveCommand.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <CameraServer.h>
#include <networktables/NetworkTableInstance.h>
ExampleSubsystem Robot::m_subsystem;
//driveSubsystem Robot::m_drive;
//OI Robot::m_oi;
//frc::DigitalInput* limitSwitch;
void Robot::RobotInit() {
  CommandBase::init();
  teleopchooser = new frc::SendableChooser<frc::Command*>;
  teleopchooser->SetDefaultOption("Tank Driving", new driveCommand());
  //limitSwitch = new frc::DigitalInput(1);
  frc::SmartDashboard::PutData("Teleop Modes", teleopchooser);
  //frc::CameraServer::GetInstance()->StartAutomaticCapture();
  camera1 = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  camera2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {

    teleopCommand = (frc::Command *) teleopchooser->GetSelected();

  if (teleopCommand != nullptr) {
    teleopCommand->Start();
  }
  /*
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

  m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }
  */
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  /*
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
*/
  teleopCommand = (frc::Command *) teleopchooser->GetSelected();

  if (teleopCommand != nullptr) {
    teleopCommand->Start();
  }
}

void Robot::TeleopPeriodic() {  
    frc::Scheduler::GetInstance()->Run(); 


 /*  if (oi->logiStick->GetRawButton(8)) {
    printf("Setting camera 2\n");
    nt::NetworkTableInstance::GetDefault().GetTable("")->PutString("CameraSelection", camera2.GetName());
  } else if (!oi->logiStick->GetRawButton(8)) {
    printf("Setting camera 1\n");
    nt::NetworkTableInstance::GetDefault().GetTable("")->PutString("CameraSelection", camera1.GetName());
  } */
} 


void Robot::TestInit() {

// JUST COPIED THE TELEOPINIT HERE. 


    // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }

  teleopCommand = (frc::Command *) teleopchooser->GetSelected();

  if (teleopCommand != nullptr) {
    teleopCommand->Start();
  }
}

void Robot::TestPeriodic() {
  frc::Scheduler::GetInstance()->Run(); 
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
