# Tidy Images
Easy sort and organize your image collection
<br>
<br>

[![Paypal](https://img.shields.io/badge/donate-PayPal-blue.svg?style=flat-square&logo=paypal)](https://paypal.me/SimonSchwarzkopf)
[![Bitcoin](https://img.shields.io/badge/donate-Bitcoin-orange.svg?style=flat-square&logo=bitcoin)](https://github.com/Simon-12/TestImage/blob/develop/app/data/bitcoin-code.png)
<br>
<br>


## Features

![Gallery](https://github.com/Simon-12/common/blob/main/tidy-images/01.gif)
<br>

Image and videos can be viewed in different modes: as Gallery, Image-only-viewer and Video-only-viewer.  
Files can be moved into separate folders and can be added to a database for later browsing.  
Files can also be copied to a specific folder or be deleted.  
All actions can be undo or redo.

<details>
<summary>...</summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/02.gif" width="65%"/>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/03.gif" width="65%"/>
</details>  
<br>

Files can be labeled with text information or marked as favorite. Favorite images get copied into a separate folder.  
The database can be browsed for already sorted files (currently support SQLite).  
Folders can be completely added or removed from the database.

<details>
<summary>...</summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/04.gif" width="65%"/>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/05.gif" width="65%"/>
</details>  
<br>


To find similar images, images can be compared side by side or with an algorithm.  
(for algorithm the OpenCV plugin is needed)

<details>
<summary>...</summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/06.gif" width="65%"/> 
</details>  
<br>

## Plugins

The application can be extended with plugins. The idea is to reduce dependencies, so the application can also be built without external libs.
<br>
<br>

Plugin |      | Description | Link
:----: | :--: | :----------- | :----
**Exiv2** | <img src="https://github.com/Simon-12/TestImage/blob/develop/plugins/exiv2/plugin/icon.png" width="50%"/> | Image metadata library and tools. Is needed for read image metadata (date) and read and write labels to metadata comment section. | [github/exiv2](https://github.com/Exiv2/exiv2)
**OpenCV** | <img src="https://github.com/Simon-12/TestImage/blob/develop/plugins/opencv/plugin/icon.png" width="40%"/> | Open Source Computer Vision Library. Is needed for read and rotate images, read in single video frames and the image compare algorithm. | [github/opencv](https://github.com/opencv/opencv)

<br>

## Installation
- Tested under Windows 10 and Linux with Qt version 5.15.2
- Download the current release link... and unzip
- Open `CMakeLists.txt` inside your Qt Creator and configure with on if your installed Qt kits
- If you want to play videos you have to install codecs to your system. For windows i can recommend the K-Lite Basic Pack: [link](http://www.codecguide.com/download_kl.htm)

<br>

**CMake options**

Options | Purpose | Default |
:------ |:------- |:------: |
APP\_BUILD\_PLUGINS | Build plugins (be sure dependencies are installed and in PATH) | ON
APP\_BUILD\_TESTS |Build unit tests | ON
APP\_BUILD\_DOC | Generate documentation (requires Doxygen) | ON
APP\_COPY\_SAMPLES | Copy samples to the application folder | ON

<br>

## TO-DO
- [ ] Add more options to customize the application
- [ ] Display more image meta data (exiv2 plugin)
- [ ] Plugin for alternative database ...?
- [ ] Use VLC lib for videos ...?
- [ ] Port to Qt6
<br>

## Story
This application was published in the hope that someone would find it useful and inspiring.
In the first place this application was developed for my wife, to sort her beautiful camera pictures and to find her favorite memories in a well organized database.
Thanks a lot to Bryan for the instructive Udemy courses and YouTube tutorials. With this i could improve my skills and got some good inspirations to do this project.
For interested check out the links below and join the community:
- [facebook/voidrealms](https://www.facebook.com/groups/1400884323467285/)
- [youtube/voidrealms](https://www.youtube.com/user/VoidRealms)
- [udemy/bryan-cairns](https://www.udemy.com/user/bryan-cairns/)

Feedback, suggestions for improvements or ideas for new features are always welcome. If you find bugs, please report to: [github/issues](https://github.com/Simon-12/tidy-images/issues)

If you like the application and want to support, you can donate via:

PayPal | Bitcoin
:----: | :-----:
[![Paypal img](https://github.com/Simon-12/TestImage/blob/develop/app/icons/flaticon/paypal.png)](https://paypal.me/SimonSchwarzkopf) | <img src="https://github.com/Simon-12/TestImage/blob/develop/app/data/bitcoin-code.png" width="40%"/><br>**bc1qll43hkqvv9jjwqw54xhejw324q4t4t55p8ss9e**

<br>
