// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-
#ifndef __application_hh
#define __application_hh

#include "eventdispatcher.hh"
#include "display.hh"
#include "renderstyle.hh"

namespace otk {

class AppWidget;

class Application : public EventDispatcher {

public:

  Application(int argc, char **argv);
  virtual ~Application();

  virtual void run(void);
  // more bummy cool functionality

  void setDockable(bool dockable) { _dockable = dockable; }
  inline bool isDockable(void) const { return _dockable; }

  inline RenderStyle *getStyle(void) const { return _style; }
  // more accessors

private:
  void loadStyle(void);

  Display _display;
  RenderStyle *_style;
  bool _dockable;

  int _appwidget_count;

  friend class AppWidget;
};

}

#endif
