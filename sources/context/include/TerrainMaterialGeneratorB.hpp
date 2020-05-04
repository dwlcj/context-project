/*
MIT License

Copyright (c) 2020 Andrey Vasiliev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*//*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#pragma once

#include <Terrain/OgreTerrainPrerequisites.h>
#include <Terrain/OgreTerrainMaterialGenerator.h>

namespace Ogre {
class PSSMShadowCameraSetup;
};

using namespace Ogre;

namespace Context {
class ShaderHelper;
enum TechniqueType {
  HIGH_LOD,
  LOW_LOD,
  RENDER_COMPOSITE_MAP
};

class TerrainMaterialGeneratorB : public TerrainMaterialGenerator {
 public:
  TerrainMaterialGeneratorB();
  ~TerrainMaterialGeneratorB() override;

  class SM2Profile :
      public TerrainMaterialGenerator::Profile {
   public:
    SM2Profile(TerrainMaterialGenerator *parent,
               const String &name,
               const String &desc);
    ~SM2Profile() override;
    MaterialPtr generate(const Terrain *terrain) override;
    MaterialPtr generateForCompositeMap(const Terrain *terrain) override;
    uint8 getMaxLayers(const Terrain *terrain) const override;
    void updateParams(const MaterialPtr &mat, const Terrain *terrain) override;
    void updateParamsForCompositeMap(const MaterialPtr &mat, const Terrain *terrain) override;
    void requestOptions(Terrain *terrain) override;
    [[nodiscard]] bool isVertexCompressionSupported() const override;

/** Whether to support normal mapping per layer in the shader (default true).
*/
    [[nodiscard]] bool isLayerNormalMappingEnabled() const { return mLayerNormalMappingEnabled; }
/** Whether to support normal mapping per layer in the shader (default true).
*/
    void setLayerNormalMappingEnabled(bool enabled);
/** Whether to support parallax mapping per layer in the shader (default true).
*/
    [[nodiscard]] bool isLayerParallaxMappingEnabled() const { return mLayerParallaxMappingEnabled; }
/** Whether to support parallax mapping per layer in the shader (default true).
*/
    void setLayerParallaxMappingEnabled(bool enabled);
/** Whether to support specular mapping per layer in the shader (default true).
*/
    [[nodiscard]] bool isLayerSpecularMappingEnabled() const { return mLayerSpecularMappingEnabled; }
/** Whether to support specular mapping per layer in the shader (default true).
*/
    void setLayerSpecularMappingEnabled(bool enabled);
/** Whether to support a global colour map over the terrain in the shader,
    if it's present (default true).
*/
    [[nodiscard]] bool isGlobalColourMapEnabled() const { return mGlobalColourMapEnabled; }
/** Whether to support a global colour map over the terrain in the shader,
if it's present (default true).
*/
    void setGlobalColourMapEnabled(bool enabled);
/** Whether to support a light map over the terrain in the shader,
if it's present (default true).
*/
    [[nodiscard]] bool isLightmapEnabled() const { return mLightmapEnabled; }
/** Whether to support a light map over the terrain in the shader,
if it's present (default true).
*/
    void setLightmapEnabled(bool enabled) override;
/** Whether to use the composite map to provide a lower LOD technique
    in the distance (default true).
*/
    [[nodiscard]] bool isCompositeMapEnabled() const { return mCompositeMapEnabled; }
/** Whether to use the composite map to provide a lower LOD technique
in the distance (default true).
*/
    void setCompositeMapEnabled(bool enabled);
/** Whether to support dynamic texture shadows received from other
    objects, on the terrain (default true).
*/
    [[nodiscard]] bool getReceiveDynamicShadowsEnabled() const { return mReceiveDynamicShadows; }
/** Whether to support dynamic texture shadows received from other
objects, on the terrain (default true).
*/
    void setReceiveDynamicShadowsEnabled(bool enabled);

/** Whether to use PSSM support dynamic texture shadows, and if so the
    settings to use (default 0).
*/
    void setReceiveDynamicShadowsPSSM(PSSMShadowCameraSetup *pssmSettings);
/** Whether to use PSSM support dynamic texture shadows, and if so the
settings to use (default 0).
*/
    [[nodiscard]] PSSMShadowCameraSetup *getReceiveDynamicShadowsPSSM() const { return mPSSM; }
/** Whether to use depth shadows (default false).
*/
    void setReceiveDynamicShadowsDepth(bool enabled);
/** Whether to use depth shadows (default false).
*/
    [[nodiscard]] bool getReceiveDynamicShadowsDepth() const { return mDepthShadows; }
/** Whether to use shadows on low LOD material rendering (when using composite map) (default false).
*/
    void setReceiveDynamicShadowsLowLod(bool enabled);
/** Whether to use shadows on low LOD material rendering (when using composite map) (default false).
*/
    [[nodiscard]] bool getReceiveDynamicShadowsLowLod() const { return mLowLodShadows; }

    bool isShadowingEnabled(TechniqueType tt, const Terrain *terrain) const;
   protected:
    typedef StringStream stringstream;

    void addTechnique(const MaterialPtr &mat, const Terrain *terrain, TechniqueType tt);

    ShaderHelper *mShaderGen;
    bool mLayerNormalMappingEnabled;
    bool mLayerParallaxMappingEnabled;
    bool mLayerSpecularMappingEnabled;
    bool mGlobalColourMapEnabled;
    bool mLightmapEnabled;
    bool mCompositeMapEnabled;
    bool mReceiveDynamicShadows;
    PSSMShadowCameraSetup *mPSSM;
    bool mDepthShadows;
    bool mLowLodShadows;
    bool terrain_fog_perpixel_ = true;
   public:
    bool IsTerrainFogPerpixel() const;
    void SetTerrainFogPerpixel(bool terrain_fog_perpixel);
  };
};

typedef TerrainMaterialGeneratorB::SM2Profile SM2Profile;

/// Interface definition for helper class to generate shaders
class ShaderHelper : public TerrainAlloc {
 public:
  explicit ShaderHelper(bool glsl) : mShadowSamplerStartHi(0), mShadowSamplerStartLo(0), mIsGLSL(glsl) {}
  virtual ~ShaderHelper() = default;
  bool isVertexCompressionSupported() { return !mIsGLSL; }
  virtual HighLevelGpuProgramPtr generateVertexProgram(const SM2Profile *prof,
                                                       const Terrain *terrain,
                                                       TechniqueType tt);
  virtual HighLevelGpuProgramPtr generateFragmentProgram(const SM2Profile *prof,
                                                         const Terrain *terrain,
                                                         TechniqueType tt);
  virtual void updateParams(const SM2Profile *prof,
                            const MaterialPtr &mat,
                            const Terrain *terrain,
                            bool compositeMap);
 protected:
  virtual String getVertexProgramName(const SM2Profile *prof, const Terrain *terrain, TechniqueType tt);
  virtual String getFragmentProgramName(const SM2Profile *prof, const Terrain *terrain, TechniqueType tt);
  virtual HighLevelGpuProgramPtr createVertexProgram(const SM2Profile *prof,
                                                     const Terrain *terrain,
                                                     TechniqueType tt) = 0;
  virtual HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile *prof,
                                                       const Terrain *terrain,
                                                       TechniqueType tt) = 0;
  virtual void generateVertexProgramSource(const SM2Profile *prof,
                                           const Terrain *terrain,
                                           TechniqueType tt,
                                           StringStream &outStream);
  virtual void generateFragmentProgramSource(const SM2Profile *prof,
                                             const Terrain *terrain,
                                             TechniqueType tt,
                                             StringStream &outStream);
  virtual void generateVpHeader(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream) = 0;
  virtual void generateFpHeader(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream) = 0;
  virtual void generateVpLayer(const SM2Profile *prof,
                               const Terrain *terrain,
                               TechniqueType tt,
                               uint layer,
                               StringStream &outStream) = 0;
  virtual void generateFpLayer(const SM2Profile *prof,
                               const Terrain *terrain,
                               TechniqueType tt,
                               uint layer,
                               StringStream &outStream) = 0;
  virtual void generateVpFooter(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream) = 0;
  virtual void generateFpFooter(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream) = 0;
  virtual void defaultVpParams(const SM2Profile *prof,
                               const Terrain *terrain,
                               TechniqueType tt,
                               const HighLevelGpuProgramPtr &prog);
  virtual void defaultFpParams(const SM2Profile *prof,
                               const Terrain *terrain,
                               TechniqueType tt,
                               const HighLevelGpuProgramPtr &prog);
  virtual void updateVpParams(const SM2Profile *prof,
                              const Terrain *terrain,
                              TechniqueType tt,
                              const GpuProgramParametersSharedPtr &params);
  virtual void updateFpParams(const SM2Profile *prof,
                              const Terrain *terrain,
                              TechniqueType tt,
                              const GpuProgramParametersSharedPtr &params);
  static String getChannel(uint idx);

  size_t mShadowSamplerStartHi;
  size_t mShadowSamplerStartLo;
  bool mIsGLSL;
  bool terrain_fog_perpixel_ = true;
 public:
  bool IsTerrainFogPerpixel() const;
  void SetTerrainFogPerpixel(bool terrain_fog_perpixel);
};

/// Utility class to help with generating shaders for Cg / HLSL.
struct ShaderHelperCg : public ShaderHelper {
  ShaderHelperCg();
 protected:
  bool mSM4Available;
  HighLevelGpuProgramPtr createVertexProgram(const SM2Profile *prof,
                                             const Terrain *terrain,
                                             TechniqueType tt) override;
  HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile *prof,
                                               const Terrain *terrain,
                                               TechniqueType tt) override;
  void generateVpHeader(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateFpHeader(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateVpLayer(const SM2Profile *prof,
                       const Terrain *terrain,
                       TechniqueType tt,
                       uint layer,
                       StringStream &outStream) override;
  void generateFpLayer(const SM2Profile *prof,
                       const Terrain *terrain,
                       TechniqueType tt,
                       uint layer,
                       StringStream &outStream) override;
  void generateVpFooter(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateFpFooter(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  uint generateVpDynamicShadowsParams(uint texCoordStart,
                                      const SM2Profile *prof,
                                      const Terrain *terrain,
                                      TechniqueType tt,
                                      StringStream &outStream);
  void generateVpDynamicShadows(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream);
  void generateFpDynamicShadowsHelpers(const SM2Profile *prof,
                                       const Terrain *terrain,
                                       TechniqueType tt,
                                       StringStream &outStream);
  void generateFpDynamicShadowsParams(uint *texCoord,
                                      uint *sampler,
                                      const SM2Profile *prof,
                                      const Terrain *terrain,
                                      TechniqueType tt,
                                      StringStream &outStream);
  void generateFpDynamicShadows(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream);
};

/// Utility class to help with generating shaders for GLSL.
struct ShaderHelperGLSL : public ShaderHelper {
  ShaderHelperGLSL();
 protected:
  bool mIsGLES;
  HighLevelGpuProgramPtr createVertexProgram(const SM2Profile *prof,
                                             const Terrain *terrain,
                                             TechniqueType tt) override;
  HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile *prof,
                                               const Terrain *terrain,
                                               TechniqueType tt) override;
  void generateVpHeader(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateFpHeader(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateVpLayer(const SM2Profile *prof,
                       const Terrain *terrain,
                       TechniqueType tt,
                       uint layer,
                       StringStream &outStream) override;
  void generateFpLayer(const SM2Profile *prof,
                       const Terrain *terrain,
                       TechniqueType tt,
                       uint layer,
                       StringStream &outStream) override;
  void generateVpFooter(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  void generateFpFooter(const SM2Profile *prof,
                        const Terrain *terrain,
                        TechniqueType tt,
                        StringStream &outStream) override;
  uint generateVpDynamicShadowsParams(uint texCoordStart,
                                      const SM2Profile *prof,
                                      const Terrain *terrain,
                                      TechniqueType tt,
                                      StringStream &outStream);
  void generateVpDynamicShadows(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream);
  void generateFpDynamicShadowsHelpers(const SM2Profile *prof,
                                       const Terrain *terrain,
                                       TechniqueType tt,
                                       StringStream &outStream);
  void generateFpDynamicShadowsParams(uint *texCoord,
                                      uint *sampler,
                                      const SM2Profile *prof,
                                      const Terrain *terrain,
                                      TechniqueType tt,
                                      StringStream &outStream);
  void generateFpDynamicShadows(const SM2Profile *prof,
                                const Terrain *terrain,
                                TechniqueType tt,
                                StringStream &outStream);
};

} //namespace Context
