#!/usr/bin/env python
# coding=utf-8
import gtk.gdk
import gtk
import glib
class MyRect():
  def __init__(self, x = 0, y = 0, w = 0, h = 0):
    self.x = x
    self.y = y
    self.w = w
    self.h = h
  def __init__(self, x, y):
    self.x = min(int(x.x), int(y.x))
    self.y = min(int(x.y), int(y.y))
    self.w = abs(int(y.x - x.x))
    self.h = abs(int(y.y - x.y))
class MyPair():
  def __init__(self, x = 0, y = 0):
    self.x = x
    self.y = y
class MyPoint(MyPair):
  def __init__(self, x = 0, y = 0):
    MyPair.__init__(self, x, y)
class MySize(MyPair):
  def __init__(self, w = 0, h = 0):
    MyPair.__init__(self, x, y)
class MyCapture():
  (event_enter, event_leave) = (0, 1)
  def __init__(self):
    pass
  def capture(self):
    pass
  def handleEvent(self, event):
    if event == event_enter:
      enterSnap()
    elif event == event_leave:
      leaveSnap()
  def enterSnap(self):
    pass
  def leaveSnap(self):
    pass
  def snap(self, window = None, rect = None, name = None):
    pass
class MyCaptureGtk(MyCapture):
  def __init__(self):
    MyCapture.__init__(self)
    self.window = gtk.Window()
    self.window.set_default_size(1,1)
    self.window.connect("button-press-event", self.button_press_cb)
    self.first = None
    self.second = None
    self.window.show()
    #self.window.set_events(gtk.gdk.BUTTON_PRESS_MASK)
  def getWindow(self):
    return self.window
  def button_press_cb(self, widget, event):
    #print "type is %d" % event.type
    if event.type == gtk.gdk.BUTTON_PRESS:
      if event.button == 1: #left button
        print ("(%d, %d), (%d, %d), button is %d" % (event.x_root, event.y_root, event.x, event.y, event.button))
        if not self.first:
          self.first = MyPoint(event.x_root, event.y_root)
        else:
          self.second = MyPoint(event.x_root, event.y_root)
          self.snap(None, MyRect(self.first, self.second))
          self.first = None
      elif event.button == 3: #right button
        self.uncapture()
      else:
        pass
  def uncapture(self):
    if self.first:
      print("cancel")
      self.first = None
    else:
      print("exit now")
      gtk.gdk.pointer_ungrab()
      gtk.mainquit()
  def capture(self, time):
    cursor = gtk.gdk.Cursor(gtk.gdk.display_get_default(), gtk.gdk.CROSSHAIR)
    ret = gtk.gdk.pointer_grab(self.window.window, True,
          gtk.gdk.BUTTON_PRESS_MASK,
          None, cursor, time)
    if ret == gtk.gdk.GRAB_SUCCESS:
      print ("left button start, end, right button cancel/exit")
    else:
      print ("failed to capture %d, (viewable %d),(frozen %d), (already %d)" \
       % (ret, gtk.gdk.GRAB_NOT_VIEWABLE, gtk.gdk.GRAB_FROZEN, gtk.gdk.GRAB_ALREADY_GRABBED))
  def snap(self, window = None, rect = None, name = None):
    w = window
    if not window:
      #w = gtk.gdk.get_default_root_window()
      d = gtk.gdk.display_get_default()
      w = d.get_default_screen().get_root_window()
    r = rect
    if not r:
      sz = w.get_size()
      r = MyRect(0, 0, sz[0], sz[1])
    print ("The size of the window is (%d, %d, %d, %d)" % (r.x, r.y, r.w, r.h))
    n = name
    if not n:
      n = "screenshot.png"
    buf = gtk.gdk.Pixbuf(gtk.gdk.COLORSPACE_RGB,False,8, r.w, r.h)
    buf = buf.get_from_drawable(w,w.get_colormap(), r.x, r.y, 0, 0, r.w, r.h)
    if (buf != None):
      buf.save(n, "png")
      print ("Screenshot saved to %s." % n)
    else:
      print ("Unable to get the screenshot.")
def timeout(data):
  #print "timeout"
  data.capture()
if __name__ == '__main__':
  cap = MyCaptureGtk()
  w = cap.getWindow()
  w.show()
  glib.timeout_add_seconds(1, timeout, cap)
#cap.snap()
  gtk.main()
