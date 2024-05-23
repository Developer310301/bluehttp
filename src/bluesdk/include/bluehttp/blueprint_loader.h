#ifndef BLUESDK_BLUEPRINT_LOADER_H
#define BLUESDK_BLUEPRINT_LOADER_H

#include "bluehttp/libs.h"
#include "bluehttp/sdk/sdk.h"


#ifdef PLATFORM_WINDOWS
    #define DEFAULT_BLUEPRINT_FOLDER "C:\\'Program Files'\\BlueHTTP\\blueprints"
    #define ALLOWED_EXTENSION ".dll"
#else
    #define DEFAULT_BLUEPRINT_FOLDER "/usr/local/share/bluehttp/blueprints"
    #define ALLOWED_EXTENSION ".so"
#endif

namespace bh{

    namespace fs = std::filesystem;

    BLUEHTTP_API class BlueprintLoader{

        private:
            std::string _blueprint_folder;
            bool _whitelist_enabled;
            std::vector<std::string> _allowed_blueprints = {};
            std::vector<std::pair<void*,sdk::ExportBlueprints>> _handlers = {};
            std::vector<sdk::HTTPBlueprint*> _blueprints_instances = {};
        
        private:
            bool IsBlueprintAllowed(std::string blueprint_name);

        public:
            inline BlueprintLoader(std::string blueprint_folder = DEFAULT_BLUEPRINT_FOLDER, bool whitelist = true, std::vector<std::string> allowed = {}) 
                : _blueprint_folder(blueprint_folder), _whitelist_enabled(whitelist), _allowed_blueprints(allowed) {}

            void LoadFiles();
            void LoadBlueprints();

            template<typename S>
            inline void RegisterRoutes(S* server){

                for(sdk::HTTPBlueprint* bp : this->_blueprints_instances){

                    for(const sdk::HTTPRoute& r : bp->GetRoutes()){

                        for(const sdk::HTTPMethods m : r.allowed_methods){
                            switch (m)
                            {
                            case sdk::HTTPMethods::GET:
                                server->Get(r.path, r.fnc);
                                break;
                            case sdk::HTTPMethods::POST:
                                server->Post(r.path, r.fnc);
                                break;
                            case sdk::HTTPMethods::PUT:
                                server->Put(r.path, r.fnc);
                                break;
                            case sdk::HTTPMethods::PATCH:
                                server->Patch(r.path, r.fnc);
                                break;
                            case sdk::HTTPMethods::DELETE:
                                server->Delete(r.path, r.fnc);
                                break;
                            case sdk::HTTPMethods::OPTIONS:
                                server->Options(r.path, r.fnc);
                                break;
                            }
                        }

                    }

                }

            }

            inline void RegisterRoutes(httplib::Server* server){this->RegisterRoutes<httplib::Server>(server);};
            inline void RegisterRoutes(httplib::SSLServer* server){this->RegisterRoutes<httplib::SSLServer>(server);};

    };

}

#endif //BLUESDK_BLUEPRINT_LOADER_H