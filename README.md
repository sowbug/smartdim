SmartDim
===

A timed dimmer for the Ikea JANSJÖ lamp. Using pulse-width modulation, it starts the light at full brightness, waits 30 minutes, then dims gradually to full darkness over 5 minutes. In theory it's good for a kid who wakes up when the parent comes back in to shut off the reading light.


Parts List
===

* One [Ikea JANSJÖ clip lamp](http://www.ikea.com/us/en/catalog/products/30237256/#/20315674). The one I got was item 801.696.36 and it was marked down to $12.99. If it has a 2-pin DIN speaker connector for the power adapter, and the power is 4 volts at 0.75 amps (3 watts). Be careful and check this. I've seen other lamps in the JANSJÖ series that run on 7 volts, and that voltage will kill this circuit.
* A way to manufacture PCBs. You will, of course, use [OSH Park](https://oshpark.com/).
* Any old N-channel MOSFET in SOT-223 package that can handle a couple of amps. I used the [NDT3055L](https://www.jameco.com/webapp/wcs/stores/servlet/Product_10001_10001_874875_-1), which says it can dissipate 3 watts. I'd have preferred something with more margin for error, but this was available at Jameco will-call.
* An ATTiny85-20SU, which is the SOIC-8 package. Depending on how lazy you are, you can pick a smaller version of this series and figure out how to scrunch down the firmware size.
* A 6-pin AVR ISP.
* Either a [ProtoProg](http://protofusion.org/wordpress/2013/05/open-hardware-pogo-pin-programmer/) connector or an SOIC-8 clip to program the t85. Yeah, I probably could have fit a standard 6-pin header on this board. Sorry about that.
* An 0805 1uF capacitor.
* The standard [Dangerous Prototypes octagon-shaped SMD button](http://dangerousprototypes.com/docs/Partlist#Buttons_and_switches) (ALPS SKQGADE010). I usually use the [TD-85XU](http://www.dx.com/p/td-85xu-mini-tact-switches-50-piece-pack-122514#.VmRq-H4rKV4) because you can acquire a lifetime supply for $10, but I wanted something that was easier to find in the dark, and I happened to have some left over from another project. Looking back (to a few hours ago when this project started), I probably should have picked something a little less premium and with even more travel ([take your pick](http://www.dx.com/s/tact+switch)).
* Depending on whether you want to cut the lamp wires, a male and female pair of 2-pin DIN speaker connectors. You can find these on eBay.
