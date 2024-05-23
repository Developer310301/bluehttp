#include "bluehttp/blueprint_loader.h"

using namespace httplib;
using namespace bh;

int main(){

    Server srv;
    BlueprintLoader bp_l("./blueprints", false);

    bp_l.LoadFiles();
    bp_l.LoadBlueprints();
    bp_l.RegisterRoutes(&srv);

    srv.listen("127.0.0.1", 8080);

    return 0;
}