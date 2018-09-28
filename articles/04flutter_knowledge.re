= Flutterの基礎知識を学ぼう

== Flutterアプリの構造について

Flutterでは入力フォームや、ボタン、全体のレイアウトのWidgetを組み合わせることで、アプリのUIを作成します。

新規アプリ作成時のサンプルコードから表示に関わる部分を切り出し、どのようにWidgetが組み合わさってUIを構成しているのかまとめました。

//list[samplecode][main.dart]{
   Scaffold(
      appBar: AppBar(
        title: Text("Flutter Demo Home Page"),//タイトル
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
           Text('You have pushed the button this many times:'),//本文
            new Text(//カウント数字表示
              '$_counter',
              style: Theme.of(context).textTheme.display1,
            ),
          ],
        ),
      ),
      floatingActionButton: new FloatingActionButton(//追加ボタン表示
        child: new Icon(Icons.add),//Addアイコン表示
      ),
    );
//}

//image[Widget][Widgetの組合せ][scale=0.9]{
//}

Widgetには必須パラメータやそのWidget自体が保有しているメソッドや返り値などが存在します。

本書を超えて自分オリジナルのアプリを作る場合には、公式リファレンス（@<href>{https://flutter.io/widgets/}）に非常に優れたドキュメントやサンプルコードがあるのでぜひご覧ください。

== Stateless？Stateful？

Flutterでアプリを作成していると「Stateless」と「Stateful」というワードが頻繁に出てきます。

ステートが変化するかしないかでどちらを選ぶのかが変わります。といわれてもいまいち理解しずらいので具体例を出してみます。

=== Stateless

 * スプラッシュ画面（起動画面）
 * 規約情報表示等の固定で毎回変化のない画面

=== Stateful

 * リスト表示
 * 入力画面
 * ネットからデータを取ってくるなど表示が可変する画面

簡単な分類ですが、固く構えずにイメージをつかんで試していきましょう。

== プライベート変数について

Flutterでは変数や関数を宣言する時に、頭に"_"をつけるとその変数や関数はプライベートなものとして扱われます。

== パッケージ

パッケージを使用すると、簡単にアプリを拡張することができます。
Flutterでは、次のURLでパッケージを検索することができます。

@<href>{https://pub.dartlang.org/flutter/packages}
