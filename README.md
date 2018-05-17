# LiveWallpaper
This Program is LiveWallpaper Project.(English)  
这个解决方案是"LiveWallpaper"项目。(简体中文)  
這個解決方案是"LiveWallpaper"項目。(繁體中文)  
この解決策は「LiveWallpaper」プロジェクトです。(日本语)    
Cette solution est le projet "LiveWallpaper".(français)     
А это решение-проект "ливевальлпапер".(русский)  

## Icon
![](https://github.com/Alopex6414/LiveWallpaper/raw/master/Release/frame/Wait/Sakura.png)

## Simple
Do you stare at a boring desk every day? Or do we want our desktop to have a "Live" feeling? If you have such an idea, you might as well (laugh). Because of the exposure to some 3D rendering, I wonder if we can project video onto the desktop, so that our desktop becomes more Live (laugh). That's the idea, so I'd like to make a dynamic wallpaper program instead of a traditional desktop.


The LiveWallpaper project lasted about 3 months, right? If I remember correctly. Still, due to various pressures, work is really different from going to college. There are many things to learn, and there are very few free time. Maybe you can just think about something quietly after work every night... Well, how long does it take to make your first game? (laugh) You don't have to think so much...


Em... I think LiveWallpaper still has a lot of shortcomings, such as high CPU usage, unsynchronized audio and video, and sound decoding, which can't adapt to all video format... But I think that as long as it brings some happiness, it's not a big deal, is it?

## Abstract
This solution is based on the C/C + + Win32 and DirectX projects. The solution is divided into five projects, respectively LiveWallpaper, LiveWallpaperUI, LiveWallpaperCore, LiveWallpaperReStart, LiveWallpaperCleanUp. LiveWallpaper engineering is the application of the dynamic wallpaper users can directly open the program; LiveWallpaperUI project is the UI interface of dynamic wallpaper. LiveWallpaperCore project is a desktop rendering program for dynamic wallpaper. LiveWallpaperReStart project is to help restart the LiveWallpaperCore application; The LiveWallpaperCleanUp project is the default video for cleaning up the decompression.

这个解决方案是基于C/C++编写的Win32和DirectX工程. 解决方案分成5个工程，分别为LiveWallpaper, LiveWallpaperUI, LiveWallpaperCore, LiveWallpaperReStart, LiveWallpaperCleanUp. LiveWallpaper工程是整个动态壁纸用户可以直接打开的应用程序; LiveWallpaperUI工程是动态壁纸的UI界面; LiveWallpaperCore工程是动态壁纸的桌面渲染程序; LiveWallpaperReStart工程是帮助重启LiveWallpaperCore应用程序; LiveWallpaperCleanUp工程是用于清理解压后的默认视频.

  * ### LiveWallpaper
    * #### *`LiveWallpaper` is used to start the `LiveWallpaperUI` application.*  
    * #### *`LiveWallpaper` will end the process After the `LiveWallpaperUI` is started.*

    LiveWallpaper应用程序是作为用户进入动态壁纸应用的主入口，用于启用LiveWallpaperUI应用程序。在LiveWallpaperUI应用程序启动之后，LiveWallpaper会自动关闭当前进程。
    
    LiveWallpaperアプリケーションは,ユーザーとしての動的な壁紙アプリケーションの主な入口であり,LiveWallpaperUIアプリケーションを起動するために用いられる。LiveWallpaperUIアプリケーションが開始された後に,LiveWallpaperは,現在のプロセスを自動的に停止させる。

  * ### LiveWallpaperUI
    * #### *`LiveWallpaperUI` is the user UI part of the dynamic wallpaper.*
