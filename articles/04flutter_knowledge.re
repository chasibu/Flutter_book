= Flutterの基礎知識

== Flutterアプリの構造について

FlutterではWidgetという、オブジェクトを組み合わせることでUIを簡単に作成することができます。
どんなUIも全てWidgetで管理されており、入力フォームや、ボタン、全体のレイアウトに到るまで全て
Widgetから成り立っており、これらを組み合わせることで、アプリのUIを作成します。

新規アプリ作成時のサンプルデモを元に、どのようにWidgetが組み合わさってUIを構成しているのかを次の画像で表現します。

//list[samplecode][main.dart]{
import 'package:flutter/material.dart';

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Flutter Demo',
      theme: new ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: new MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;

  void _incrementCounter() {
    setState(() {
      _counter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text(widget.title),
      ),
      body: new Center(
        child: new Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            new Text(
              'You have pushed the button this many times:',
            ),
            new Text(
              '$_counter',
              style: Theme.of(context).textTheme.display1,
            ),
          ],
        ),
      ),
      floatingActionButton: new FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: new Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}
//}

//image[Widget][Widgetの組合せについて][scale=0.9]{
//}

Widgetには必須パラメータやそのWidget自体が保有しているメソッドや返り値などが存在します。

本書では、「貸し借り記録メモ」を作成するに必要なパラメータやメソッドについて解説等は行いますが、
本書を超えて自分オリジナルのアプリを作る場合には、公式リファレンス（@<href>{https://flutter.io/widgets/}）
をご覧ください。

== Stateless？Stateful？

Flutterでアプリを作成していると「Stateless」と「Stateful」というワードが頻繁に出てきます。

ステータスが変化するかしないかでどちらを選ぶのかが変わります。といわれてもいまいち理解しずらいので具体例を出してみます。

=== Stateless

 * スプラッシュ画面（起動画面）
 * 規約情報表示等の固定で変化のない画面

=== Stateful

 * リスト表示
 * 入力画面
 * ネットからデータを取ってくるなど可変表示する画面

簡単な分類ですが、固く構えずにイメージをつかんで試していきましょう。

== プライベート変数について

Flutterでは変数や関数を宣言する時に、頭に"_"をつけるとその変数や関数はプライベートな値として扱われます。
