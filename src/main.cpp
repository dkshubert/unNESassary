#include "application.h"

int main()
{
    // TODO : populate config file from command line processing/config file.
    unnes::ApplicationConfig config;
    unnes::Application application { config };

    application.run();

    return 0;
}
