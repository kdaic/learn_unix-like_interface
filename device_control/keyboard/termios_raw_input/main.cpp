#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <termios.h>

#include <unistd.h> // for usleep()

// ハンドラ捕捉フラグ(ハンドラが呼ばれたら1になり終了合図)
volatile sig_atomic_t endflag = 0;

// 開始のターミナル設定
static struct termios org_termios_p;

/// ターミナル属性を入力待ちなしにする
/// @param[in] fd 属性を変更する端末ファイルディスクリプタ
/// @return 成功0; 失敗-1
int set_termios_raw_mode( int fd )
{
  struct termios termios_p;
  // 現在の属性を取得
  if( tcgetattr( fd, &termios_p ) )
  {
    return( -1 );
  }
  // 取得したターミナル属性を保存
  org_termios_p = termios_p;
  // 1文字来るまでreadをブロック (c_cc[VMIN]=1)
  termios_p.c_cc[VMIN]  =  1;
  // タイマを使わない (c_cc[VTIME]=0)
  termios_p.c_cc[VTIME] =  0;
  // 非カノニカルモード(Enterを押さなくてもバッファをフラッシュ)
  termios_p.c_lflag &= ~( ECHO|ICANON|
                          ECHOE|ECHOK|ECHONL );
  // 出力処理を実装に依存しない
  termios_p.c_oflag &= ~( OPOST );
  // 属性を設定(TCSADRAIN : fdへの出力が完了された後に設定有効化)
  return( tcsetattr( fd, TCSADRAIN, &termios_p ) );
}

// ターミナル属性の設定を復帰
void reset_termios()
{
  // 属性を復帰(TCSANOW : ただちに変更が有効になる)
  tcsetattr(0, TCSANOW, &org_termios_p);
}

/// シグナルハンドラ
/// @param[in] sig シグナル
void handler(int sig)
{
  endflag = 1;
  reset_termios();
}

/// ヘルプ
void help()
{
  std::cout << "'P' : inching move X=" << std::endl;
  std::cout << "'N' : inching move X=" << std::endl;
  std::cout << "'F' : inching move Y=" << std::endl;
  std::cout << "'B' : inching move Y=" << std::endl;
  std::cout << "'U' : inching move Z=" << std::endl;
  std::cout << "'D' : inching move Z=" << std::endl;
  std::cout << "'q' : quit." << std::endl;
  std::cout << std::endl;
}

/// メイン関数
int main()
{
  // ヘルプ出力
  help();

  // シグナルの設定
  if (signal(SIGINT, handler) == SIG_ERR)
  {
    std::cerr << "failed to set singal" << std::endl;
    exit(-1);
  }

  // ファイルディスクリプタ=0(標準入力0)の取得設定
  int input_fd = 0;
  if (set_termios_raw_mode(input_fd) < 0 ) {
    std::cerr << "failed to set termios" << std::endl;
    exit(-1);
  }

  // キー入力ループ
  char c;
  while( endflag==0 ) {
    c = getchar();
    std::cout << "'" << c << "'";
    if( c == 'q' ) {
      std::cout << "\r" << std::endl;
      reset_termios();
      break;
    }
    switch (c) {
     case 'P':
        std::cout << " : inching move X=" << "\r" << std::endl;
        break;
      case 'N':
        std::cout << " : inching move X=" << "\r" << std::endl;
        break;
      case 'F':
        std::cout << " : inching move Y=" << "\r" << std::endl;
        break;
      case 'B':
        std::cout << " : inching move Y=" << "\r" << std::endl;
        break;
      case 'U':
        std::cout << " : inching move Z=" << "\r" << std::endl;
        break;
      case 'D':
        std::cout << " : inching move Z=" << "\r" << std::endl;
        break;
      default :
        std::cout << "\r" << std::endl;
        break;
    }
    usleep(5000);
  }
  // sttyコマンドで端末設定デフォルトに戻す
#ifdef __QNX__
  // (+edit:デフォルト値に戻す)
  system("stty +edit");
#else
  // (cooked:デフォルト値に戻す)
  system("stty cooked");
#endif
  std::cout << "End\r" << std::endl;
  exit(0);
}


