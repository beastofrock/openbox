// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-

%module ob_screen

%{
#include "config.h"
#include "screen.hh"
#include "otk/display.hh"
#include "otk/property.hh"
%}

%include "ob_client.i"
%include "otk_rect.i"
%include "otk_ustring.i"
%include "otk_size.i"
%include "std_vector.i"

%typemap(python,out) const otk::Property::StringVect& {
  otk::Property::StringVect *v = $1;
  unsigned int s = v->size();
  PyObject *l = PyList_New(s);

  otk::Property::StringVect::const_iterator it = v->begin(), end = v->end();
  for (unsigned int i = 0; i < s; ++i, ++it) {
    PyObject *pdata = PyString_FromString(it->c_str());
    PyList_SET_ITEM(l, i, pdata);
  }
  $result = l;
}

%typemap(python,out) std::list<ob::Client*> {
  unsigned int s = $1.size();
  PyObject *l = PyList_New(s);

  std::list<ob::Client*>::const_iterator it = $1.begin(), end = $1.end();
  for (unsigned int i = 0; i < s; ++i, ++it) {
    PyObject *pdata = SWIG_NewPointerObj((void*)*it,SWIGTYPE_p_ob__Client,0);
    PyList_SET_ITEM(l, i, pdata);
  }
  $result = l;
}

%typemap(python,out) const std::vector<otk::Rect>& {
  std::vector<otk::Rect> *v = $1;
  unsigned int s = v->size();
  PyObject *l = PyList_New(s);

  std::vector<otk::Rect>::const_iterator it = v->begin(), end = v->end();
  for (unsigned int i = 0; i < s; ++i, ++it) {
    PyObject *pdata = SWIG_NewPointerObj((void*)&(*it),SWIGTYPE_p_otk__Rect,0);
    PyList_SET_ITEM(l, i, pdata);
  }
  $result = l;
}

namespace ob {

%extend Screen {
  void showDesktop(bool show) {
    Window root = RootWindow(**otk::display, self->number());
    send_client_msg(root, otk::Property::atoms.net_showing_desktop,
                    root, show);
  }

  void changeDesktop(unsigned int desktop) {
    Window root = RootWindow(**otk::display, self->number());
    send_client_msg(root, otk::Property::atoms.net_current_desktop,
                    root, desktop);
  }

  const otk::Size& size() {
    return otk::display->screenInfo(self->number())->size();
  }

  const std::vector<otk::Rect> &xineramaAreas() {
    return otk::display->screenInfo(self->number())->xineramaAreas();
  }

  Window rootWindow() {
    return otk::display->screenInfo(self->number())->rootWindow();
  }
}

%immutable Screen::clients;

%ignore Screen::event_mask;
%ignore Screen::Screen(int);
%ignore Screen::~Screen();
%ignore Screen::focuswindow() const;
%ignore Screen::managed() const;
%rename(ignored_showDesktop) Screen::showDesktop(bool show);
%ignore Screen::ignored_showDesktop(bool show);
%ignore Screen::updateStruts();
%ignore Screen::manageExisting();
%ignore Screen::manageWindow(Window);
%ignore Screen::unmanageWindow(Client*);
%ignore Screen::raiseWindow(Client*);
%ignore Screen::lowerWindow(Client*);
%ignore Screen::installColormap(bool) const;
%ignore Screen::propertyHandler(const XPropertyEvent &);
%ignore Screen::clientMessageHandler(const XClientMessageEvent &);
%ignore Screen::mapRequestHandler(const XMapRequestEvent &);

}

%include "screen.hh"
