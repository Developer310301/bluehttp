workspace "Panim"
    architecture "x64"
    configurations { "Debug", "Release" }
    libdirs {"external/lib"}
    includedirs {"external/include"}

    OutputDir = "output/bin/%{cfg.architecture}/%{cfg.system}/%{cfg.buildcfg}"
    ObjDir = "output/obj/%{cfg.architecture}/%{cfg.system}/%{cfg.buildcfg}"

-------------------------------------------------
---- BLUEPRINTS PLUGINS SDK DEFINITIONS
-------------------------------------------------

project "bluesdk"
    kind "SharedLib"
    language "C++"
    cppdialect "c++20"
    buildoptions {"-fPIC"}
    targetdir ( OutputDir .. "/")
    objdir (ObjDir .. "/%{prj.name}")
    
    files { "src/bluesdk/include/**.h", "src/bluesdk/src/**.cpp" }

    includedirs { "src/bluesdk/include" }

    links { "ssl", "crypto", "spdlog" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        debugger "GDB"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-------------------------------------------------
-- SERVER EXECUTABLE
-------------------------------------------------

project "bluehttp"
    kind "ConsoleApp"
    language "C++"
    targetdir ( OutputDir .. "/")
    objdir (ObjDir .. "/%{prj.name}")
    
    files { "src/bluehttp/include/**.h", "src/bluehttp/src/**.cpp" }

    includedirs { "src/bluehttp/include", "src/bluesdk/include" }

    links { "bluesdk", "ssl", "crypto", "spdlog" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        debugger "GDB"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

------------------------------------------------------
----- PLUGINS
------------------------------------------------------

project "blueprint"
    kind "SharedLib"
    language "C++"
    buildoptions {"-fPIC"}
    targetdir ( OutputDir .. "/")
    objdir (ObjDir .. "/%{prj.name}")
    
    files { "src/blueprint/src/**.cpp" }

    includedirs { "src/bluesdk/include"}

    links { "bluesdk", "ssl", "crypto", "spdlog" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        debugger "GDB"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"