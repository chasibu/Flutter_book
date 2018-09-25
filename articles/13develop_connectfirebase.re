= Firebaseとの連携
この章ではFirebaseとの連携を行います。といってもコードを書くのは次の章からでここでは連携の為の準備を
行います。
基本的にはこの導入のためのチュートリアルがあるので、それに沿って導入を進めて行きます。
※参考：Firebase for Flutter（https://codelabs.developers.google.com/codelabs/flutter-firebase/#0）
　これの１から８を行います。



== アカウント取得
1. FirebaseのWebサイトを開きます。Google等で検索すればトップに表示されると思うので、そこから開きましょう。
2. 画面の右上にある「コンソールへ移動」を選択します。
3. 保有のアカウント情報を入力します。持っていない場合は、新規作成してください。
4. 「Firebaseへようこそ」と記載された画面が表示されたら、「プロジェクトを追加」を選択します。
5. プロジェクト名を入力します。今回は「kasikari-memo」とします。
6. 次の項目のチェックボックスが表示されると思います。
　・Firebase 向け Google アナリティクスのデータ共有にデフォルトの設定を使用する
　・測定管理者間のデータ保護条項に同意します。
　・アプリで Firebase サービスを使用することに同意するとともに、該当する規約にも同意します。
　一番下の項目のみチェックをつければ、使用可能ですが、今回はGoogle アナリティクスのデータ共有をデフォルトの設定にしておきます。
 チェックをつけたら右下のプロジェクト作成ボタンを押します。
7. プロジェクトが作成されるので、完了したら、OKボタンを選択します。

ここまでくれば、コンソール画面が表示されると思います。

== プロジェクトとFirebaseの紐付け
アンドロイド向けiOS向けにそれぞれ設定を行う必要があります。

=== iOSの設定
1.「Project Overview」を選択し、画面上にある「iOS」のマークを選択します。
2. アプリの登録を行うのにiOSバンドルIDを入力する必要があるので、それを調べます。次のコマンドを入力して
Xcodeから該当のプロジェクトのフォルダーを開きます。

//cmd{
  $ cd Users/user/development/kasikari_memo
  $ open ios/Runner.xcworkspace
//}

今回作業をしているフォルダーに移動して、xcodeで開くようにコマンドを叩いています。
うまくいくと、次の画像のようにxcodeが開きます。
//image[open_xcode][xcodeで開く]{
//}

3. 左のペインからRunnerを選択すると、画面真ん中が、Runnerのinfoの画面に切り替わります。
切り替え後、Runnernの横にあるボタンを押します。
※次の画像にて、赤い四角で囲まれているボタンです。
//image[show_targets_list][Show_targets_listを開く]{
//}

4. 選択後、「TARGETS」の下にある「Runner」を選択すると、
画面真ん中に「Bundle Identifier」と記載のある欄が表示されます。
これがバンドルIDなので、コピーします。
※次の画像にて、赤い下線が引いてあるのが、バンドルIDになります。
//image[show_bundleID][バンドルIDの表示]{
//}

5. Firebaseのアプリ登録画面に戻り、バンドルIDを入力し、アプリの登録を行います。

6. 画面の表示に従い、「GoogleService-info.plist」をダウンロードします。

7. ダウンロードしたファイルをXcode上で「Runner」フォルダの直下に移動させます。
//image[downloadfile][ダウンロードファイルの移動]{
//}

以上で終わりです。

=== Androidの設定
1.「Project Overview」を選択し、画面上にある「Android」のマークを選択します。
2. アプリの登録を行うのにAndroidのパッケージ名を入力する必要があるので、それを調べます。
プロジェクト直下の「android/app/src/main/AndroidManifest.xml」を開きます。
3. 「manifest」エレメントの下にある「package」の値がパッケージ名なので、これをコピーし登録します。
4. 画面の表示に従い、「GoogleServicet.json」をダウンロードします。
5. プロジェクトフォルダ下にある「android/app」フォルダの直下に移動させます。
6. Firebase用のSDKを導入します。プロジェクトレベルのbuild.gradle（android/build.gradle）
とアプリレベルの build.gradle（android/app/build.gradle）に次の内容を追記します。

//list[main_connectfirebase1][プロジェクトレベルのbuild.gradle]{
  buildscript {
     repositories {
         // ...
     }

     dependencies {
         // ...
         classpath 'com.google.gms:google-services:3.2.1'   // new
     }
  }
//}

//list[main_connectfirebase2][アプリレベルのbuild.gradle]{
  dependencies {
  ...
  }
  ...
  // Add to the bottom of the file
  apply plugin: 'com.google.gms.google-services'
//}

== データベースの作成
1. 左のペインより「開発」→「Database」を選択。
2. 「データベースの作成」を選択。
3. 次の選択肢が表示されるので、「テストモードで開始」を選択し、有効にするボタンを選択。
　・ロックモードで開始
　・テストモードで開始
4. 「＋コレクションを追加」を選択し、コレクションIDを決定します。アプリ名に紐づけておくのが
　　分かりやすいと思うので、「kasikari-memo」とします。
5. コレクションの作成画面に遷移します。試しに次のようなコレクションを作成します。

//table[firebase-document][作成するコレクション]{
フィールド	タイプ	値
--------------------------------------------------------------
lendorrent	String	lend
name	String	借りた人です
loan	String	本
date	timestamp	2018/10/8
//}

== pubspec.yamlの変更
1. 「pubspec.yaml」を開き、次のように変更を加えます。

//list[pubspec-connectfirebase][pubspec.yamlの変更]{
  dependencies:
    flutter:
      sdk: flutter
    cloud_firestore: ^0.7.3     # new
//}

2. コンソール画面から次のコマンドを入力します。

//cmd{
flutter packages get
//}

以上で、Firebaseとの連携の準備は完了です。
