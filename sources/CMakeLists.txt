#MIT License
#
#Copyright (c) 2020 Andrey Vasiliev
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
#

cmake_minimum_required(VERSION 3.15.1)

find_package(OpenMP REQUIRED)
if (NOT ANDROID)
    find_package(OpenGL REQUIRED)
endif()

include(cotire)

project(context-lib)

set(CMAKE_MODULE_PATH
    "${CONTEXT_ROOT_DIR}/CMake"
    )

include(cotire)

set(OGGSOUND_HEADERS
    oggsound/include/LocklessQueue.h
    oggsound/include/OgreOggISound.h
    oggsound/include/OgreOggListener.h
    oggsound/include/OgreOggSoundCallback.h
    oggsound/include/OgreOggSoundFactory.h
    oggsound/include/OgreOggSound.h
    oggsound/include/OgreOggSoundManager.h
    oggsound/include/OgreOggSoundPrereqs.h
    oggsound/include/OgreOggSoundRecord.h
    oggsound/include/OgreOggStaticSound.h
    oggsound/include/OgreOggStaticWavSound.h
    oggsound/include/OgreOggStreamSound.h
    oggsound/include/OgreOggStreamWavSound.h
    )

set(PAGEDGEOMETRY_HEADERS
    pagedgeometry/include/BatchedGeometry.h
    pagedgeometry/include/BatchPage.h
    pagedgeometry/include/GrassLoader.h
    pagedgeometry/include/ImpostorPage.h
    pagedgeometry/include/PagedGeometry.h
    pagedgeometry/include/PagedGeometryConfig.h
    pagedgeometry/include/PropertyMaps.h
    pagedgeometry/include/RandomTable.h
    pagedgeometry/include/StaticBillboardSet.h
    pagedgeometry/include/TreeLoader2D.h
    pagedgeometry/include/TreeLoader3D.h
    pagedgeometry/include/WindBatchedGeometry.h
    pagedgeometry/include/WindBatchPage.h
    )

set(BTOGRE_HEADERS
    btogre/include/BtOgreExtras.h
    btogre/include/BtOgreGP.h
    btogre/include/BtOgrePG.h
    )

set(CONTEXT_HEADERS
    context/include/Application.hpp
    context/include/InputListener.hpp
    context/include/AppState.hpp
    context/include/AppStateManager.hpp
    context/include/CameraMan.hpp
    context/include/Exception.hpp
    context/include/Io.hpp
    context/include/pcheader.hpp
    context/include/ContextManager.hpp
    context/include/ShaderResolver.hpp
    context/include/DummyListener.hpp
    context/include/InputManager.hpp
    context/include/ConfigManager.hpp
    context/include/EventMapper.hpp
    context/include/DotSceneLoaderB.hpp
    context/include/StaticForestManager.hpp
    context/include/PagedForestManager.hpp
    context/include/SinbadCharacterController.hpp
    context/include/constants.hpp
    context/include/PhysicsManager.hpp
    context/include/BulletCommon.hpp
    context/include/OgreCommon.hpp
    context/include/DummyAppState.hpp
    context/include/SoundManager.hpp
    context/include/ManagerCommon.hpp
    context/include/SDL2Common.hpp
    context/include/Context.hpp
    context/include/EntityCommon.hpp
    context/include/AgentCommon.hpp
    context/include/CompositorManager.hpp
    context/include/ContextConfigStructures.hpp
    context/include/NoCopy.hpp
    context/include/ImguiOverlay.hpp
    context/include/TerrainMaterialGeneratorB.hpp
    context/include/TerrainMaterialGeneratorC.hpp
    context/include/PropertyMaps.hpp
    context/include/CeguiOverlayManager.hpp
    context/include/PSSMShadowCameraSetupB.hpp
    context/include/PagedGeometryCommon.hpp
    context/include/CubeMapCamera.hpp
    context/include/ReflectionCamera.hpp
    context/include/ParticlesManager.hpp
    )

set(HEADER_FILES_CONTEXT_LIB
    ${BTOGRE_HEADERS}
    ${OGGSOUND_HEADERS}
    ${PAGEDGEOMETRY_HEADERS}
    ${CONTEXT_HEADERS}
    )

set(BTOGRE_SOURCES
    btogre/src/BtOgre.cpp
    )

set(OGGSOUND_SOURCES
    oggsound/src/OgreOggISound.cpp
    oggsound/src/OgreOggListener.cpp
    oggsound/src/OgreOggSoundFactory.cpp
    oggsound/src/OgreOggSoundManager.cpp
    oggsound/src/OgreOggSoundRecord.cpp
    oggsound/src/OgreOggStaticSound.cpp
    oggsound/src/OgreOggStaticWavSound.cpp
    oggsound/src/OgreOggStreamSound.cpp
    oggsound/src/OgreOggStreamWavSound.cpp
    )

set(PAGEDGEOMETRY_SOURCES
    pagedgeometry/src/BatchedGeometry.cpp
    pagedgeometry/src/BatchPage.cpp
    pagedgeometry/src/GrassLoader.cpp
    pagedgeometry/src/ImpostorPage.cpp
    pagedgeometry/src/PagedGeometry.cpp
    pagedgeometry/src/PropertyMaps.cpp
    pagedgeometry/src/StaticBillboardSet.cpp
    pagedgeometry/src/TreeLoader2D.cpp
    pagedgeometry/src/TreeLoader3D.cpp
    pagedgeometry/src/WindBatchedGeometry.cpp
    pagedgeometry/src/WindBatchPage.cpp
    )

set(CONTEXT_SOURCES
    context/src/Application.cpp
    context/src/AppState.cpp
    context/src/AppStateManager.cpp
    context/src/CameraMan.cpp
    context/src/Exception.cpp
    context/src/Io.cpp
    context/src/ContextManager.cpp
    context/src/ShaderResolver.cpp
    context/src/DummyListener.cpp
    context/src/InputManager.cpp
    context/src/ConfigManager.cpp
    context/src/EventMapper.cpp
    context/src/DotSceneLoaderB.cpp
    context/src/SinbadCharacterController.cpp
    context/src/PhysicsManager.cpp
    context/src/StaticForestManager.cpp
    context/src/PagedForestManager.cpp
    context/src/DummyAppState.cpp
    context/src/SoundManager.cpp
    context/src/ManagerCommon.cpp
    context/src/InputListener.cpp
    context/src/pcheader.cpp
    context/src/EntityCommon.cpp
    context/src/AgentCommon.cpp
    context/src/CompositorManager.cpp
    context/src/ImguiOverlay.cpp
    context/src/TerrainMaterialGeneratorB.cpp
    context/src/TerrainMaterialGeneratorC.cpp
    context/src/PropertyMaps.cpp
    context/src/CeguiOverlayManager.cpp
    context/src/PSSMShadowCameraSetupB.cpp
    context/src/CubeMapCamera.cpp
    context/src/ReflectionCamera.cpp
    context/src/ParticlesManager.cpp
    )

set(SOURCE_FILES_CONTEXT_LIB
    ${BTOGRE_SOURCES}
    ${OGGSOUND_SOURCES}
    ${PAGEDGEOMETRY_SOURCES}
    ${CONTEXT_SOURCES}
    )

include_directories(context-lib ${CONTEXT_DEPENDENCY_INCLUDE_DIRS})

add_library(context-lib-static STATIC ${SOURCE_FILES_CONTEXT_LIB} ${HEADER_FILES_CONTEXT_LIB})
add_library(context-lib-dynamic SHARED EXCLUDE_FROM_ALL ${SOURCE_FILES_CONTEXT_LIB} ${HEADER_FILES_CONTEXT_LIB})

target_link_directories(context-lib-dynamic PUBLIC ${CONTEXT_EXTERNAL_LIB_DIR} ${CONTEXT_EXTERNAL_LIB_DIR}/OGRE)
target_link_libraries(context-lib-dynamic PUBLIC ${CONTEXT_STATIC_DEPENDENCY_LIBS})

set_target_properties(context-lib-static PROPERTIES OUTPUT_NAME "context-static")
set_target_properties(context-lib-dynamic PROPERTIES OUTPUT_NAME "context")
if (WIN32)
    set_target_properties(context-lib-dynamic PROPERTIES PREFIX "")
endif ()

set(CMAKE_CXX_FLAGS ${CONTEXT_CXX_FLAGS})
set(CMAKE_C_FLAGS ${CONTEXT_C_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${CONTEXT_EXE_LINKER_FLAGS})
set(CMAKE_STATIC_LINKER_FLAGS ${CONTEXT_STATIC_LINKER_FLAGS})
set(CMAKE_SHARED_LINKER_FLAGS ${CONTEXT_SHARED_LINKER_FLAGS})

if (NOT MSVC AND NOT ANDROID)
    set_target_properties(context-lib-dynamic PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "context/include/pcheader.hpp")
    set_target_properties(context-lib-static PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "context/include/pcheader.hpp")
    #    cotire(context-lib-dynamic)
    cotire(context-lib-static)
endif ()

# install(TARGETS context-lib-dynamic
#         CONFIGURATIONS Release
#         RUNTIME DESTINATION bin
#         LIBRARY DESTINATION bin
#         )