# QtPlex

### About
QtPlex is a cross-platform media player, based on [Plex](https://www.plex.tv/) home server and the [Qt](https://www.qt.io/) framework. The main motivation behind QtPlex was to provide a stable, modern interface into Plex without sacrificing functionality. Most notably, existing solutions for Plex interfaces lack support for media playback keys. Additionally, available Plex interfaces on Linux machines are sorely lacking, both in features and support. With this in mind, QtPlex was created as an interface into the Plex web client. This allows for low-level control over things such as keyboard shortcuts, while taking advantage of the officially maintained web interface, all while being cross-platform ready.

### Prerequisites
* Accessible server running Plex. 
* QtCreator software.

### Getting Started
Currently, QtPlex is stable with core functionality, but still in development. I hope to have a packaged release shortly, but for now you must download QtCreator and run the project through the build button. Alternatively, you should be able to use qmake from the command line, via `qmake QtPlex.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug`. 

### Goals
* Icons for Linux and Windows
* Officially packaged distributable will be made.
* About page w/ link to repository and credits.
* Cross-platform testing needs to be done, possibly w/ Selenium.
* Adding support for Windows media key shortcuts.
* OS notifications re: song playback

------
### Acknowledgments
This project is dependent on Plex and Qt, and the hard-working developers there who build and maintain the core features that QtPlex relies on. Additionally, [QHotKey](https://github.com/Skycoder42/QHotkey) enabled the base framework for cross-platform keyboard hooks. 
