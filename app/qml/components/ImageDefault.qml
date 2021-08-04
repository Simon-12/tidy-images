import QtQuick 2.15
import QtQuick.Controls 2.15


// Default image with default options
Image {

    asynchronous: true // load image in extra thread
    antialiasing: true
    smooth: true // smoothly filtered when scaled or transformed
    mipmap: true // better visual quality when scaling down compared to smooth
    fillMode: Image.PreserveAspectFit // if image larger -> scale down
}
