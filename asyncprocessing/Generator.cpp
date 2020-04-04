#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Generator.h"

using namespace std;

void Generator::init(int interval, int reps) {
    Generator::reps = reps;
    Generator::interval = interval;
    int count = 0;
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(interval));
    t.async_wait(boost::bind(Generator::send, boost::asio::placeholders::error, &t, &count));
    io.run();
}

void Generator::send(const boost::system::error_code& ec, boost::asio::steady_timer* timer, int* count) {
    cout << "tick " << *count << endl;
    ++(*count);

    if (*count < Generator::reps)
    {
        timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(Generator::interval));
        timer->async_wait(boost::bind(Generator::send, boost::asio::placeholders::error, timer, count));
    }
}

int Generator::reps = 1;
int Generator::interval = 1;