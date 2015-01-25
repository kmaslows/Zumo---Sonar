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
#define SONAR_MEAS_INTERVAL_MS 35

/**
 @brief Defines maximum wanted range of a sonar
 All measurments which return value greather than this, will be changed into 0.
 It is useful when we want to limit background noise picked up by a sonar.
 @todo Function not implemented yet
*/
#define SONAR_MAX_RANGE_CM 50


/**
	@brief Define number of measurment to average. When set to 1, measurments are not avergaged.
	@todo Function not implemented yet
*/
#define SONAR_AVG_NUMBER 3

/**
	@brief Define maximum number of measurment retries.
	In #SINGLE mode when sonar fails to obtain usable data after #SONAR_MAXTRY it will return 0
	In #CONTINOUS mode it will proceed with next sweep step
*/
#define SONAR_MAXTRY 2


/**
 @brief Define Sonar work modes

	Sonar can operate in two modes. #CONTINUOUS  and #SINGLE. In #CONTINUOUS mode
	Sonar triggers are generated periodicaly by TPM.
	In #SINGLE mode, a trigger must be generated by a user
*/	
typedef enum { CONTINUOUS, /**< Repeat measurment every ::SONAR_MEAS_INTERVAL_MS */
							 SINGLE /**< Perform single measurment */
} SonarWorkModes;


/* Global variables */
extern SonarWorkModes SonarMode; 

/* Functions */
void Sonar_init(SonarWorkModes InitialWorkMode);
void SonarDistHandler(uint16_t distance, int32_t angle); 

void EnableSonar(void);
void DisableSonar(void);
void SonarChangeMode(SonarWorkModes NewMode);
void SonarStartMeas(int32_t angle); 
uint16_t SonarGetDistance(int32_t angle);

#endif 
