# CPP-ENGINE
C++-Engine is an easy-to-understand rendering engine, which is not yet finished. This is published by Joel for study and education.

# Rending model

The rending model is based on boxes, which are encapsulated in a tree model. The distance model is a renderer, which uses most of the time to calculate the distance between boxes the MAX-function. 

When rendering designs, the MAX-function ensures that only intended distances by the designer will appear in the final screen design. This saves much CSS-code, because to define distances between visible boxes is more natural than the CSS Box Model where the definition of distances with margin and padding is not possible.

The combination of the C++-Engine with the standardised software production would allow C++ developers to create their own visual 2D or 3D-components based on C++ with an easy-to-understand Rendering Engine, optimized for 2D rendering.

# Why not use HTML and the CSS-Box Model? 

In the CSS Box Model the margin and padding used define numbers which define distances to points with no meaning. When two objects have natural distances, the nature would use this natural distance to a point with meaning and not an artificial point. When a graphic looks good (e.g. an icon) with a certain area around itself, it means that this area must be free from other boxes with this number and not this number + a maybe unkown number. And the uncertainty is because the designers do not know while define the component, what other components are used or introduced. 

When a box has a natural distance around itself where no other boxes are placed, it means normally the distance to a visually remarkable point. Designers measure like this and wish that the given numbers are not added, because adding numbers (margin + padding, or margin+margin, or any combination) will result in more measurable distances and according to design theory, a harmonious design contains more equal mesuarable distances. The design theory is also very good visible in the Google Material Design, where distances of e.g. 2px, 4px, 8px, 16px, 32px, 64px are used to create a harmonious user interface. When implementing this in HTML, the using of margin and padding with these numbers would result in all combinations of measurable distances like (16px + 2px = 18px) which are unintended distances. 

The CSS Box Model rendering needs too much adjustsments for defining margin and padding to fix the issue with the natural distance. Much of todays CSS code is just fixing this issue and much of the design problems on websites base on this issue. 

Of course HTML has a complex ecosystem and Google Chrome around 50 million lines of code. This is a complex environment which has too much features for fail-safe systems and industry machines. 

Please read about the "Collapsible Margins" recommandation and imagine that the margins and paddings would both and always collapse. And the default also for text rendering is bad, because it has no visual meaning. 

HTML is not designed to be integrated into a designer like Sketch, because the rulers for margin-padding would mostly point to nowhere. To synchronize distances it is much easier to have fewer distances.  

# Idea

The idea is to keep the lines of code for the software under 10'000 lines, with an easy to implement interface which can render text, colored boxes, images, etc. (for example to call SDL/OpenGL/Vulkan/Software-Renderer API's to use the graphics-card for rendering or to keep the library easy to check).

The idea is to create a complete ecosystem for building low-energy-use applications, for products which do not have much RAM, hard-drive space, processor power, etc. Like colored paper ink display (3-color, grayscale, more colors), which do not need a fast processor, because the refresh rate of the screen is much lower than on other displays. This means that the time for painting a frame is around 1 second. 

There is unfortunately (not yet) a standard for 2D rendering in C++, so the renderer will use SDL to render the graphics.

To create user interfaces for industry machines, low-power-products, etc. normally requires programming skills and much time. The designer application, like the Resource Manger, has the environment to build JSON-files with a visual editor. 

When you can convert a spoken sentence into a design like "The distance from the title to the following element is minimum 5px". You find out, that with the CSS Box Model it is hard to build natural language sentences. 

"The flash icon has minimum a 10 pixel distance (to the title)" 

.flash-icon{
  "distance-top": 5px
  "relative-to": "#messagebox"
}

The application model is already a tree structure (e. g. Angular) and to build a separate design tree structure is not necessary, but the design model is able to attach content visually to other components instead of the place them in the tree structure with JavaScript-DOM-manipulation.

The idea is to use this for the following: Message-boxes, navigation, error messages, ...

# CSS

The best CSS is always if you can convert the code into natural language sentences which make sense.

e. g. ;

<documentation>
  <title>C++</title>
  <subtitle>A C++-example</subtitle>
  <text>Just a test</text>
  <image></image>
</documentation>

.documentation {
  padding: 10px; // All documentations have a padding of 10 pixel to the "invisible outer area of the title, subtitles, texts and other elements"
  border: 1px solid green; // 
}

.documentation .title {
  color: red; // "All titles within documentations have the color red"
  margin: 10px; // "All titles within documentations have a margin of 10 Pixel"
}

.documentation .subtitle {
  margin: 10px;
}

.documentation .text {
  margin: 10px;
}

The words "margin" and "padding" are not a natural language constructs, because the definition has no meaning to technical people, non-technical people and not even to designers. 

It would be much easier to say "the documentation tag is a red line around title, subtitle and text with a distance of 10 pixel to the elements within." 

When CSS is not convertable into natural language which is understandable by designers it is not a design language which results in good designs. Because the designers know the important numbers and measures / lines to measure the correctness of the layout and these numbers are not found very often in CSS. 

The usage of SCSS leads to CSS which is too heavy and unreadable, because the programmers write too much selectors. 
