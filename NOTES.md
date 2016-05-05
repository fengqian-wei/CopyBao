## TODO

### ver 1.0
- [x] 开发一个分派程序，可供用户选择是进入默认虚拟机还是修改版虚拟机
- [x] 开发一个对话框，可供用户输入要粘贴进虚拟机的内容
- [x] 开发读入文件&转换为base64编码的功能
- [x] 开发发送端调速功能
- [x] 开发接收端base64解码的功能
- [x] 清理spicy的界面

### ver 1.1
- [ ] 重构spicy.c，把发送窗口的部分分割出来。允许单独调试发送窗口 
- [x] 添加STOP（停止发送）按钮

### ver 2.0
- [ ] 添加菜单项FileSender，实现长文件的分块、互动、出错重传的传输
- [ ] 添加菜单项Copy File，弹出文件对话框，复制文件
- [ ] 开发文件显示对话框

## 参考

### GTK

- [GTK+ 2.0 Tutorial](https://developer.gnome.org/gtk-tutorial/stable/)
  - [Timeouts](https://developer.gnome.org/gtk-tutorial/stable/c1759.html)
  - [Progress Bars](https://developer.gnome.org/gtk-tutorial/stable/x829.html)
- [GTK+ 2 Reference Manual](https://developer.gnome.org/gtk2/2.24/)
  - [gtk_window_set_modal ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-modal)
- [Text Widget Overview](https://developer.gnome.org/gtk2/2.24/TextWidget.html)
- [GtkTextView](https://developer.gnome.org/gtk2/2.24/GtkTextView.html)
  - [gtk_text_view_set_wrap_mode ()](https://developer.gnome.org/gtk2/2.24/GtkTextView.html#gtk-text-view-set-wrap-mode)
  - gtk_widget_set_sensitive () for _enable/disable_
  - [gtk_text_view_get_buffer ()](https://developer.gnome.org/gtk2/2.24/GtkTextView.html#gtk-text-view-get-buffer)
  - GtkTextBuffer
    - [gtk_text_buffer_get_text ()](https://developer.gnome.org/gtk2/2.24/GtkTextBuffer.html#gtk-text-buffer-get-text)
    - [gtk_text_buffer_get_start_iter ()](https://developer.gnome.org/gtk2/2.24/GtkTextBuffer.html#gtk-text-buffer-get-start-iter)
      - __Hints:__ g_free()
    - [g_object_ref ()](https://developer.gnome.org/gobject/unstable/gobject-The-Base-Object-Type.html#g-object-ref)
  - [gtk_text_view_set_editable ()](man.chinaunix.net/develop/GTK+/2.6/gtk/GtkTextView.html#gtk-text-view-set-editable)
- [GtkScrolledWindow](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html)
  - [gtk_scrolled_window_set_policy ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-policy)
  - [gtk_scrolled_window_set_shadow_type ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-shadow-type)
- [How to set a fixed windows size for a GTK+ app in C?](http://stackoverflow.com/questions/4772804/how-to-set-a-fixed-windows-size-for-a-gtk-app-in-c)
- [GLib: Key-value file parser](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html)
  - [g_key_file_new ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-new)
  - [g_key_file_load_from_file ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-load-from-file)
  - [g_key_file_get_integer_list ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-integer-list)
- [GtkFileChooserDialog](https://developer.gnome.org/gtk2/2.24/GtkFileChooserDialog.html)
- [GtkMessageDialog](http://man.chinaunix.net/develop/GTK+/2.6/gtk/GtkMessageDialog.html)
- [gtk_widget_hide_on_delete ()](http://man.chinaunix.net/develop/GTK+/2.6/gtk/GtkWidget.html#gtk-widget-hide-on-delete)
- [g_locale_from_utf8 ()](https://developer.gnome.org/glib/unstable/glib-Character-Set-Conversion.html#g-locale-from-utf8)
- [spice_main_file_copy_async()](http://www.spice-space.org/api/spice-gtk/SpiceMainChannel.html#spice-main-file-copy-async)
  - [The “new-file-transfer” signal](http://www.spice-space.org/api/spice-gtk/SpiceMainChannel.html#SpiceMainChannel-new-file-transfer)
  - [GCancellable](https://developer.gnome.org/gio/unstable/GCancellable.html)
  - [GFile](https://developer.gnome.org/gio/stable/GFile.html#GFileCopyFlags)
  - [GAsyncResult](https://developer.gnome.org/gio/stable/GAsyncResult.html#GAsyncReadyCallback)
- [glib-genmarshal](https://developer.gnome.org/gobject/stable/glib-genmarshal.html)
  - 用于实现<code>spice-marshal.txt</code>→<code>spice-marshal{.h, .c}</code>的转换
- [gtk_window_set_deletable ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-deletable)可用来禁用关闭按钮
- [gtk_window_set_type_hint ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-type-hint)设置为[GDK_WINDOW_TYPE_HINT_DIALOG](https://developer.gnome.org/gdk2/2.24/gdk2-Windows.html#GdkWindowTypeHint)可用来隐藏最大最小化按钮
- [g_message ()](https://developer.gnome.org/glib/unstable/glib-Message-Logging.html#g-message) 使用g_message等函数记录日志
- [g_path_get_basename ()](https://developer.gnome.org/glib/stable/glib-Miscellaneous-Utility-Functions.html#g-path-get-basename) 获得路径中的文件名部分。

### Win32 API

- [How can we check if a file Exists or not using Win32 program?](http://stackoverflow.com/questions/3828835/how-can-we-check-if-a-file-exists-or-not-using-win32-program)
- [Win32 - Select Directory Dialog from C/C++](http://stackoverflow.com/questions/12034943/win32-select-directory-dialog-from-c-c)
- [CoTaskMemFree Function]() - 使用这个而非IMalloc->Free()释放pidl
- [DialogBoxIndirectParam](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645461(v=vs.85).aspx) - 从二进制对话框“模板”创建对话框
- [DialogProc callback function](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645469(v=vs.85).aspx)
- [Changing the Current Directory](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363806(v=vs.85).aspx) - 改变“当前”目录
- [Creation of a Console (Windows)](https://msdn.microsoft.com/en-us/library/windows/desktop/ms682528(v=vs.85).aspx) A process can also create a console by specifying the **CREATE_NEW_CONSOLE** flag in a call to CreateProcess. 传递这参数给CreateProcess，可以让spicy.exe显示出命令行窗口。
  - 参考[此页面](http://stackoverflow.com/questions/780465/winapi-createprocess-but-hide-the-process-window)学习CreateProcess的用法

### Win32 Resource File
- [How can I read a compiled resource (.res) file in C#?](http://stackoverflow.com/questions/7982181/how-can-i-read-a-compiled-resource-res-file-in-c)

### base64
- [coreutils/base64.c](http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/base64.c)
- [gnulib/base64.c](http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob;f=lib/base64.c;h=1a8bfce7a534f83f19a093432bafe883f16de9b1;hb=HEAD)
- [g_base64_encode ()](https://developer.gnome.org/glib/unstable/glib-Base64-Encoding.html#g-base64-encode) GLib本身就提供base64加密解密支持。
- [Base64在线编码解码](http://tools.jb51.net/tools/base64_decode-gb2312.php)

### C# ###
- [Control.InValidate vs. Control.Refresh()?](https://bytes.com/topic/c-sharp/answers/244445-control-invalidate-vs-control-refresh)
- [String.Format for Hex](http://stackoverflow.com/questions/11618387/string-format-for-hex)
- [Reference Source](http://referencesource.microsoft.com/)
- [How do I encode and decode a base64 string?](http://stackoverflow.com/questions/11743160/how-do-i-encode-and-decode-a-base64-string)
- [C#: Get complete desktop size?](http://stackoverflow.com/questions/1317235/c-get-complete-desktop-size)
- [C# - Reading from and Writing into Binary files](http://www.tutorialspoint.com/csharp/csharp_binary_files.htm)
- [/target (C# Compiler Options)](https://msdn.microsoft.com/zh-cn/library/6h25dztx.aspx)

### SPICE
- [Spice-GTK Reference Manual](http://www.spice-space.org/api/spice-gtk/index.html)
- [DisplayChannel: The “display-primary-create” signal](http://www.spice-space.org/api/spice-gtk/SpiceDisplayChannel.html#SpiceDisplayChannel-display-primary-create) 
  - 处理此信号时，可以保存屏幕缓冲区的地址
  - 虚机的<code>d_format</code>是32_xRGB，即颜色用32位整数表示，只有24位有效。little-endian下B是第一个字节。
  - 参数<code>d_stride</code>指屏幕的pitch，一般等于<code>d_width*4</code>。
- [DisplayChannel: The “display-invalidate” signal](http://www.spice-space.org/api/spice-gtk/SpiceDisplayChannel.html#SpiceDisplayChannel-display-invalidate) 画面一旦有内容上的更新，就会触发此信号
- [spicy-screenshot.c](https://github.com/SPICE/spice-gtk/blob/master/src/spicy-screenshot.c)

### misc
- [fstat](http://linux.die.net/man/2/fstat) - 获得文件长度
- [tmpfile](https://msdn.microsoft.com/zh-cn/library/x8x7sakw.aspx) - 创建一个临时文件并返回其FILE指针

## 2016.3.30
- 学宝虚拟机每次重新启动（cold & hot），都会使用新的端口号和密码。
- 能否通过给virt-viewer编写扩展来解决问题？

## 2016.4.7
- 把read_file改成了接受一个FILE \*参数（而不是文件路径），之后读取文件到文本框的的功能失效。后将fopen("r")改成了"rb"，解决了问题。
- 在receiver的实现中，也是使用w而不是wb模式打开的将要写入内容的文件。这导致接收到的文件存盘时，长度莫名增加。而后加上'b'修复了bug。
- 为<code>GtkTextView</code>设置了新的TextBuffer后，会将旧的TextBuffer的引用计数减一。此前如果用<code>gtk_text_view_get_buffer()</code>保存了TextBuffer，该TextBuffer就会失效，因为该函数不会增加TextBuffer的引用计数。因此如果要避免旧的TextBuffer失效，在获取、保存它之后，就要用<code>g_object_ref()</code>增加它的引用计数。

## 2016.4.8
- Windows的文本框有长度限制，超过某个长度后，就无法再增加字符。这会导致大文件（大约25kB左右）传输失败。

## 2016.5.2
我尝试了SPICE协议自带的文件传送功能，传送1M的文件只需2s，效果很好。

问题有两个：
- **Fedora提供的MinGW的spice-gtk包版本太低。**它使用的还是旧版的文件传输，示例程序里文件传输部分的代码是不可用的，因为这个版本根本没有emit信号<code>new-file-transfer</code>。
  - 所以<code>spice.c</code>里面那个显示文件传输进度的对话框是不会显示的。
    - 不过使用<code>spice_main_file_copy_async()</code>的回调函数也能简单监控文件传输的进度。
  - 判断文件传输是否为新版的一种方法是：检查<code>/usr/i686-w64-mingw32/sys-root/mingw/include/spice-client-glib-2.0/</code>中有没有<code>spice-file-transfer.h</code>。
    - 注意：并不是头文件的问题，是spice-gtk库的问题。
  - spice客户端提供文件传输功能的源文件是spice-gtk仓库中<code>channel-main.c</code>。关于文件传输功能的改版，参见[这次commit](https://github.com/SPICE/spice-gtk/commit/2c26ee3c37691f51e1746d9d1004635dd356c28a)。
- **远程机器上的agent程序版本太低。**根本不支持接收文件。必须复制新版agent进去。
  - 远程机器上的vdagent可以在<code>C:\\Program Files\\SaiweiGuestAgent\\vdagent\\</code>目录找到。
  - 可以通过搜索vdagent.exe是否包含<code>%u %s</code>来判断它是否支持文件传送，参见[这次commit](https://cgit.freedesktop.org/spice/win32/vd_agent/commit/?id=71193f658131d31b28b6d9afdd385111bc32377b)。
    - 新版和旧版agent程序“属性”中的版本都是0.5.10.0，所以没办法根据这个确定新旧。
  - agent可以在[官方下载页面](http://www.spice-space.org/download.html)下载。
    - Guest/Windows Binaries
    - 可以用7-zip打开安装程序，从中找出32位的<code>vdservice.exe</code>和<code>vdagent.exe</code>。
  - 只需要替换<code>vdagent.exe</code>即可，该文件压缩后达近240K，传输过去大概需要1个多小时。
  - 替换远程机器上的agent前，先从其任务管理器中结束到两个vd\*进程，然后删除掉<code>vdagent.exe</code>，接下来复制新文件至那个文件夹，最后运行文件夹里的<code>upgrade.bat</code>。
  - 新版的vdagent只比老版本大了34K，能否通过二进制patch，只复制多出来的部分进去，实现替换，从而减少传输量？
