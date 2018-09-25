= FlutterとFirebaseを知ろう

== Flutter

オープンソースのモバイルアプリケーションフレームワークです。

特徴は次のとおりです。

 * 対応言語はDart
 * Hot Reload対応
 * AndroidやiOSが開発可能なマルチプラットフォーム対応
 * 開発元はGoogle

//image[flutter][Flutterロゴ][scale=0.4]{
//}

====[column] Dart

Googleによって開発されたWebプログラミング言語です。

JavaScriptの代替となる言語として作られました。
JavaScriptやJavaに記法が似ており、どちらかの言語を使ったことがある方には始めやすい言語だと思います。

====[/column]

=== ReactNativeやXamarinとの比較

//table[comparison][他のマルチクロスプラットフォームとの比較]{
対応プラットフォーム	Flutter/Dart	ReactNative/JavaScript	Xamarin/.NET
--------------------------------------------------------------
Android	○	○	○
iOS	○	○	○
デスクトップ（Win）	-	-	○
デスクトップ（Mac）	-	-	○
Web（フロントエンド）	○	○	○
Web（バックエンド）	○	○	-
//}

デスクトップアプリが作れるXamarinに比べると対応プラットフォーム数は劣りますが、
ReactNativeと対応プラットフォーム数は同じです。

== Firebase

FirebaseはGoogleが運営するBaaSです。

BaaS（backend as a service）とは、サーバーサイドのプログラミングが不要でデータベースや認証機能、プッシュ通知などを行ってくれるサービスです。

今回は、「Cloud Firestore」（※2018年9月現在、β版のみ提供）というクエリと自動スケーリング機能を兼ね備えたリアルタイムデータベースを使用します。
