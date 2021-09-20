#ifndef BIKE_H /* include guards */
#define BIKE_H

class Bike{
    public:
        Bike(int pin);
        void readBikeInput();
        int nImpulse;
        float nMetersPerCycle;
        int nMetersTraveled;
        float nKmTraveled;
        int nSeconds;
        float nAverageSpeed;
        float nCalories;
    private:
        void updateBikeData();
        void bikeSerialOut();
        int bikePin;
        
        int counter;
        int reading;
        int current_state;
        long milTime;
        int debounce_count;
        bool lowTriggered;

};

#endif 