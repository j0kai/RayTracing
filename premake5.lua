workspace "RayTracer"
    architecture "x64"
    configurations 
    { 
      "Debug", 
      "Release", 
    }

    startproject "RayTracer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RayTracer"
    location "RayTracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
      "%{prj.name}/src"
    }

    defines
      {
        "_CRT_SECURE_NO_WARNINGS"
      }
    
    filter "system:windows"
      systemversion "latest"
      
      
    filter "configurations:Debug"
      defines { "RT_DEBUG" }
      runtime "Debug"
      symbols "on"

    filter "configurations:Release"
      defines { "RT_RELEASE" }
      runtime "Release"
      optimize "on"