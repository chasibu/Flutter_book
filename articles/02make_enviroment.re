= 開発環境を構築しよう

それでは、開発するために環境構築を行います。

インストールするものは次のとおりです。

 * Flutter SDK
 * Android Studio
 * Xcode（（Macのみ）iOSの開発を行う場合）

基本的に開発環境および開発は@<b>{Windows 10}をベースに行います。
Flutterはベータ版なのでインストール方法が変わる可能性があります。

執筆現在（2018/9/23）のインストール方法について紹介します。
本書の手順でうまくいかない場合など最新のインストール方法については公式サイトをご覧ください。

公式サイト： @<href>{https://flutter.io/get-started/install/}

== Flutter SDKのインストール

Flutter SDKのインストールを行います。
WindowsとMacのインストールがそれぞれ異なるので順に説明します。

=== Windows版

1. 公式のFlutterのサイト（@<href>{https://flutter.io/setup-windows/}）にアクセスします。
Flutter SDKのダウンロードリンクがありますので、ダウンロードします。

※執筆時点ではフォルダー名が「flutter_macos_v0.8.2-beta.zip」となっております。

//image[windows1][ダウンロードリンク][scale=0.8]{
//}

2. ダウンロードしたZipファイルを展開し中身のFlutterフォルダを「C:\Users\ユーザフォルダ」の下などに配置します。

//image[windows2][フォルダ配置][scale=0.8]{
//}

3.「コントロールパネル > ユーザーアカウント > ユーザーアカウント > 環境変数の変更」をすると次のような画面が表示されます。

「Path」と書かれた行を選択した上で編集というボタンを押します。

//image[windows3][パス設定][scale=0.8]{
//}

4. 先ほど 2.の手順で配置したフォルダのパスを「編集」をクリックし、設定します。

本書と同じ手順であれば「C:\Users\ユーザフォルダ\flutter\bin」となります。
設定が完了したらOKをクリックし、閉じます。

//image[windows4][パス設定][scale=0.6]{
//}

Windows版のFlutter SDKの準備は完了です。

=== Mac版

1. 公式のFlutterのサイト（@<href>{https://flutter.io/setup-macos/}）にアクセスします。
Flutter SDKのダウンロードリンクをクリックし、ダウンロードします。

※執筆時点ではフォルダー名が「flutter_macos_v0.8.2-beta.zip」となっております。

//image[mac1][ダウンロードリンク][scale=0.8]{
//}

2. 公式ドキュメントどおり、ホーム直下に「development」フォルダーを作成し、そこにフォルダーを展開しましょう。

//cmd{
  $ cd
  $ mkdir development
  $ cd ~/development
  $ unzip ~/Downloads/flutter_macos_v0.8.2-beta.zip
//}

3. パスを追加します。次のコマンドを入力して、「~.bash_profile」ファイルにパスを書き込みます。

//cmd{
  $ cd
  $ vim .bash_profile
//}

//cmd{
  #ファイルの一番下に書き込む userと書かれた部分には実行ユーザ名が入ります。
  export PATH=/Users/${user}/development/flutter/bin:$PATH
//}

※次の画像の57行目のように入力して下さい。画像では、「user」の箇所が実行ユーザ名の「sho」となっています。
ここの名前は実行環境により異なります。

//image[write_path][パス入力画面][scale=0.8]{
//}


4. pathを定義したファイルの再読み込みを行ないます。

//cmd{
source $HOME/.bash_profile
//}

5. pathが更新されたかを確認します。

//cmd{
echo $PATH
//}

※場合によっては、次の画像のように先頭に表示されない場合がありますので、注意して確認してください。

//image[path_list][パス表示画面][scale=0.5]{
//}

Mac 版の Flutter SDK の準備は完了です。

== Android Studioのインストール

1. 公式サイト（@<href>{https://developer.android.com/studio/}）よりインストーラをダウンロードします。

//image[android1][Android Studioのインストール][scale=0.8]{
//}

2. インストーラに沿ってインストールを完了してください。

== Flutterプラグインの追加

Android StudioでFlutterを開発するためにFlutterのプラグインをインストールします。

1. 起動画面で「Configure>Plugins」を選択します。

//image[plugin1][Flutterプラグインのインストール][scale=0.8]{
//}

もしくは「File＞settings」からでも同様の画面に進むことができます。

//image[plugin2][Flutterプラグインのインストール][scale=0.7]{
//}

2. プラグイン一覧が表示されます。下部にある「Browser repositories」を選択してます。

//image[plugin3][Flutterプラグインの一覧][scale=0.8]{
//}

3. 検索欄がありますので「flutter」と入力します。選択するとインストールボタンが表示されるのでそれをクリックします。

//image[plugin4][Flutterプラグインの検索][scale=0.8]{
//}

4. 途中、「Dart plugin」をインストールしてもいいかと聞かれるので「Yes」を選択し、インストールして下さい。

//image[plugin5][Dartプラグインのインストール][scale=0.8]{
//}

5. インストール完了後、Browse Repositoriesを「Close」で閉じ、「Flutter」をリストから探しクリックします。

「Restart Android Studio」をクリックします。
そうするとAndroid Studioが再起動するのでしばらく待ちましょう。

//image[plugin6][Dartプラグインのインストール][scale=0.8]{
//}

これで環境構築は完了です！

次の章ではいったんアプリの開発を始める前にサンプルプログラムを動かして、デバイスへのデプロイなどを体験します。
