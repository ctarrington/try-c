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
#include <boost/random.hpp>

class Generator {
private:
    static int reps;
    static int interval;
    static boost::random::mt19937 gen;
    static boost::random::uniform_int_distribution<> dist;
    static void send(const boost::system::error_code&, boost::asio::steady_timer* timer, int* count);

public:
    static void init(int interval, int repititions);
};


#endif //ASYNCPROCESSING_GENERATOR_H
