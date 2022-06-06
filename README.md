SeeX - Simple Image Viewer
==========================

SeeX is a simple image viewer primary written for macOS. Key features:

* iterates over images files in the same folder (as it should be!)
* supports a wide range of commonly used image formats (see notes below)
* looks good on modern Retina (HighDPI) displays
* supports macOS dark theme
* compatible with Apple Silicon (i.e. M1) Macs

Why
---

The default image viewer in macOS is too inconvenient, the most problem is that it doesn't iterate over files. Also, it is very hard to find (especially free or at least very cheap) something small and usable, the best option was [Xee³](https://theunarchiver.com/xee) this app was inspirited by, but I didn't like something in it and decided to write my own.

About supported image formats
-----------------------------

This app is written in Qt, and it initially supports anything supported by Qt itself, but custom plugins can be also implemented. Unfortunately, Qt seems to have issues with some SVG images, so do not be surprised when some of them look incorrectly.
