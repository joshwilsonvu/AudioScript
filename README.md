#AudioScript

*A scriptable, real-time audio processing playground.*

![./audioscript512.png)](./audioscript512.png)

Mission Statement: To provide software that makes real-time audio
processing intuitive, simple, and responsive for all users, while
enabling users familiar with C++ to create and integrate their
own audio processing code.

AudioScript is an application in two parts; one general module that
all users may benefit from, and one module that allows C++ users to
extend the library capabilities of the application.
The main module is a graphical window into which users drag
AudioScript blocks from a library. These blocks can be connected
together with arrows, much like a block diagram. When the permanent
input and output blocks have been connected, audio can be run through
the processing that the intermediate blocks represent and output to
the speakers or to a file.

The secondary portion is a simple IDE in which developers subclass the
given AudioScript C++ class, implementing methods that process incoming
samples through code. The AudioScript application will build user code into
a block and plug it into its own code, enabling user-defined blocks to
be used seamlessly with the standard effects.
