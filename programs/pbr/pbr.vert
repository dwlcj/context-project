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
*/

// The MIT License
// Copyright (c) 2016-2017 Mohamad Moneimne and Contributors

#ifndef GL_ES
#define VERSION 120
#version VERSION
#define USE_TEX_LOD
#if VERSION != 120
#define attribute in
#define texture1D texture
#define texture2D texture
#define texture2DProj textureProj
#define shadow2DProj textureProj
#define texture3D texture
#define textureCube texture
#define texture2DLod textureLod
#define textureCubeLod textureLod
#else
#define in varying
#define out varying
#endif
#ifdef USE_TEX_LOD
#extension GL_ARB_shader_texture_lod : require
#endif
#else
#version 100
#extension GL_OES_standard_derivatives : enable
#extension GL_EXT_shader_texture_lod: enable
#define textureCubeLod textureLodEXT
precision highp float;
#define in varying
#define out varying
#endif

attribute vec4 position;
uniform mat4 uMVPMatrix;

#ifdef SHADOWCASTER_ALPHA
attribute vec2 uv0;
out vec2 vUV;
#endif

#ifndef SHADOWCASTER
uniform mat4 uModelMatrix;

#ifdef HAS_UV
attribute vec2 uv0;
#endif

out vec4 vUV;

#ifdef HAS_NORMALS
attribute vec4 normal;
#endif
#ifdef HAS_TANGENTS
attribute vec4 tangent;
#endif

uniform float uLightCount;

#define MAX_LIGHTS 5

#ifdef SHADOWRECEIVER
uniform float uLightCastsShadowsArray[MAX_LIGHTS];
uniform mat4 uTexWorldViewProjMatrixArray[3];
out vec4 lightSpacePosArray[MAX_LIGHTS * 3];
#endif

#ifdef FADE
uniform float fadeRange;
#endif
uniform float uTime;

#ifdef TERRAIN
uniform sampler2D HeighMap;
uniform vec4 TerrainBox; //-x+x-z+z
uniform vec4 TerrainBox2; //-y+y
#endif

out vec3 vPosition;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
out mat3 vTBN;
#else
out vec3 vNormal;
#endif
#endif
#ifdef REFLECTION
out vec4 projectionCoord;
#endif

#endif //SHADOWCASTER

void main()
{
  vec4 mypos = position;

//  vec2 uv;
//  uv.x = (mypos.x - TerrainBox.x) / (TerrainBox.y - TerrainBox.x);
//  uv.y = (mypos.z - TerrainBox.z) / (TerrainBox.w - TerrainBox.z);
//  float heigh = texture2D(HeighMap, uv).r * TerrainBox2.y - TerrainBox2.x;
//  mypos.y += heigh;

#ifdef FOREST
  float radiusCoeff = 0.25;
  float heightCoeff = 0.25;
  float factorX = 1;
  float factorY = 1;
  mypos.y += sin(uTime + mypos.z + mypos.y + mypos.x) * radiusCoeff * radiusCoeff * factorY;
  mypos.x += sin(uTime + mypos.z ) * heightCoeff * heightCoeff * factorX;
#endif

#ifndef SHADOWCASTER
  vec4 pos = uModelMatrix * position;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
  vec3 normalW = normalize(vec3(uModelMatrix * vec4(normal.xyz, 0.0)));
  vec3 tangentW = normalize(vec3(uModelMatrix * vec4(tangent.xyz, 0.0)));
  vec3 bitangentW = cross(normalW, tangentW) * tangent.w;
  vTBN = mat3(tangentW, bitangentW, normalW);
#else // HAS_TANGENTS != 1
  vNormal = normalize(vec3(uModelMatrix * vec4(normal.xyz, 0.0)));
#endif
#endif

#ifdef HAS_UV
  vUV.xy = uv0;
#else
  vUV.xy = vec2(0.0);
#endif

  for (int i = 0; i < int(uLightCount);  i += 3) {
#ifdef SHADOWRECEIVER
  // Calculate the position of vertex in light space
  if (uLightCastsShadowsArray[i] == 1.0) {
    lightSpacePosArray[i] = uTexWorldViewProjMatrixArray[i] * mypos;
    lightSpacePosArray[i + 1] = uTexWorldViewProjMatrixArray[i + 1] * mypos;
    lightSpacePosArray[i + 2] = uTexWorldViewProjMatrixArray[i + 2] * mypos;
  }
#endif
  }

  gl_Position = uMVPMatrix * mypos;
  vUV.z = gl_Position.z;
  vPosition = vec3(pos.xyz) / pos.w;

#ifdef REFLECTION
  mat4 scalemat = mat4(0.5, 0.0, 0.0, 0.0,
                        0.0, 0.5, 0.0, 0.0,
                        0.0, 0.0, 0.5, 0.0,
                        0.5, 0.5, 0.5, 1.0);
  projectionCoord = scalemat * gl_Position;
#endif

#else //SHADOWCASTER

#ifdef SHADOWCASTER_ALPHA
  vUV.xy = uv0;
#endif

  gl_Position = uMVPMatrix * mypos;
#endif //SHADOWCASTER

#ifdef FADE
  vUV.w = 1.0 - clamp(gl_Position.z * fadeRange, 0.0, 1.0);
#endif
}