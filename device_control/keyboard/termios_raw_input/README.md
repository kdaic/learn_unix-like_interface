termios input
===

簡易的なキーボード入力プログラム。

- termios構造体の属性を設定し、Enter入力待ちなしのキー入力を試す。  
- 実行プロセスからキー入力(Ctrl+c)でシグナル(SIGINT)を取得できるようにする。  
  (termios.c_lflag にISIGを設定しない)  
- 終了後に改行位置が崩れないようにする  
  (設定していたターミナル属性リセットする、 ``stty cooked`` をシステムコールしてデフォルトに戻す)  

&nbsp;

## 参照URL

- [QNX6.5.0SP1 リファレンス tcsetattr()](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/t/tcsetattr.html)  
- [Man Page of TERMIOS](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/termios.3.html)  

&nbsp;

<div align="right"> 以上. </div>
