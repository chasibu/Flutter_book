= Firebaseの設定をしよう

この章を完了すると下記のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter6}

== アカウント取得
1. FirebaseのWebサイトを開き、画面の右上にある「コンソールへ移動」を選択します。

Firebase公式サイト : @<href>{https://firebase.google.com/}

//image[firebase1][コンソールへ移動][scale=0.8]{
//}

2. 「Firebaseへようこそ」と記載された画面が表示されたら、「プロジェクトを追加」を選択します。

//image[firebase2][プロジェクトを追加][scale=0.8]{
//}

3. プロジェクト名に「kasikari-memo」を入力します。
すべてにチェックを入れて、プロジェクト作成ボタンを押します。

//image[firebase3][情報を入力][scale=0.6]{
//}

4. しばらく待つとプロジェクトが作成されるので、「次へ」ボタンを選択します。

//image[firebase4][準備完了][scale=0.5]{
//}

== プロジェクトとFirebaseの紐付け

Android向けとiOS向けにそれぞれ設定を行う必要があります。

=== Androidの設定

1.「Project Overview」を選択し、画面上にある「Android」のマークを選択します。

//image[firebase5][Androidの設定][scale=0.8]{
//}

2. アプリの登録を行うのにAndroidのパッケージ名を入力する必要があるので、それを調べます。
「android/app/src/main/AndroidManifest.xml」を開きます。

「package」の値がパッケージ名なので、これをコピーします。

//image[firebase6][AndroidManifest][scale=0.8]{
//}

3. パッケージ名を入力し、「アプリを登録」をクリックします。

//image[firebase7][パッケージ名を入力][scale=0.8]{
//}


4. 「google-services.json をダウンロード」をクリックし、Jsonファイルをダウンロードします。
ダウンロードが完了したら「次へ」をクリックします。

//image[firebase8][ダウンロード][scale=0.8]{
//}

5. ダウンロードしたファイルを「android/app」フォルダ直下にコピーします。

//image[firebase9][ファイルを配置][scale=0.8]{
//}

6. 配置できたら次は2つのファイルを設定します。
「android/build.gradle」と「android/app/build.gradle」に次の内容を追記します。

//list[main_connectfirebase1][android/build.gradle]{
  buildscript {
     dependencies {
         classpath 'com.google.gms:google-services:4.0.1'   // ADD
     }
  }
//}

//list[main_connectfirebase2][android/app/build.gradle]{
  dependencies {
    implementation 'com.google.firebase:firebase-core:16.0.1'//ADD
  }
  apply plugin: 'com.google.gms.google-services'//ADD
//}

//image[firebase10][追記内容][scale=0.8]{
//}

7. 最後にこの表示になりますが、「このステップをスキップ」をクリックして処理を終了します。
これでAndroidの設定は完了です！

//image[firebase11][このステップをスキップ][scale=0.8]{
//}

=== iOSの設定

1.「Project Overview」を選択し、画面上にある「iOS」のマークを選択します。

2. アプリの登録を行うのにiOSバンドルIDを入力する必要があるので、それを調べます。次のコマンドを入力して
Xcodeから該当のプロジェクトのフォルダーを開きます。

//cmd{
  $ cd Users/user/development/kasikari_memo
  $ open ios/Runner.xcworkspace
//}

今回作業をしているフォルダーに移動して、Ⅹcodeで開くようにコマンドを叩きます。

//image[open_xcode][Xcodeで開く][scale=0.8]{
//}

3. サイドバーからRunnerを選択し、Runnernの横にあるボタンを押します。
「TARGETS」の下にある「Runner」を選択すると、画面中央に「Bundle Identifier」と記載のある欄が表示されます。
これがバンドルIDなので、コピーします。

//image[show_bundleID][バンドルIDのコピー][scale=0.8]{
//}

5. Firebaseのアプリ登録画面に戻り、バンドルIDを入力し、アプリの登録を行います。

6. 画面の表示に従い、「GoogleService-info.plist」をダウンロードします。

7. ダウンロードしたファイルをXcode上で「Runner」フォルダの直下に移動させます。

//image[downloadfile][ダウンロードファイルの移動][scale=0.8]{
//}

== データベースの作成
1. 左のリストより「開発」→「Database」を選択します。
選択したら「Cloud FireStore」のデータベースを作成します。

@<b>{このときに間違えてRealtime Databaseで作成しないように注意してください。}

//image[database1][Cloud FireStore][scale=0.8]{
//}

2. 「テストモードで開始」を選択し、有効にするボタンをクリックします。

//image[database2][テストモードで開始][scale=0.8]{
//}

== テストデータの作成

1. 「＋コレクションを追加」を選択して、テスト用データを作成します。

//image[database3][コレクションを追加][scale=0.8]{
//}

2. コレクションの作成ダイアログが表示されます。
コレクションIDに「kasikari-memo」と入力し、「次へ」をクリックします。

//image[database4][コレクションの作成ダイアログ][scale=0.8]{
//}

3. テスト用のデータをして次のデータを入力します。入力できたら「保存」をクリックします。

//table[firebase-document][作成するコレクション]{
フィールド	タイプ	値
--------------------------------------------------------------
borrowOrLend	String	lend
stuff	String	PC
user	String	てすとユーザ
date	timestamp	2018/10/8
//}

//image[database5][作成するコレクション][scale=0.8]{
//}

4. 正常に作成できると、次のようになっているはずです。

これでFirebaseの設定は完了です！

//image[database6][成功例][scale=0.7]{
//}
