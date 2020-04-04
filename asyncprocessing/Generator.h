/*
 *  Generate letters
 *
 *  Todo
 *  generate on a cadence
 *  send to listeners
 *
 */

#ifndef ASYNCPROCESSING_GENERATOR_H
#define ASYNCPROCESSING_GENERATOR_H

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Generator {
public:
    static int reps;
    static int interval;
    static void init(int interval, int repititions);
    static void send(const boost::system::error_code&, boost::asio::steady_timer* timer, int* count);
};


#endif //ASYNCPROCESSING_GENERATOR_H
