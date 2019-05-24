# openApp
## C++ 17 Framework to make great 2D and 3D cross-platform application

openApp is designed in pure camelCase notation, without any external dependency (except used renderer's library).
This way, you can bring it to any C++ 17 compatible project.

openApp features a renderer interface for 2D and 3D draw.
Currently supported renderers are :
  - Irrlicht (2D and 3D with openGL / DirectX / Software renderer)
  
 ## Design language '*.oA'
 openApp has its own design language, it is an oriented object language which uses class inheritance and properties.
 Every base class comes from C++, which can then be dynamically inherited, customized and instancied.
 openApp also support data binding, relative expressions and event-functions declaration.
 
 This is a simple HelloWorld example :

```javascript
/* MyApp.oA */
Window {
    id: myWnd
    title: "My Application"
    resizable: true

    Text {
        id: myText
        text: "Hello world !"
        relativePos: 0.5, 0.5 // Will be always centered in parent
        relativeSize: 0.5, 0.5 // Will always take 50% of parent's size
    }

    Button {
        text: "Click me"
        x: 0 // Brute x
        y: parent.height - height // Parent relative y
        width: 200 // Brute width
        height: 100 // Brute height

        on released { // will be called every time the button is released
            myText.text = "openApp is easy to use !"
        }
    }
}
```

## Why openApp ?
openApp was created with the aim of developping application focusing on the C++ backend without having to hard code the frontend.
Its langugage being dependency-free and interpreted in C++ at runtime makes it very confortable to develop with.

This library was highly inspired from Qt Quick Controls framework and its QML language (https://www.qt.io/).
Thanks to Qt for their amazing work !
