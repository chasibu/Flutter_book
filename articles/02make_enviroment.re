= 開発環境構築

それでは、PCを操作して実際に環境の構築を行なっていこうと思います。

インストールするものは次のとおりです。

 1. Flutter SDK
 2. Xcode（（Macのみ）iOSの開発を行う場合）
 3. Android Studio（Androidの場合）

基本的に開発環境および開発は@<b>{Mac}をベースに行います。
Windows、Linuxでは環境構築の手順が異なりますので、公式サイトのインストール項目をご確認下さい。

※公式サイト：@<href>{https://flutter.io/get-started/install/}

== Flutter SDKのインストール
まずは、Flutter SDKのインストールから行います。
基本的には公式のページに英語のドキュメントがありますので、それに沿って行えば問題なくインストール行えます。

1. 公式のFlutterのサイト（@<href>{https://flutter.io/setup-macos/}）にアクセスします。
 画面トップの方にFlutter SDKのダウンロードリンクがありますので、ダウンロードします。
※執筆時点ではフォルダー名が「flutter_macos_v0.7.3-beta.zip」となっております。
//image[download][ダウンロードリンク]{
//}

2. 公式ドキュメントどおり、ホーム直下に「development」フォルダーを作成し、そこにフォルダーを展開しましょう。

//cmd{
  $ mkdir development
  $ cd ~/development
  $ unzip ~/Downloads/flutter_macos_v0.6.0-beta.zip
//}

3. パスを追加します。次のコマンドを入力して、「~.bash_profile」ファイルにパスを書き込みます。

//cmd{
  $ cd
  $ vim bash_profile
//}

//cmd{
  #ファイルの一番下に書き込む
  export PATH=/Users/user/development/flutter/bin:$PATH
//}

4. pathを定義したファイルの再読み込みを行ないます。

//cmd{
source $HOME/.bash_profile
//}

5. pathが更新されたかを確認します。

//cmd{
echo $PATH
//}
正しく更新されていれば、3.で記載した内容が表示されます。

=== Android Studio インストール

 1. 公式サイト（@<href>{https://developer.android.com/studio/}）
よりインストーラをダウンロードし、インストールします。
 2. インストール手順等についてはこちら（@<href>{https://developer.android.com/studio/install?hl=ja}）
を参考にインストールして下さい。

== プラグインの追加
基本的にはAndroidアプリ、iOSアプリを作るにしろ全て、Android Studioを操作して行きます。そのため、Flutterを使う準備など全てAndroidStudio上で行います。

 1. 画面上部より、「AndroidStudio>Preferences>Plugins」を選択します。
 2. プラグイン一覧が表示されるので、「Flutter plug-in」を選択して、インストールを行います。
 3. 途中、「Dart plugin」をインストールしてもいいかと聞かれるので、インストールして下さい。
 4. インストール後、AndroidStudioを再起動します。

== Flutterの動作確認
長くなりましたが、環境構築は以上となり、残りは動作確認になります。
開発に入るまでもう一息ですが、頑張りましょう！

 1. 画面上部より「File>New>New Flutter Project」を選択します。
 2. 「Flutter Application」を選択し、「Next」を選択します。
 3. 「Projectname」を「Flutter_test」とし、「Next」を選択します。
 4. 「Set the package name」画面では特に変更を加えずに、「Finish」を選択します。
 5. 「今開いている画面で開くかどうか」聞かれるので、「This Window」を選んでおきましょう。
 6. 画面上部にあるデバイス選択画面から使用デバイスを選択します。
　先ほど起動した、「Nexus 5X」があると思いますので、選択します。
 7. 先ほど同様に、Nexus 5Xが起動すると思いますので、起動を確認したら、AndroidStudioの画面上部にある再生ボタンを選択します。
 8. 画像のようなデモアプリが実行されれば動作確認完了です。

=====[column] エミュレータの設定

  1. インストールが完了したら、AndroidStudioを開き、Androidシミュレータの設定を行います。
     画面上部にある、「AVD Manager」のアイコンを選択します。
  2. 表示された画面の左下にある「Create Virtual Device...」のボタンを選択します。
  3. デバイス選択画面が表示されるので「Nexus 5X」を選択し、右下の「Next」ボタンを選択します。
     ※基本的にどれ選んでも問題ないと思うのですが、今回動作確認を行なったデバイスがNexus 5Xだったため、これを選択しています。
  4. OSのバージョン選択画面が表示されますが、「Android 8.1」を選択し、右下の「Next」ボタンを押下します。
  5. 設定の確認画面が出てきますが、特に変更することなく、右下の「Finish」を選択します。
  6. 再生ボタンを選択し、デバイスを起動させます。
  7. Nexus 5Xが画面に表示されれば、成功です。画面横にある×ボタンを選択して、エミュレータを終了させます。

====[/column]

=====[column] ホットリロード

FlutterにはHot Reloadという、アプリ実行中に変更を反映させるためにアプリを停止させることなく、効率よくアプリ開発ができる機能があります。

次の画像は、「Hello World!」から「Flutter」と文字をプログラム上で変更する例です。
文字を変更してプログラムを保存すると1秒後には画像にあるようにアプリの表示が更新されました。

通常であれば数十秒から数分かかるプログラムの更新がすぐできるので非常に効率よくプログラムを作成できるのが伝わると思います。

//image[hotreload][Hot Reload（文字変更）]{
//}

====[/column]
