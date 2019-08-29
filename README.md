# openApp

## What it is ?
openApp is a cross platform application framework which uses its own interpreted language.
It currently supports everything that supports SDL2: Windows, Mac, Android, iOS, and many more !

## Is it standard ?
openApp is a framework but unlike other one like Qt, it builds every core class on top of C++ standard library.
This means that the oA::String is can be passed as a std::string, and so for every other standard classes like oA::Vector, oA::Thread, oA::Mutex, oA::Unique...
The oA:: version of standard library only adds utils functions that still aren't implemented in C++ 17 (ex: oA::String::startsWith).

## Dependencies ?
openApp only need C++ 17 and a rendererer in order to work, its interpreted language is written in standard C++.
Currently, the only supported renderer is SDL2.
That said, to run an openApp application you will need to install the following libraries :
 - SDL2
 - SDL2_image
 - SDL2_ttf

## openApp's interpreted language
openApp uses a custom object-oriented language that is fully integrated with C++.
This means it is really easy to interact with it in the C++ code and it doesn't require much effort to create complex and interactive views.
The interpreter takes care of building expressions's dependencies using Signal / Slot paradigm: when a variable change, every expression which depends on it is re-computed.
### A quick example
```qml
/*
  Main.oA - A simple window with label and button
*/

import MyCustomWidgets // Import a directory in order to uses '*.oA' in it

Window {
  id: mainWindow
  title: "openApp"
  
  MyCustomWidgets {
    id: label
    text: mainWindow.title + " - Hello World" // Bind 'text' to result of expression
    width: 200
    height: 100
    relativePos: 0.5, 0.5 // Center label in its parent
  }
  
  Button {
    // Update the label, but uses a static variable to do it only once
    function updateLabel: {
      static var updated = false
      if (updated)
        return
      label.text.append("!!!")
      updated = true
    }
    
    width: label.width // Bind 'width' to 'label.width'
    height: label.height // Bind 'height' to 'label.heigh'
    text: "Click me"

    on released: updateLabel() // Call 'updateLabel' function whenever the button is released
  }
}
```
```c++
// Main.cpp

#include <openApp/SDLApp.hpp>

int main(void)
{
  SDLApp app;
  
  app.parseFile("Main.oA");
  app.run();
  return 0;
}
```

## What openApp is good at ?
openApp versatile. It's a good framework to build small and large cross-platform applications.
Thanks to his very low amount of dependencies, it is very easy to install and integrate it in existing projects.
His interpreted language makes it easier to combine C++ speed and a powerful high level / runtime UI design.
Unless you're coding your whole backend logic in openApp's interpreted language, it's going to run fast.

## Why openApp ?
openApp is greatly inspired by Qt Quick Controls framework.
In fact, you can install a qml linter extension and it'll work with openApp's language.
So, you may wonder: why another framework ?
Qt Quick has a very huge amount of abstaction, layers, dependencies and (too many) possibilities thanks to its Javascript binding.
After using it for a while I got very disapointed by how, in large projects (generally with dynamic views), JavaScript backend isn't stable enough (mostly conflicts with garbage collector).
That's why I decided to create a new interpreter optimized for that usage, with the same syntax of QML combined to JavaScript, but in pure and standard C++ !
