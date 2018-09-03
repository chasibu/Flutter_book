= DartとFlutterとFirebaseについて

== Dartについて
Google社によって開発されたwebプログラミング言語になります。
位置付けとしてはJavaScriptの代替となる言語として作られました。
その為、JavaScriptもしくはJavaとかをやっていると比較的始めやすい言語なのかなと思います。
また、2018年２月にはDart2発表され、本書でもDart2を使用して行きます。
//comment{
余裕があったら何が変更になったのかを記載する。
//}


== Flutterについて
こちらもGoogle社が開発した、オープンソースのモバイルアプリケーションフレームワークになります。特徴は以下の通りとなります。

 * 対応言語はDart
 * hotreload対応
 * Android,iOSが開発可能なマルチプラットフォーム対応


=== 他のマルチクロスプラットフォーム(ReactNative,Xamarin)との比較を表にまとめました。

|対応プラットフォーム|Flutter/dart|ReactNative/javascript|Xamarin/.NET|
|---|---|---|---|
|Android||||
|iOS||||
|デスクトップ(Win)||||
|デスクトップ(Mac)||||
|Web(フロントエンド)||||
|Web(バックエンド)||||

デスクトップアプリが作れるXamarinに比べると対応プラットフォーム数は劣りますが、ReactNativeとは対応数は同じです。

//comment{
引用元：https://qiita.com/amay077/items/dff88e7ce6868615a9bb
//}

== Firebaseについて
こちらも、Google社が提供しているサービスになります。
Baas(backend as a service)と呼ばれるサービスの一つで、今までサーバサイドで行なっていた処理をインターネットを経由してクラウドサービスとして提供してくれうサービスです。
Firebaseは様々なサービスを提供しており、ストレージや認証機能を一つのサービスとして提供してくれます。今回は、「Cloud Firestore」(※2018年8月現在、β版のみ提供)というクエリと自動スケーリング機能を兼ね備えたリアルタイムデータベースを使用いたします。
