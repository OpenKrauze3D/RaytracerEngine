workspace "Raytracer"
    architecture "x64"
    configurations { "Debug", "Release" }

targetdir "build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includedirs {
    -- Thirdparty
    "./thirdparty/include/",
    "./thirdparty/include/glm/"
}

libdirs {
    -- "./thirdparty/lib/"
}

-- Build configurations
filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "NDEBUG"
    optimize "On"

project "Engine"
    location "Engine"
    kind "ConsoleApp"
    language "C++"

    files { 
        "./Engine/**.h",
        "./Engine/**.hpp",
        "./Engine/**.c",
        "./Engine/**.cpp"
    }

    includedirs {
        -- Project source code
        "./Engine/",
    }


-- Windows system
    filter "system:windows"
        system "windows"
        cppdialect "C++17"
        systemversion "latest"
        -- flags { "MultiProcessorCompile" }

-- Linux system
    filter "system:linux"
        system "linux"
        cppdialect "gnu++17"
        -- buildoptions { "-fopenmp" }
        -- links { "omp", "glfw", "GL", "m", "X11", "pthread", "Xi", "Xrandr", "dl" }

