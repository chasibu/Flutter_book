= 表示機能の実装
まずはじめに、文字の表示機能の実装を行います。
FlutterはJavaと同様にmain（）からプログラムが開始します。
今回はmain（）からMyApp（）を実行し、文字の表示を行います。
文字の表示だけを行うような、どのようなリクエストが来ても、同じレスポンスを返答するページを作成します。
このようなページをステートレスなページと呼びます。


コードを書くにあたり、プロジェクト作成時に生成された、「main.dart」ファイルの中身を一度全て消し
次のコードを書いてみましょう。


//list[main_display1][main.dart][Dart]{

import 'package:flutter/material.dart';

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text("貸し借りメモタイトル"),
      ),
      body: new Center(
        child: new Column(
          children: <Widget>[
            new Text(
            "貸し借りメモですよ"
            )
          ]
        )
      )
    );
    },
}

//}

## コードの説明

  Widget build(BuildContext context) {


    return new Scaffold(
      appBar: new AppBar(
        title: new Text("貸し借りメモタイトル"),
      ),
      body: new Center(
        child: new Column(
          children: <Widget>[
            new Text(
            "貸し借りメモですよ"
      
