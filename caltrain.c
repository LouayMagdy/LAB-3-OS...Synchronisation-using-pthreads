#include <pthread.h>
#include "caltrain.h"
#include "stdio.h"


void station_init(struct station *station){
    pthread_mutex_init(&station->inTheStation, NULL);
    pthread_cond_init(&station->trainArrived, NULL);
    pthread_cond_init(&station->trainCanLeave, NULL);
    station->availableSeatsNo = 0;
    station->waitingPassengersNo = 0;
    station->departedPassengersNo = 0;
}

void station_load_train(struct station *station, int count){
    pthread_mutex_lock(&station->inTheStation);
    station->availableSeatsNo = count;
    station->departedPassengersNo = 0;
    if(station->availableSeatsNo != 0 && station->waitingPassengersNo != 0) {
        pthread_cond_broadcast(&station->trainArrived);
        pthread_cond_wait(&station->trainCanLeave, &station->inTheStation);
    }
//    printf("train is leaving .. waiting Passengers : %d .. available seats: %d\n",
//           station->waitingPassengersNo, station->availableSeatsNo);
    (station->availableSeatsNo) = 0;
    pthread_mutex_unlock(&station->inTheStation);
}

void station_wait_for_train(struct station *station){
    pthread_mutex_lock(&station->inTheStation);
    (station->waitingPassengersNo)++;
//    printf("passenger : %d\n", station->waitingPassengersNo);
    while(station->availableSeatsNo == 0 || station->waitingPassengersNo == 0){
        pthread_cond_wait(&station->trainArrived, &station->inTheStation);
    }
    (station->availableSeatsNo)--;
    (station-> waitingPassengersNo)--;
    (station->departedPassengersNo)++;
//    printf("no. of available seats: %d\n", station->availableSeatsNo);
    pthread_mutex_unlock(&station->inTheStation);
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->inTheStation);
    if((station->departedPassengersNo) != 0 )
        (station->departedPassengersNo)--;
    if((station->departedPassengersNo) == 0 &&
    ((station->availableSeatsNo) == 0 || (station->waitingPassengersNo) == 0))
        pthread_cond_signal(&station->trainCanLeave);
    pthread_mutex_unlock(&station->inTheStation);
}
