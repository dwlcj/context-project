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

#pragma once

#include "ManagerCommon.hpp"

namespace Ogre {
class Material;
}

namespace Context {
class GBufferSchemeHandler;
class DepthSchemeHandler;
}

namespace Context {

class CompositorManager : public ManagerCommon {
 private:
  static CompositorManager CompositorManagerSingleton;

 public:
  static CompositorManager *GetSingletonPtr();
  static CompositorManager &GetSingleton();

 public:
  void Setup() final;
  void Reset() final;

 public:
  void preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt) final;
  void postRenderTargetUpdate(const Ogre::RenderTargetEvent &evt) final;

 private:
  void CreateMotionBlurCompositor();

 public:
  void SetCompositor(const std::string &compositor_);
  void SetPost(const std::string &post_);

 private:
  std::vector<std::string> compositor_names_;
  std::string current_compositor_;

  std::vector<std::string> post_names_;
  std::string current_post_;
  std::string current_modulate_scene_;

  std::unique_ptr<GBufferSchemeHandler> ssaog_buffer_scheme_handler_;
  std::unique_ptr<DepthSchemeHandler> depth_scheme_handler_;

  //SSAO
  bool graphics_shadows_enable_ = true;
  bool compositor_use_bloom_ = true;
  bool compositor_use_ssao_ = true;
  bool compositor_use_blur_ = true;
  bool compositor_use_hdr_ = true;
  bool compositor_use_moution_blur_ = false;
};

} //namespace Context
