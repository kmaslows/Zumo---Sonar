#ifndef SONAR_H
#define SONAR_H

#include "MKL46Z4.h"                    // Device header


/**
 @brief Define sonar IRQ priority
*/
#define SONAR_INTERUPT_PRIORITY 2

/**
 @brief Define sonar measurment interval.
 Triggers are send every ::SONAR_MEAS_INTERVAL_MS by TPM1. Setting lower value will increese
 measurmend speed but it will also make sonar more prone to residiual echo from previous measurments.
 @warning Setting this to less than 35ms may produce sensor unsuable due to overlaping echos. 
*/
#define SONAR_MEAS_INTERVAL_MS 25

/**
 @brief Defines maximum wanted range of a sonar
 All measurments which return value greather than this, will be changed into 0.
 It is useful when we want to limit background noise picked up by a sonar.
 @todo Function not implemented yet
*/
#define SONAR_MAX_RANGE_CM 300

/**
	@brief Enable or disable averaging.
	When enabled echo measurment will actually result in average of ::SONAR_AVG_NUMBER measurments
	0 - off
	1 - on
	@todo Function not implemented yet
*/
#define SONAR_AVG_MODE   0 

/**
	@brief Define number of measurment to average.
	When ::SONAR_AVG_MODE is enabled  measurment will actually result in average of ::SONAR_AVG_NUMBER measurments
	@todo Function not implemented yet
*/
#define SONAR_AVG_NUMBER 5


/**
 @brief Define Sonar FSM states
 */
typedef enum { SONAR_IDLE, /**< Idle - waiting for a trigger. */
							 SONAR_TRIGGER_SENT, /**< A trigger was sent. Waiting for echo. */
							 SONAR_CAPTURE_START, /**< Reciving echo and measuring its length */
							 SONAR_CAPTURE_END, /**< Capture complete */
							 SONAR_CAPTURE_OVERFLOW /**< Echo length exceeded maximum value defined by ::SONAR_MAX_RANGE_CM */
} SonarFSM;

/**
 @brief Define Sonar work modes

	Sonar can operate in two modes. #CONTINUOUS  and #SINGLE. In #CONTINUOUS mode
	Sonar triggers are generated periodicaly by TPM.
	In #SINGLE mode, a trigger must be generated by a user
*/	
typedef enum { CONTINUOUS, /**< Repeat measurment every ::SONAR_MEAS_INTERVAL_MS */
							 SINGLE /**< Perform single measurment and go idle */
} SonarWorkModes;


/* Global variables */
extern SonarWorkModes SonarMode; 
extern SonarFSM SonarState;

/* Functions */
void Sonar_init(SonarWorkModes InitialWorkMode);
void SonarDistHandler(uint16_t distance); 
void SonarStartMeas(void); 
uint16_t SonarGetDistance(void);

#endif 
