= 機能実装の進め方について
//comment{
  実装機能の進め方については、「10develop_intro」に記入し、「1111develop_display」の
  ファイル自体を削除する方針。ただし、記載内容を一部１２に取り込む必要があるので、一旦保留で。
//}



コードを書くにあたり、プロジェクト作成時に生成された、「main.dart」ファイルの中身を一度全て消し
次のコードを書いてみましょう。


//list[main_display][main.dart]{
  import 'package:flutter/material.dart';

  void main() => runApp(new MyApp());

  class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return new MaterialApp(
            title: ("貸し借りメモタイトル"),
            home: new Scaffold(
              appBar: new AppBar(
                title: new Text("貸し借りメモタイトル"),
              ),
              body: new Center(
                  child:new Text(
                      "貸し借りメモですよ"
                  )
              )
            )
      );
    }
  }

//}

== コードの説明

//list[main_display1][main.dart]{
  import 'package:flutter/material.dart';

  void main() => runApp(new MyApp());
  class MyApp extends StatelessWidget {
　
  }
//}
今回はステートレスなページを作成するのでStatelessWidgetを継承します。

//list[main_display2][main.dart]{
import 'package:flutter/material.dart';

void main() => runApp(new MyApp());
class MyApp extends StatelessWidget {
  Widget build(BuildContext context) {
      return new MaterialApp(
          ....
          );
        }
      }
//}
早速出て来ましね、Widget型のbuildメソッドです。
StatelessWidget（今回はMyAppが相当）が基本的には呼び出すメソッドになります。
これは他のWidgetを返す役割を果たします。
コードを見ていただくと分かるのですが、MaterialAppというWidgetを返しています。

MaterialAppはマテリアルデザインを使用するためのクラスとなっており、
まずはじめに呼び出すクラスになります。
アプリのタイトルであったり、最初の遷移先のページなどを決めることができます。

//list[main_display3][main.dart]{

  import 'package:flutter/material.dart';

  void main() => runApp(new MyApp());

  class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return new MaterialApp(
            title: ("貸し借りメモタイトル"),
            home: new Scaffold(
              appBar: new AppBar(
                title: new Text("貸し借りメモタイトル"),
              ),
              body: new Center(
                  child:new Text(
                      "貸し借りメモですよ"
                  )
              )
            )
      );
    }
  }

//}

こまめにインテンドを揃えてあげないとかっこの数でエラーが発生しますので落ち着いて対処して行きましょう。

さて、MaterialAppの中身に移って行きます。
MaterialAppのプロパティ「title:」はアプリ自体のタイトル、「home:」は最初に表示するページの情報を記載します。

homeの次に書かれているのはScaffoldクラスで画面全体のレイアウトを表示するクラスになります。
「appBar:」で画面上部に表示する情報の設定が行えます。今回はAppBarクラスを呼び出しタイトルを表示しています。
「body:」では画面の主要コンテンツとして表示したい情報の設定が行えます。

今回は画面真ん中に文字を表示したい為,Centerクラスを呼び出しています。
Centerのプロパティ「child:」にTextクラスを呼び出し「"貸し借りメモですよ"」と表示させます。

この状態でアプリの起動を行うと次の画面が表示されると思います。
