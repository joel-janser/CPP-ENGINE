# CPP-ENGINE
C++-Engine is an easy-to-understand rendering engine, which is not yet finished. This is published by Joel for education.

# Rending model

The rending model is based on boxes, which are encapsulated in a tree model. The distance model is a renderer, which uses most of the time to calculate the distance between boxes the MAX-function. 

When rendering designs, the MAX-function ensures that only intended distances by the designer will appear in the final screen design. This saves much CSS-code, because to define distances between visible boxes is more natural than the CSS Box Model where the definition of distances with margin and padding is not possible.

The combination of the C++-Engine with the standardised software production would allow C++ developers to create their own visual 2D or 3D-components based on C++ with an easy-to-understand Rendering Engine, optimized for 2D rendering.

# Why not use HTML and the CSS-Box Model? 

In the CSS Box Model the margin and padding used define numbers which define distances to points with no meaning. When two objects have natural distances, the nature would use this natural distance to a point with meaning and not an artificial point. When a graphic looks good (e.g. an icon) with a certain area around itself, it means that this area must be free from other boxes with this number and not this number + a maybe unkown number. And the uncertainty is because the designers do not know while define the component, what other components are used or introduced. 

When a box has a natural distance around itself where no other boxes are placed, it means normally the distance to a visually remarkable point. Designers measure like this and wish that the given numbers are not added, because adding numbers (margin + padding, or margin+margin, or any combination) will result in more measurable distances and according to design theory, a harmonious design contains more equal mesuarable distances. The design theory is also very good visible in the Google Material Design, where distances of e.g. 2px, 4px, 8px, 16px, 32px, 64px are used to create a harmonious user interface. When implementing this in HTML, the using of margin and padding with these numbers would result in all combinations of measurable distances like (16px + 2px = 18px) which are unintended distances. 

The CSS Box Model rendering needs too much adjustsments for defining margin and padding to fix the issue with the natural distance. Much of todays CSS code is just fixing this issue and much of the design problems on websites base on this issue. 

Of course HTML has a complex ecosystem and Google Chrome around 50 million lines of code. This is a complex environment which has too much features for fail-safe systems and industry machines. The idea is to keep the lines of code for the software under 10'000 lines, with an easy to implement interface which can render text, colored boxes, images, etc. (for example to call SDL/OpenGL/Vulkan/Software-Renderer API's to use the graphics-card for rendering or to keep the library easy to check).

The idea is to create a complete ecosystem for building low-energy-use applications, for products which do not have much RAM, hard-drive space, processor power, etc. Like colored paper ink display (3-color, grayscale, more colors), which do not need a fast processor, because the refresh rate of the screen is much lower than on other displays. This means that the time for painting a frame is around 1 second. 

There is unfortunately (not yet) a standard for 2D rendering in C++. 

To create user interfaces for industry machines, low-power-products, etc. normally requires programming skills. 
