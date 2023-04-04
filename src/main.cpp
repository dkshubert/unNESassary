#include "nes.h"
#include "stdoutlogger.h"
#include "time_utils.h"
#include "tv.h"

int main() {
    unnes::StdOutLogger logger;
    unnes::NES nes(logger);
    unnes::TV tv(logger);

    while (tv.isOn()) {
        const double time{unnes::getTime()};
        nes.run(time);
        tv.run(time);
    }

    return 0;
}
