Kinnect with UCEngine
=====================

Instructions for a quick start
------------------------------

1. Install dependencies:
   * [OpenNI](https://github.com/OpenNI/OpenNI)
   * [Sensor](https://github.com/boilerbots/Sensor)
   * [NITE](http://www.openni.org/downloadfiles/openni-compliant-middleware-binaries/34-stable)

2. Compile the UCE-Gestures:

       git clone <...> && cd kinect.uce
       make
       ./bin/UCE-Gestures

3. Create the vhost:

       echo "127.0.0.1 nono.localhost" >> /etc/hosts
       ln -s ~/dev/kinect.uce/config/nginx /etc/nginx/sites-available/nono.localhost
       ln -s /etc/nginx/sites-available/nono.localhost /etc/nginx/sites-enabled/
       /etc/init.d/nginx restart

4. Enjoy:

       firefox http://nono.localhost/

