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
- [ ] 添加Encode Text（编码当前文本）功能
- 升级协议：区分文本和文件，加入文件名
  - [ ] 发送端
  - [ ] 接收端
- [x] 添加STOP（停止发送）按钮
- [ ] 连接超时的检测与提示

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

### Win32 API

- [How can we check if a file Exists or not using Win32 program?](http://stackoverflow.com/questions/3828835/how-can-we-check-if-a-file-exists-or-not-using-win32-program)
- [Win32 - Select Directory Dialog from C/C++](http://stackoverflow.com/questions/12034943/win32-select-directory-dialog-from-c-c)
- [CoTaskMemFree Function]() - 使用这个而非IMalloc->Free()释放pidl
- [DialogBoxIndirectParam](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645461(v=vs.85).aspx) - 从二进制对话框“模板”创建对话框
- [DialogProc callback function](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645469(v=vs.85).aspx)
- [Changing the Current Directory](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363806(v=vs.85).aspx) - 改变“当前”目录

### Win32 Resource File
- [How can I read a compiled resource (.res) file in C#?](http://stackoverflow.com/questions/7982181/how-can-i-read-a-compiled-resource-res-file-in-c)

### base64
- [coreutils/base64.c](http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/base64.c)
- [gnulib/base64.c](http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob;f=lib/base64.c;h=1a8bfce7a534f83f19a093432bafe883f16de9b1;hb=HEAD)

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

