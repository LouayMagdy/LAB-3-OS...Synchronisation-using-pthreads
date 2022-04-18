#include <pthread.h>

struct station {
    pthread_mutex_t inTheStation;
    pthread_cond_t trainArrived; /////to make the passenger wait till train arrives
    pthread_cond_t trainCanLeave; ////train can go on
    int availableSeatsNo; ////no. of available seats in the train
    int waitingPassengersNo; ///no. of waiting passsengers
    int departedPassengersNo; ///no. of departed passengers
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);