PathologicalVideoLoad
=====================
This is an openFrameworks app (built out of the VideoPlayerExample that comes with OF) for mac that has been built to illustrate an issue I have run into dealing with ofVideoPlayer in OpenFrameworks 0.8.0.  

What this app should do is continuously load new videos into a ofVideoPlayer on random intervals - What actually happens is the ofVideoPlayer loads new videos for a while and then after some period of time or when some unknown condition is met the app hangs on a mutex (in QTVisualContextSetImageAvailableCallback) when QTKit tries to flush out the old video data.

There seems to be some correlation between how often the refresh is made and how likely the app will hang.  The less frequent the call to load a new video the more likely the call is to make the app hang, or, put another way, the more time between video refreshes the fewer times the video is likely to load before it eventually hangs.

