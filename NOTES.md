## TODO
- [x] 开发一个分派程序，可供用户选择是进入默认虚拟机还是修改版虚拟机
- [x] 开发一个对话框，可供用户输入要粘贴进虚拟机的内容
- [ ] 开发读入文件&转换为base64编码的功能
- [x] 开发接收端base64解码的功能

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
- [GtkScrolledWindow](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html)
  - [gtk_scrolled_window_set_policy ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-policy)
  - [gtk_scrolled_window_set_shadow_type ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-shadow-type)
- [How to set a fixed windows size for a GTK+ app in C?](http://stackoverflow.com/questions/4772804/how-to-set-a-fixed-windows-size-for-a-gtk-app-in-c)
- [GLib: Key-value file parser](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html)
  - [g_key_file_new ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-new)
  - [g_key_file_load_from_file ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-load-from-file)
  - [g_key_file_get_integer_list ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-integer-list)
- [GtkFileChooserDialog](https://developer.gnome.org/gtk2/2.24/GtkFileChooserDialog.html)

### Win32 API

- [How can we check if a file Exists or not using Win32 program?](http://stackoverflow.com/questions/3828835/how-can-we-check-if-a-file-exists-or-not-using-win32-program)
- [Win32 - Select Directory Dialog from C/C++](http://stackoverflow.com/questions/12034943/win32-select-directory-dialog-from-c-c)
- [CoTaskMemFree Function]() - 使用这个而非IMalloc->Free()释放pidl

### Win32 Resource File
- [How can I read a compiled resource (.res) file in C#?](http://stackoverflow.com/questions/7982181/how-can-i-read-a-compiled-resource-res-file-in-c)

### base64
- [coreutils/base64.c](http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/base64.c)
- [gnulib/base64.c](http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob;f=lib/base64.c;h=1a8bfce7a534f83f19a093432bafe883f16de9b1;hb=HEAD)

## 2016.3.30
- 学宝虚拟机每次重新启动（cold & hot），都会使用新的端口号和密码。
- 能否通过给virt-viewer编写扩展来解决问题？
