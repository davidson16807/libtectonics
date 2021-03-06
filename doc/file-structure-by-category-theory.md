Every file in this project only considers either a single data structure or a homset between them, and every folder considers only a single namespace that corresponds to a single mathematical category. A category diagram is linked to in the README.md of the folder for a category. 

The only deliberate exception to the rule is where the homset maps to a primitive data type, or where there is a compelling reason to privitize the attributes of a class. In either case, the homset is then represented as methods within the object itself. 

I've found the approach offers numerous advantages, which I will enumerate.

* Dependencies can be easily reasoned with. A file for a type only depends on the types that define its structure. A file for a homset only depends upon the the types that it maps to or from. The only exception I've found is with standard libraries or libraries that should probably count as such (e.g. vector math libraries). 
* Build times are generally quicker since dependencies for a file can be more cleanly defined.
* Functionality can be quickly navigated to. 
* Namespaces boundaries are well defined mathematically. 
* File boundaries are well defined mathematically. 
* If a change is made to an interface, the footprint of that change can be easily predicted, and the file overview for the commit is easy to interpret. 
* Combined with localizing unit tests, it's easy to build up tests incrementally, one homset at a time. Test coverage can be easily reasoned with. When combined with `-Wunused-*` compiler flags, you can guarantee that if a test file for a component has been written, it has at least been covered to some extent. You can then easily see at a glance from a file navigator which functionality has been covered by unit tests, and how far along the project is. Functionality that is not properly tested can be simply avoided when writing `#include`s and the compilation will still be trusted to work. 
* Beautiful category diagrams can be trivially constructed with online editors and saved in nonproprietary plaintext formats, and can be linked to in the README.md to give a visual understanding of the folder structure and project architecture at high level. I personally recommend [tikzcd-editor](https://tikzcd.yichuanshen.de/) for being both easy to use and servicable. It uses the [tikzcd](http://ctan.math.washington.edu/tex-archive/graphics/pgf/contrib/tikz-cd/tikz-cd-doc.pdf) file format.

In the future I would like to develop a vs code plugin that integrates the tikzcd-editor, modifying it so that types and homsets are color coded based on whether they compile or pass unit tests, and modifying it so that clicking on types and homsets will open up their underlying source code in an adjacent pane. Time will tell if I'm able to get to this. 