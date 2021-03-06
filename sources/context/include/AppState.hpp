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

#include <OgreFrameListener.h>
#include <OgreRenderTargetListener.h>

#include "InputManager.hpp"
#include "InputListener.hpp"

namespace Context {
class CameraMan;
}

namespace Context {

class AppState : public Ogre::RenderTargetListener, public Ogre::FrameListener, public Context::InputListener {
 public:
  AppState();
  virtual ~AppState();

  virtual void SetupGlobals();
  virtual void ResetGlobals();
  virtual void Setup() = 0;
  virtual void Reset() = 0;
  virtual void Next() = 0;

  void preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt) override {};

  void postRenderTargetUpdate(const Ogre::RenderTargetEvent &evt) override {};

  void SetOgreRoot(Ogre::Root *ogre_root);
  void SetOgreScene(Ogre::SceneManager *ogre_scene);
  void SetCameraMan(const std::shared_ptr<CameraMan> &camera_man);
  void SetOgreCamera(Ogre::Camera *ogre_camera);
  void SetOgreViewport(Ogre::Viewport *ogre_viewport);

 public:
  Ogre::Root *ogre_root = nullptr;
  Ogre::SceneManager *ogre_scene_manager_ = nullptr;
  std::shared_ptr<CameraMan> camera_man_;
  Ogre::Camera *ogre_camera_ = nullptr;
  Ogre::Viewport *ogre_viewport_ = nullptr;
  bool registered_ = false;
};

}
