#include "typewise-alert.h"
#include <stdio.h>

// Function to determine the breach type based on temperature and limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    return (value < lowerLimit) ? TOO_LOW :
           (value > upperLimit) ? TOO_HIGH : NORMAL;
}

// Function to classify the temperature breach based on cooling type
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    const double lowerLimits[] = {0, 0, 0};
    const double upperLimits[] = {35, 45, 40};
    return inferBreach(temperatureInC, lowerLimits[coolingType], upperLimits[coolingType]);
}

// Function to check temperature breach and send alerts accordingly
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

// Function to send breach type to controller
void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

// Function to send a low temperature email
void sendLowTemperatureEmail(const char* recipient) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too low\n");
}

// Function to send a high temperature email
void sendHighTemperatureEmail(const char* recipient) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too high\n");
}

// Function to send an email based on breach type
void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    
    // Array of function pointers for different breach types
    void (*emailHandlers[])(const char*) = {nullptr, sendLowTemperatureEmail, sendHighTemperatureEmail};

    // Call the appropriate email function if it exists
    if (emailHandlers[breachType]) {
        emailHandlers[breachType](recipient);
    }
}
