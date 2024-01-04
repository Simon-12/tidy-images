# Tidy Images
Easily sort and organise your image collection.
<br>
<br>

[![Paypal](https://img.shields.io/badge/donate-PayPal-blue.svg?style=flat-square&logo=paypal)](https://paypal.me/SimonSchwarzkopf)
[![Bitcoin](https://img.shields.io/badge/donate-Bitcoin-orange.svg?style=flat-square&logo=bitcoin)](https://github.com/Simon-12/TestImage/blob/develop/app/data/bitcoin-code.png)
<br>
<br>

## Features

### View Modes

![Gallery](https://github.com/Simon-12/common/blob/main/tidy-images/01.gif)
<br>

Select a folder and view its contents. Images and videos can be viewed in different modes:
- Gallery view
- Image only viewer
- Video only viewer
- Compare images side by side
- Database content

<br>

### Move Actions

Files can be moved to a separate folder and added to a database for later browsing.
You can add multiple folders to organise your files.
Files can also be copied to a specific folder, deleted (seperate trash folder) or marked as favourites (copied to a separate folder).
In Gallery view, you can select and move multiple files at once.
All actions can be Undo or Redo.

<details>
<summary><b>Move Folders Example ...</b></summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/02.gif" width="65%"/>
</details>

<details>
<summary><b>Add Folder Example ...</b></summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/03.gif" width="65%"/>
</details>

<br>

### Label Files

Files can be tagged with labels, so that they are easier to find later.
When the Exiv2 plugin is active, these labels are added to the metadata comment section of the image.
Files with labels are automatically added to the database.

<details>
<summary><b>Label Example ...</b></summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/04.png" width="65%"/>
</details>

<br>

### Database

The database can be browsed for already sorted files.
Folders can be completely added or removed from the database.
The database can be filtered and sorted by name, folder, label, date, type or favourites.
Currently supported database driver is SQLite.

<details>
<summary><b>Database Example ...</b></summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/05.png" width="65%"/>
</details>

<br>

### Compare Images

Images can be compared with a side by side view, with details about the image such as size, type and recording date.
To find similar images, images can be compared using an algorithm (the algorithm requires the OpenCV plugin), the result is a score of how similar the image is to each other.

<details>
<summary><b>Compare Example ...</b></summary>
<img src="https://github.com/Simon-12/common/blob/main/tidy-images/06.png" width="65%"/>
</details>

<br>

## Plugins

The application can be extended with plugins.
The idea is to reduce dependencies so that the application can be built without external libraries.
Currently there are two plugins available.

<br>

Plugin |      | Description | Link
:----: | :--: | :----------- | :----
**Exiv2** | <img src="https://github.com/Simon-12/TestImage/blob/develop/plugins/exiv2/plugin/icon.png" width="50%"/> | Image metadata library and tools. It is used to read image metadata such as recording date and to read and write labels to the metadata comment section. | [github/exiv2](https://github.com/Exiv2/exiv2)
**OpenCV** | <img src="https://github.com/Simon-12/TestImage/blob/develop/plugins/opencv/plugin/icon.png" width="40%"/> | Open Source Computer Vision Library. Is required for reading and rotating images, read in single video frames to display a video thumbnail, and the image comparison algorithm. | [github/opencv](https://github.com/opencv/opencv)

<br>

## Installation
- Tested on Windows 10 and Ubuntu 22.04 with Qt version 6.4.3.
- Download the latest release from [github/tidy-images/releases](https://github.com/Simon-12/tidy-images/releases) and unzip it.
- Open `CMakeLists.txt` in your Qt Creator and configure with one of your installed Qt kits.
- If you want to play videos, you will probably need to install codecs on your system. For Windows I recommend the K-Lite Basic Pack: [codecguide.com](http://www.codecguide.com/download_kl.htm). For Ubuntu you need [FFmpeg](https://ffmpeg.org/).

<br>

### CMake options

Options | Purpose | Default |
:------ |:------- |:------: |
APP\_BUILD\_PLUGINS | Build plugins (be sure dependencies are installed and in PATH) | ON
APP\_BUILD\_TESTS |Build unit tests | ON
APP\_BUILD\_DOC | Generate documentation (requires Doxygen) | OFF
APP\_COPY\_SAMPLES | Copy samples to the application folder | ON
APP\_STATIC\_BUILD | Build static application | OFF
APP\_STATIC\_PLUGINS | Build and add static plugins to the application | OFF

<br>

## TO-DO
- [ ] Add more options to customise the application (style, font, colours).
- [ ] Edit database (remove rows, edit paths) → Make compatible with undo framework.
- [ ] More options for database (edit columns).

### Other Ideas
- [ ] Show more image metadata (exiv2 plugin).
- [ ] Plugin for alternative database ...?
- [ ] Use VLC library for videos ...?
- [ ] Add other language translations …?

<br>

## Story
This application has been released in the hope that someone will find it useful and inspiring.
It was originally developed for my wife to sort her beautiful camera pictures and find her favourite memories in a well organised database.
Thanks a lot to Bryan for the educational Udemy courses and YouTube tutorials.
They helped me improve my skills and gave me some good inspiration for this project.
If you are interested, check out the links below and join the community:
- [facebook/voidrealms](https://www.facebook.com/groups/1400884323467285/)
- [youtube/voidrealms](https://www.youtube.com/user/VoidRealms)
- [udemy/bryan-cairns](https://www.udemy.com/user/bryan-cairns/)

Feedback, suggestions for improvements or ideas for new features are always welcome. If you find any bugs, please report them to: [github/tidy-images/issues](https://github.com/Simon-12/tidy-images/issues)

If you like the application and would like to support it, you can donate via:

PayPal | Bitcoin
:----: | :-----:
[![Paypal img](https://github.com/Simon-12/TestImage/blob/develop/app/icons/flaticon/paypal.png)](https://paypal.me/SimonSchwarzkopf) | <img src="https://github.com/Simon-12/TestImage/blob/develop/app/data/bitcoin-code.png" width="40%"/><br>**bc1qll43hkqvv9jjwqw54xhejw324q4t4t55p8ss9e**

<br>
