#define RYML_SINGLE_HDR_DEFINE_NOW

#include "bluehttp/configuration.h"
#include "bluehttp/blueprint_loader.h"

using namespace httplib;
using namespace bh;

int main(){

    Configuration config;
    Logger logger;
    Server srv;

    BH_LOG_INFO("Reading Configuation...");
    config.LoadConfig();

    BH_LOG_INFO("Initializing server...");

    srv.set_logger([](const Request& req, const Response& res) {
        BH_LOG_INFO("[{}:{}]({} {})\t{}", req.remote_addr, req.remote_port, req.method, res.status, req.path);
    });

    BlueprintLoader bp_l(config.GetBlueprintsPath(), config.UseBlueprintsWhitelist());

    BH_LOG_INFO("Loading plugins...");
    bp_l.LoadFiles();
    BH_LOG_INFO("Plugins loaded!");
    BH_LOG_INFO("Loading blueprints...");
    bp_l.LoadBlueprints();
    BH_LOG_INFO("Blueprints loaded!");
    BH_LOG_INFO("Registring routes...");
    bp_l.RegisterRoutes(&srv);


    BH_LOG_INFO("Starting server on {}:{}", config.GetListenAddress(), config.GetServerPort());

    

    srv.listen(config.GetListenAddress(), config.GetServerPort());

    return 0;
}