What is GTK
-----------

Let's start with a quotation from www.gtk.org:

GTK+, or the GIMP Toolkit, is a multi-platform toolkit for creating
graphical user interfaces. Offering a complete set of widgets, GTK+
is suitable for projects ranging from small one-off tools to complete
application suites.


GTK Version 2 vs. Version 3
---------------------------

When starting the development of sarturis the acutal version of GTK
was an early 2.x. During the ongoing progress now there is version 3.y
which is not binary compatible to the 2.x series.

This kind of hard cut is strongly supported by sarturis-gtk. Due to 
the wrapper characteristics sarturis-gtk supports both versions by
source code. When configuring the build there is a preference for
the 3.y series, but one can also build sarturis-gtk against GTK 2.x.

For users there should be no difference as the proper GTK binaries
should come together with sarturis-gtk or are installed via package
managers correctly. The binaries of GTK 2.x and 3.y can be installed
together on one system.

Module developers can request the GTK major version number with a call
to sarturis::gtk::GtkBase::GtkVersion().
