#ifndef BH_CONFIGURATION_H
#define BH_CONFIGURATION_H


#include "bluehttp/sdk/sdk.h"
#include "bluehttp/ryml.h"

#ifdef PLATFORM_WINDOWS
    #define DEFAULT_CONFIG_PATH "C:\\'Program Files'\\BlueHTTP\\config\\config.yaml"
#else
    #define DEFAULT_CONFIG_PATH "/usr/local/share/bluehttp/config/config.yaml"
#endif

namespace bh{

    namespace fs = std::filesystem;

    BLUEHTTP_API class Configuration{

        private:
            ryml::Tree _config;

        public:
            void LoadConfig(std::string path = DEFAULT_CONFIG_PATH);
            std::string GetListenAddress();
            int GetServerPort();
            std::string GetBlueprintsPath();
            bool UseBlueprintsWhitelist();

    };

}

#endif //BH_CONFIGURATION_H