# CMake entry point
cmake_minimum_required(VERSION 3.0)
project(Moteur_de_Jeu)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)


if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif ()
if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()
if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()


# Compile external dependencies
add_subdirectory(external)

#On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP
#[[

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)
]]


if (WIN32)
    set(ASSIMP_DIR assimp_windows) #TODO
elseif (APPLE)
    set(ASSIMP_DIR assimp_ios) #TODO
else ()
    set(ASSIMP_DIR assimp_linux)
endif ()


include_directories(
        external/glfw-3.1.2/include/
        external/glm-0.9.7.1/
        external/glew-1.13.0/include/
        #external/${ASSIMP_DIR}/include/
        .
)
link_directories(
        external/glfw-3.1.2/src/Release/
        external/glew-1.13.0/lib/
        #external/${ASSIMP_DIR}/lib/
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130
        #assimp
        )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

add_executable(Project
        Demo/testScene.cpp
        common/Shaders/shader.cpp common/Shaders/shader.hpp
        common/DataLoaders/Mesh/objloader.cpp common/DataLoaders/Mesh/objloader.hpp
        common/vboindexer.cpp common/vboindexer.hpp
        common/DataLoaders/Image/stb_image.h
        common/Material/material.hpp
        common/Texture/texture.cpp common/Texture/texture.hpp
        common/Mesh/mesh.cpp common/Mesh/mesh.hpp
        common/Material/User_Materials/UNLIT/Unlit.h
        common/Material/Custom/custom.cpp common/Material/Custom/custom.hpp
        common/Material/User_Materials/HeightMap/heightmap.cpp common/Material/User_Materials/HeightMap/heightmap.hpp
        common/Material/Static/static.hpp common/Material/Static/static.cpp
        common/Components/component.hpp

        common/Components/drawableComponent.hpp common/Components/component.cpp
        common/Object/object.hpp common/Object/object.cpp
        common/Components/MeshRenderer/meshRenderer.hpp common/Components/MeshRenderer/meshRenderer.cpp
        common/Object/MeshObject/meshObject.cpp common/Object/MeshObject/meshObject.hpp
        common/Scene/Scene.cpp common/Scene/Scene.hpp
        common/Game/Game.cpp common/Game/Game.hpp
        "common/Components/Character controller/characterController.cpp" "common/Components/Character controller/characterController.hpp"
        common/Components/physicsComponent.cpp  common/Components/physicsComponent.hpp
        common/Object/Camera/camera.cpp common/Object/Camera/camera.hpp
        common/Utilities/Transformation/rotation_utils.cpp common/Utilities/Transformation/rotation_utils.hpp
        common/Utilities/stdUtilities.cpp common/Utilities/stdUtilities.hpp
        common/InputController.cpp common/InputController.hpp

        common/Components/ColliderComponent/Collider.cpp common/Components/ColliderComponent/Collider.hpp common/Components/ColliderComponent/PlaneCollider/PlaneCollider.cpp common/Components/ColliderComponent/PlaneCollider/PlaneCollider.hpp common/Components/ColliderComponent/SphereCollider/SphereCollider.cpp common/Components/ColliderComponent/SphereCollider/SphereCollider.hpp common/Components/ColliderComponent/SphereCollider/SphereCollider.hpp common/Utilities/DistanceBetween/DistanceBetween.cpp common/Utilities/DistanceBetween/DistanceBetween.hpp Demo/ControllableCamera.cpp common/Components/Gravity/Gravity.cpp common/Components/Gravity/Gravity.hpp Demo/myCharacterController.cpp Demo/myCharacterController.hpp common/Components/drawableComponent.cpp)
target_link_libraries(Project
        ${ALL_LIBS}

        )



#copy data to build folder
add_custom_command(
        TARGET Project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
        COMMENT "Copying data" VERBATIM
)


# Xcode and Visual working directories
set_target_properties(Project PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(Project WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*")
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$")





#copy executable to source folder
if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
    add_custom_command(
            TARGET Project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Project${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}"
    )
elseif (${CMAKE_GENERATOR} MATCHES "Xcode")

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")

