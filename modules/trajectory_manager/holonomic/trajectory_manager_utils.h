#ifndef _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_
#define _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_

/** @todo : check les inludes et faire les comment
 * Faire les bons nom de fonctions */
#include <aversive.h>
#include <aversive/error.h>
#include <holonomic/robot_system.h>
#include <holonomic/trajectory_manager.h>
#include <vect2.h>

/** Event's period */
#define TRAJ_EVT_PERIOD (25000UL/SCHEDULER_UNIT) /** < 25 ms */

/** Event that set a consign for robot_system depending on the trajectory */
void holonomic_trajectory_manager_event(void * param);

/** True if the robot is within the distance d_win of the trajectory's target */
uint8_t holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win);

/** True if the robot faces a certain angular area */
uint8_t holonomic_robot_in_angle_window(struct h_trajectory *traj, double a_win_rad);

/** Delete a trajectory event */
void holonomic_delete_event(struct h_trajectory *traj);

/** True when trajectory is finished */
int8_t holonomic_end_of_traj(struct h_trajectory *traj);

/** Schedules a trajectory event */
void holonomic_schedule_event(struct h_trajectory *traj);

/** do a modulo 2.pi -> [-Pi,+Pi], knowing that 'a' is in [-3Pi,+3Pi] */
double holonomic_simple_modulo_2pi(double a);

/** do a modulo 2.pi -> [-Pi,+Pi] */
double holonomic_modulo_2pi(double a);

/** calculates the lenght of an arc of a circle given an end point and a radius */
 /** calculates the lenght of an arc of a circle given an end point and a radius */
float holonomic_length_arc_of_circle_pnt(struct h_trajectory *traj, float rad);

/** @brief Calculates the angle between the robot and a facing point.
* @param *traj Reference to the values of the trajectory.
* @param *fpc Cartesien vector to the point that needs to be faced.
**/
float holonomic_angle_facepoint_rad(struct h_trajectory *traj, vect2_cart *fpc);

/** @brief Calculates an angle that is offset by a certain angle to the speedvector. 
* @param *traj Reference to the values of the trajectory.
* @param ao The offset angle.
**/
float holonomic_angle_2_speed_rad(struct h_trajectory *traj, float ao);

/** @brief Calculates the difference between the angle of the robot and a wished angle. 
* @param *traj Reference to the values of the trajectory.
* @param ao The wished angle to the x-axis.
**/
float holonomic_angle_2_x_rad(struct h_trajectory *traj, float a);

/** @brief Calculates if the positiv or the negativ rotation is better. 
* @param d_a An angle.
**/
float holonomic_best_delta_angle_rad(float a);

/** set the consign to robot_system_hlonomic */
void set_consigns_to_rsh(struct h_trajectory *traj, int32_t speed, int32_t direction, int32_t omega);

#endif

