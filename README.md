Kinect with UCEngine
====================

What: detect gestures with a Kinect and send them as events to UCEngine  
When: CodeWeek 5  
Where: Caours, France  
Who: Bruno Michel, af83  


Instructions for a quick start
------------------------------

1. Install dependencies:
   * [UCEngine](http://www.ucengine.org/)
   * [OpenNI](https://github.com/OpenNI/OpenNI)
   * [Sensor](https://github.com/boilerbots/Sensor)
   * [NITE](http://www.openni.org/downloadfiles/openni-compliant-middleware-binaries/34-stable)

2. Compile the UCE-Gestures:

       git clone <...> && cd kinect.uce
       make
       ./bin/UCE-Gestures | ./bin/std2uce nono.localhost 80

3. Create the vhost:

       echo "127.0.0.1 nono.localhost" >> /etc/hosts
       ln -s ~/dev/kinect.uce/config/nginx /etc/nginx/sites-available/nono.localhost
       ln -s /etc/nginx/sites-available/nono.localhost /etc/nginx/sites-enabled/
       /etc/init.d/nginx restart

4. Enjoy:

       firefox http://nono.localhost/


Events
------

List of events in UCEngine:

* kinect.wave
* kinect.nocircle (end of a circle move, with the number of circles made in param)
* kinect.swipeup
* kinect.swipedown
* kinect.swipeleft
* kinect.swiperight


Credits
-------

The code is licensed as MIT. See the MIT-LICENSE for the full license.

Copyright (c) 2011 Bruno Michel <bruno.michel@af83.com>
