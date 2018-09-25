= Flutterをサクッと動かしてみよう

この章では、サンプルコードをそのまま動かして、Flutterでアプリを開発する流れを学んでいきます。

== Flutterの始め方

1. Android Studioを開き、「Start a new Flutter project」をクリックします。

//image[flutter1][Flutterの始め方][scale=0.8]{
//}

もしくは「File > New > New Flutter Project」をクリックします。

//image[flutter2][Flutterの始め方][scale=0.6]{
//}

2. 「Flutter Application」を選択し、「Next」をクリックします。

//image[flutter3][Flutter Application][scale=0.8]{
//}

3. どこのフォルダに生成するのか確認されます。問題なければ「Next」をクリックします。

//image[flutter4][Flutter FilePath][scale=0.8]{
//}

4. 「Set the package name」画面では特に変更を加えずに、「Finish」をクリックします。

//image[flutter5][Flutter package Name][scale=0.8]{
//}

5. プログラムを書くための環境が起動しました。これで準備は完了です。
次の項目でAndroid Stduioを使ったことのない方向けに機能を簡単に説明します。

//image[flutter6][プログラム画面全体][scale=0.8]{
//}

== Android Studio 機能解説

簡単にですが、Android Studioにどのような機能があり、どの部分を触るのか今回必要となる部分に限ってですが、説明します。

//image[androidstudio1][Android Studio][scale=0.9]{
//}

=== ファイル選択

FlutterではiOSとAndroidを同時に開発できるためOSごとにフォルダがあり、それぞれに設定できます。

また、libフォルダ内にFlutterの開発につかう、「main.dart」ファイルがあります。
開発で変更する際にはパスを指定されるのでここを変更するのだと覚えておきましょう。

=== エディタ

Flutterのコードなど編集します。

=== Flutter構成

Flutterの構成を確認することができます。

Flutterの特徴として、コードで描画するViewを作成します。
このタブをみるとどのWidgetで構成されてるのか一目で分かります。

=== プログラム実行

Flutterのコードを実行する時に使用します。
デバッグモードにしたり、デプロイするデバイスを選択します。

=== エミュレータ

エミュレータを作成できます。
「Androidエミュレータの設定」のコラムで紹介します。

=== 実行ログ

プログラムを実行中にでたログを確認できます。

== Flutterを実行しよう

実機のAndroidにFlutterを実行させる手順を紹介します。
実機がない場合は「Androidエミュレータの設定」を確認してエミュレータで行いましょう。

1. 実機のAndroidを開発者モードに切り替える。デバイスごとに異なるので検索してください。

2. Androidの設定メニューから「開発者向けオプション > USBデバッグ」を有効にします。

//image[device1][USBデバッグ有効にする][scale=0.6]{
//}

3. 「２」までの設定が完了した状態でPCとUSBでつなぐとこのようなダイアログが表示されます。
「このコンピュータは常に許可する」にチェックをいれ「OK」を押します。
このダイアログが出ないとUSBのドライバーが足りないか設定が間違っている可能性があります。

//image[device2][USBデバッグの許可][scale=0.6]{
//}

4. 問題なければ、Android Studioを確認するとデバイス名が表示されます。
緑色の再生ボタンをクリックするとビルドが開始されしばらくするとプログラムが実行されます。

//image[deviceDeploy1][デプロイ][scale=0.8]{
//}

5. 実行するとこのような画面が表示されます。これで動作確認完了です。

//image[device3][実行例][scale=0.6]{
//}

=====[column] Androidエミュレータの設定

1. AndroidStudioを開き、Androidシミュレータの設定を行います。
     画面上部にある、「AVD Manager」のアイコンを選択します。
//image[Android_emu1][「AVD Manager」のアイコン][scale=0.6]{
//}

2. 表示された画面にある「＋Create Virtual Device...」のボタンを選択します。

3. デバイス選択画面が表示されるので「Nexus 5X」を選択し、右下の「Next」ボタンを選択します。
     ※基本的にどれ選んでも問題ないと思うのですが、今回動作確認を行なったデバイスがNexus 5Xだったため、これを選択しています。
//image[Android_emu2][「AVD Manager」のアイコン][scale=0.6]{
//}
4. OSのバージョン選択画面が表示されますが、「Android 8.1」を選択し、右下の「Next」ボタンを押下します。
//image[Android_emu3][「AVD Manager」のアイコン][scale=0.6]{
//}
5. 設定の確認画面が出てきますが、特に変更することなく、右下の「Finish」を選択します。
//image[Android_emu4][「AVD Manager」のアイコン][scale=0.6]{
//}
6. 再生ボタンを選択し、デバイスを起動させます。
//image[Android_emu5][「AVD Manager」のアイコン][scale=0.6]{
//}
7. Nexus 5Xが画面に表示されれば、成功です。画面横にある×ボタンを選択して、エミュレータを終了させます。
//image[Android_emu6][「AVD Manager」のアイコン][scale=0.6]{
//}
====[/column]

=====[column] iphoneエミュレータの設定

1. AndroidStudioを開き、iPhoneシミュレータの設定を行います。
     画面上部にある、「<No devices>」を選択し、「Open iOS Simulator」を選択します。
//image[iPhone_emu1][「AVD Manager」のアイコン]{
//}

2. しばらくすると、次の画像のようにiphoneが表示されます。
//image[iPhone_emu2][「AVD Manager」のアイコン]{
//}

3. 終了する場合には、”Simulator”から"Quit Simulator"を選択して終了させます。
//image[iPhone_emu3][「AVD Manager」のアイコン]{
//}


====[/column]

=====[column] iOSエミュレータの設定

1. 画面上部にある、「<no devices>」と表示されているアイコンを選択します。

2. 「Open iOS Simulator」を選択します。

3. iphoneが表示されれば成功です。画面横にある×ボタンを選択して、エミュレータを終了させます。
//image[iphone_menu][メニュー画面][scale=0.6]{
//}


====[/column]

=====[column] ホットリロード

FlutterにはHot Reloadという、アプリ実行中に変更を反映させるためにアプリを停止させることなく、効率よくアプリ開発ができる機能があります。

次の画像は、「Hello World!」から「Flutter」と文字をプログラム上で変更する例です。
文字を変更してプログラムを保存すると1秒後には画像にあるようにアプリの表示が更新されました。

通常であれば数十秒から数分かかるプログラムの更新がすぐできるので非常に効率よくプログラムを作成できるのが伝わると思います。

//image[hotreload][Hot Reload（文字変更）][scale=0.6]{
//}

====[/column]
