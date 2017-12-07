# QImgurUploader
Qt objects for uploading image files to imgur.com. Requires Qt 5.9

## Usage
Register your application (see https://api.imgur.com) to get a client ID.

Include .pri file into the .pro file of your qt application
```
include(QImgurUploader/QImgurUploader.pri)
```
Include QImgurUploader and QImgurReply as needed
```
#include <QImgurUploader>
#include <QImgurReply>
```
Construct an QImgurUploader object (client ID required).
```
uploader = new QImgurUploader("XXXXXXXX");
```
Upload image files by calling QImgurUploader::upload. Once finished, the returned QImgurReply will parse the response.
