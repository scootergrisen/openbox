// -*- mode: C++; indent-tabs-mode: nil; -*-
// window.hh for Epistophy - a key handler for NETWM/EWMH window managers.
// Copyright (c) 2002 - 2002 Ben Jansens <ben at orodu.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef   __window_hh
#define   __window_hh

extern "C" {
#include <X11/Xlib.h>
}

#include <list>
#include <string>

class epist;
class screen;
class XWindow;
class XAtom;

typedef std::list<XWindow *> WindowList;

class XWindow {
private:
  epist *_epist;
  screen *_screen;
  XAtom *_xatom;
  Window _window;
  
  unsigned int _desktop;
  std::string _title;
  std::string _app_name;
  std::string _app_class;

  // states
  bool _shaded;
  bool _iconic;
  bool _max_vert;
  bool _max_horz;

  bool _unmapped;

  void updateState();
  void updateDesktop();
  void updateTitle();
  void updateClass();

public:
  XWindow(epist *epist, screen *screen, Window window);
  virtual ~XWindow();

  inline Window window() const { return _window; }
  
  inline unsigned int desktop() const { return _desktop; }
  inline const std::string &title() const { return _title; }
  inline const std::string &appName() const { return _app_name; }
  inline const std::string &appClass() const { return _app_name; }
  
  inline bool shaded() const { return _shaded; }
  inline bool iconic() const { return _iconic; }
  inline bool maxVert() const { return _max_vert; }
  inline bool maxHorz() const { return _max_horz; }

  void processEvent(const XEvent &e);

  void shade(const bool sh) const;
  void close() const;
  void raise() const;
  void lower() const;
  void iconify() const;
  void focus() const;

  bool operator == (const XWindow &w) const { return w._window == _window; }
  bool operator == (const Window &w) const { return w == _window; }
};

#endif // __window_hh
