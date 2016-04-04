## TODO
- [x] 开发一个分派程序，可供用户选择是进入默认虚拟机还是修改版虚拟机
- [x] 开发一个对话框，可供用户输入要粘贴进虚拟机的内容
- [ ] 开发读入文件&转换为base64编码的功能
- [ ] 开发接收端base64解码的功能

## 参考
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

## 2016.3.30
- 学宝虚拟机每次重新启动（cold & hot），都会使用新的端口号和密码。
- 能否通过给virt-viewer编写扩展来解决问题？
