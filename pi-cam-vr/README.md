# Sprint 2: Raspberry Pi Cam VR

## Note

Most of this sprint was done by following [this tutorial](https://www.sitepoint.com/filtering-reality-with-javascript-google-cardboard/) by *Patrick Catanzariti*.

## Explanation
Other than this `README`, the code referenced in this directory is stored on the Raspberry Pi 4 (with a Pi Cam attached) running an Apache webserver. For more information on the RaspPi server setup, go [here](https://elinux.org/RPi-Cam-Web-Interface). The working directory is set up as a symlink into the `var/www/vrview` directory.

On boot, the Raspberry Pi itself was set up to send its current IP address as a phone notification, as the school server could not have a static IP set up on it. This was done using [IFTTT](https://ifttt.com/). When the webhook receives a web request with a JSON payload, then the notification containing the IP address (the JSON payload) appears on the phone. Of course, the phone has the app installed and is logged into the same account.

This is then used to get the link to the server created by the Raspberry Pi. So, with an example `{IP ADDRESS}`, one would open `https://{IP ADDRESS}/vrview` to get the view ready for cardboard. The user can open this link on their phone, orient it horizontally, and tap the screen to go to fullscreen in order to view it in Google Cardboard.

