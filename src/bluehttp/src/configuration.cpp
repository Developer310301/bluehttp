#include "bluehttp/configuration.h"

namespace bh{

    void Configuration::LoadConfig(std::string path){

        fs::path conf_path = path;

        if(!fs::exists(conf_path)){
            
            try{
                fs::create_directories(conf_path.root_path());
                std::ofstream file(path.c_str());
                file << "";
                file.close();
            }catch(std::exception ex){
                BH_LOG_CRITICAL("Cannot create configuration: {}", ex.what());
                exit(1);
            }
        }

        std::ifstream file(path);

        if(!file.is_open()){
            BH_LOG_CRITICAL("Cannot read configuration file at {}", path);
            exit(1);
        }

        try{
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            this->_config = ryml::parse_in_place(c4::to_substr(content));
        }catch(std::exception ex){
            BH_LOG_CRITICAL("Cannot parse configuration: {}", ex.what());
            exit(1);
        }

    }

    std::string Configuration::GetListenAddress(){
        std::string addr;
        this->_config["server"]["address"] >> addr;
        return addr;
    }

    int Configuration::GetServerPort(){
        int port;
        this->_config["server"]["port"] >> port;
        return port;
    }

    std::string Configuration::GetBlueprintsPath(){
        std::string bp;
        this->_config["server"]["blueprints"]["path"] >> bp;
        return bp;
    }

    bool Configuration::UseBlueprintsWhitelist(){
        bool wh;
        this->_config["server"]["blueprints"]["whitelist"]["enable"] >> wh;
        return wh;
    }

}