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
    * #### *`LiveWallpaperUI` can implement the `LiveWallpaperCore` application. The configuration of the CFG file.*    
    * #### *`LiveWallpaperUI` controls the playback of desktop dynamic wallpaper.*    
    
    LiveWallpaperUI是动态壁纸的用户界面部分。LiveWallpaperUI可以控制LiveWallpaperCore应用程序的LiveCore.cfg配置文件，并且可以同时对动态视频桌面进行播放控制。    
    
    LiveWallpaperUIは、動的な壁紙のユーザーインターフェースです。LiveWallpaperUIは、LiveWallpaperCoreアプリケーションのLiveCore, cfgの構成ファイルを制御することができ,同時に動画デスクを同時に再生制御することができる。    
    
  * ### LiveWallpaperCore  
    * #### *The `LiveWallpaperCore` application is mainly used as the core of the dynamic wallpaper, which is used to decode and render the video files.*  
    * #### *The `LiveWallpaperCore` is mainly divided into three parts: video decoding part, audio decoding part, display refresh rendering part.*    
    * #### *Video decoding part mainly decodes video files into YUV video format; The audio decoding part mainly decodes the audio part of video files; The refresh rendering part is to draw the decoded YUV video frame onto the screen. Video decoding part adopts `ffmpeg library` for video decoding. The audio decoding part adopts `SDL library` for decoding. The refresh rendering part USES `Direct3D Surface` for more line rendering, which makes the screen update smoother.*      
    * #### *At the same time, `LiveWallpaperCore` can also decode the default video of the packet and render it to the screen window.*  
    
    LiveWallpaperCore应用程序主要是作为动态壁纸的核心，用于对视频文件进行解码并进行渲染。LiveWallpaperCore主要分为3个部分：视频解码部分、音频解码部分、显示刷新渲染部分。视频解码部分主要是对视频文件进行解码成YUV视频格式；音频解码部分主要是对视频文件的音频部分进行解码；刷新渲染部分是将解码产生的YUV视频帧绘制到屏幕上。视频解码部分采用了ffmpeg库进行视频解码；音频解码部分采用SDL库进行解码；刷新渲染部分采用了Direct3D Surface进行更行渲染，使得画面更新比较流畅。同时LiveWallpaperCore也可以对实现封包的默认视频进行解码，并渲染到屏幕窗口。  
    
    「LiveWallpaperCore ]アプリケーション主動態壁紙の核心に使用、動画ファイルをレンダリングしてデコード。ビデオデコード部分は主に、動画ファイルをデコード割YUVビデオフォーマット；オーディオデコード部分は主に、ビデオファイルのオーディオ部分をデコード；刷新レンダリング部分はをデコード発生フレーム描画YUV動画スクリーンに。ビデオデコード部分を採用したffmpeg库では、ビデオデコード；オーディオデコード部分を採用しSDL庫で復号化し、刷新を採用したSurface Direct3Dレンダリング部分をもっといいレンダリング、更新が流暢な画面。同時に「LiveWallpaperCore」も実現パケットのデフォルトの動画で復号化し、スクリーンをレンダリング窓口。  
    
  * ### LiveWallpaperReStart    
    * #### *The `LiveWallpaperReStart` application is the process used to restart the dynamic wallpaper.*
    
    LiveWallpaperReStart应用程序是用来对动态壁纸重新启动的进程。
    
    LiveWallpaperReStartアプリケーションは用いて動態壁紙再起動のプロセス。

  * ### LiveWallpaperCleanUp    
    * #### *The `LiveWallpaperCleanUp` application is used to clean up the video after the video is removed in the default video mode.* 
    
    LiveWallpaperCleanUp应用程序是用来对默认视频模式下拆包之后的视频在播放完成之后的清理。  
    
    LiveWallpaperCleanUpアプリケーションは、デフォルトのモードにビデオをはずしてパック後の動画放送完成した後の整理。  
    
## Effect    
  * ### *Essential*
    * #### *The following picture shows how LiveWallpaper works and configuring it.*
    ![](https://github.com/Alopex6414/LiveWallpaper/raw/master/Gif/Animation.gif)
