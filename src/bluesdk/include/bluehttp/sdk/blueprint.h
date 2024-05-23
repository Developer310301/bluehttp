#ifndef BLUESDK_BLUEPRINT_H
#define BLUESDK_BLUEPRINT_H

#include "bluehttp/libs.h"

#define EXPORT_BLUEPRINT_FNC "ExportBlueprints"

namespace bh::sdk{

    BLUEHTTP_API enum HTTPMethods{
        GET,
        HEAD,
        POST,
        PUT,
        PATCH,
        DELETE,
        OPTIONS
    };

    
    typedef std::vector<HTTPMethods> AllowedMethods;
    typedef std::function<httplib::Server&(const httplib::Request&, const httplib::Response&)> RouteFnc;

    BLUEHTTP_API struct HTTPRoute{
        std::string path;
        AllowedMethods allowed_methods;
        RouteFnc fnc;
    };

    BLUEHTTP_API class HTTPBlueprint{

        private:
            std::string _base_path;
            std::vector<HTTPRoute> _routes;

        public:
            inline HTTPBlueprint(std::string base_path = "") : _base_path(base_path){}
            
            template<typename... Args>
            void RegisterRoute(std::string path, AllowedMethods methods, RouteFnc fnc){
                this->_routes.emplace_back((HTTPRoute){path, methods, fnc});
            }

            inline const std::vector<HTTPRoute>& GetRoutes(){ return this->_routes; }

    };

    typedef std::vector<std::string> BlueprintsSet;
    typedef BlueprintsSet(*ExportBlueprints)();

}

#endif //BLUESDK_BLUEPRINT_H