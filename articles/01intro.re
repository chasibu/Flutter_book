= FlutterとFirebaseを知ろう

== Flutter

オープンソースのモバイルアプリケーションフレームワークです。

特徴は次のとおりです。

 * 対応言語はDart
 * Hot Reload対応
 * AndroidやiOSが開発可能なマルチプラットフォーム対応
 * 開発元はGoogle

====[column] Dart

Googleによって開発されたWebプログラミング言語です。

位置付けとしてはJavaScriptの代替となる言語として作られました。
JavaScriptやJavaに記法が似ており、どちらを使ったことがある方には始めやすい言語だと思います。

====[/column]

=== 他のマルチクロスプラットフォーム（ReactNative,Xamarin）と比較

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
ReactNativeとは対応数は同じです。

//comment{
  引用元：https://qiita.com/amay077/items/dff88e7ce6868615a9bb
//}

== Firebase

FirebaseはGoogleが運営するBaaSです。

BaaS（backend as a service）とは、サーバーサイドプログラミング不要でデータベースや認証機能、プッシュ通知などを行ってくれるサービスです。

今回は、「Cloud Firestore」（※2018年8月現在、β版のみ提供）というクエリと自動スケーリング機能を兼ね備えたリアルタイムデータベースを使用します。
