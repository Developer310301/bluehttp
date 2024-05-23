#include "bluehttp/blueprint_loader.h"

namespace bh{

    bool BlueprintLoader::IsBlueprintAllowed(std::string blueprint_name){
        if(!this->_whitelist_enabled)
            return true;
        
        auto it = std::find(this->_allowed_blueprints.begin(), this->_allowed_blueprints.end(), blueprint_name);

        if(it!=this->_allowed_blueprints.end())
            return true;
        else
            return false;

    }

    void BlueprintLoader::LoadFiles(){

        fs::path dirPath = this->_blueprint_folder;

        if(!fs::exists(dirPath))
            fs::create_directories(dirPath);
        
        for(const auto& entry : fs::directory_iterator(dirPath)){
            if(entry.is_regular_file() && ALLOWED_EXTENSION == entry.path().extension()){

                std::string bp_path = entry.path().c_str();

                void* handler = dlopen(bp_path.c_str(), RTLD_NOW);

                if(!handler){
                    std::cerr << "Cannot open library: " << dlerror() << "\n";
                    continue;
                }

                sdk::ExportBlueprints fnc = reinterpret_cast<sdk::ExportBlueprints>(dlsym(handler,EXPORT_BLUEPRINT_FNC));

                if(!fnc){
                    std::cerr << dlerror() << std::endl;
                    
                    continue;
                }

                this->_handlers.emplace_back(std::make_pair(handler, fnc));

            }
        }

    }

    void BlueprintLoader::LoadBlueprints(){

        for(auto& bp_handler : this->_handlers){
            
            sdk::BlueprintsSet blueprints = bp_handler.second();

            for(std::string& bp : blueprints){
                if(this->IsBlueprintAllowed(bp)){
                    sdk::HTTPBlueprint* bp_obj = reinterpret_cast<sdk::HTTPBlueprint*>(dlsym(bp_handler.first, bp.c_str()));
                    if(!bp_obj){
                        std::cerr << dlerror() << std::endl;
                        continue;
                    }
                    this->_blueprints_instances.emplace_back(bp_obj);
                }
            }

        }

    }

}