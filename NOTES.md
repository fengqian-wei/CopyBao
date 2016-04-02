## TODO
- [ ] 开发一个分派程序，可供用户选择是进入默认虚拟机还是修改版虚拟机
- [ ] 开发一个对话框，可供用户输入要粘贴进虚拟机的内容

## 参考
- [GTK+ 2.0 Tutorial](https://developer.gnome.org/gtk-tutorial/stable/)
- [GTK+ 2 Reference Manual](https://developer.gnome.org/gtk2/2.24/)
  - [gtk_window_set_modal ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-modal)
- [Text Widget Overview](https://developer.gnome.org/gtk2/2.24/TextWidget.html)
- [GtkTextView](https://developer.gnome.org/gtk2/2.24/GtkTextView.html)
  - [gtk_text_view_set_wrap_mode ()](https://developer.gnome.org/gtk2/2.24/GtkTextView.html#gtk-text-view-set-wrap-mode)
- [GtkScrolledWindow](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html)
  - [gtk_scrolled_window_set_policy ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-policy)
  - [gtk_scrolled_window_set_shadow_type ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-shadow-type)
- [How to set a fixed windows size for a GTK+ app in C?](http://stackoverflow.com/questions/4772804/how-to-set-a-fixed-windows-size-for-a-gtk-app-in-c)

## 2016.3.30
- 学宝虚拟机每次重新启动（cold & hot），都会使用新的端口号和密码。
- 能否通过给virt-viewer编写扩展来解决问题？
