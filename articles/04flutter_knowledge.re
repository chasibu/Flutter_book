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

//image[Widget][Widgetの組合せについて]{
//}

Widgetには必ず値をいれなくてはいけない、パラメータであったり、そのWidget自体が保有しているメソッドや返り値などが存在します。
本書では、「貸し借り記録メモ」を作成するに必要なパラメータやメソッドについて解説等は行いますが、
本書を超えて自分オリジナルのアプリを作る場合には、公式リファレンス（@<href>{https://flutter.io/widgets/}）
を参照して頂くと、作成が捗ります。

== statelessなページとstatefullなページについて
Flutterではstatelessなページとstatefullなページを作成し、アプリを作成していきます。
登録画面は入力を伴い、ユーザからの入力や表示するの内容が他のデータに依存する
（たとえば、データベースから登録してある情報を表示するなど）ページをステートフルなページと呼びます。
それとは対象に、いつアクセスしても表示する内容が変わらないようなページをステートレスなページと呼びます。


== プライベート変数について
Flutterではプライベート変数を宣言する時に、変数名の前に"_"をつけます。
