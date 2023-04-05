#include "application.h"

int main()
{
    // TODO : populate config file from command line processing/config file.
    unnes::ApplicationConfig config;
    unnes::Application application { config };

    return application.run() ? 0 : -1;
}
