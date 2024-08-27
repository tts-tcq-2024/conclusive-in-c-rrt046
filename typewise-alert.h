#pragma once

// Enumeration for different cooling types
typedef enum {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
} CoolingType;

// Enumeration for different breach types
typedef enum {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
} BreachType;

// Enumeration for different alert targets
typedef enum {
    TO_CONTROLLER,
    TO_EMAIL
} AlertTarget;

// Structure to represent battery characteristics
typedef struct {
    CoolingType coolingType;
    char brand[48];
} BatteryCharacter;

// Function declarations
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
