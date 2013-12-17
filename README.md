PathologicalVideoLoad
=====================
This is an openFrameworks app for mac that has been built to illustrate an issue I have run into dealing with ofVideoPlayer in openframeworks 0.8.0.  

What this app should do is continuously load new videos into a ofVideoPlayer - What actually happens is the ofVideoPlayer loads new video for a while and then after some period of time or when some unknown condition is met the app hangs when QTKit tries to flush out the old video data.

