=  入力画面の実装

この章では貸し借り情報の入力を画面を作成します。
次のデータを入力できるようにします。

 * 貸したのか、借りたのか
 * 誰から?
 * 何を?
 * いつまで?

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter8}

== 入力画面の作成

入力画面を作成して必要な設定をします。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input1][main.dart]{
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
...
}

class List extends StatefulWidget {
...
}

class _MyList extends State<List> {
...
}

/*---------- Add Start ----------*/
class InputForm extends StatefulWidget {
  @override
  _MyInputFormState createState() => _MyInputFormState();
}

class _FormData {
  String borrowOrLend = "borrow";
  String user;
  String stuff;
  DateTime date = DateTime.now();
}

class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('かしかり入力'),
        actions: <Widget>[
          IconButton(
              icon: Icon(Icons.save),
              onPressed: () {
                print("保存ボタンを押しました");
              }
          ),
          IconButton(
            icon: Icon(Icons.delete),
            onPressed: () {
              print("削除ボタンを押しました");
            },
          ),
        ],
      ),
      body: SafeArea(
        child:
        Form(
          key: _formKey,
          child: ListView(
            padding: const EdgeInsets.all(20.0),
            children: <Widget>[

                RadioListTile(
                  value: "borrow",
                  groupValue: _data.borrowOrLend,
                  title: Text("借りた"),
                  onChanged: (String value){
                    print("借りたをタッチしました");
                  },
                ),

                RadioListTile(
                    value: "lend",
                    groupValue: _data.borrowOrLend,
                    title: Text("貸した"),
                    onChanged: (String value) {
                      print("貸したをタッチしました");
                    }
                ),
                TextFormField(
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.person),
                    hintText: '相手の名前',
                    labelText: 'Name',
                  ),
                ),

                TextFormField(
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.business_center),
                    hintText: '借りたもの、貸したもの',
                    labelText: 'loan',
                  ),
                ),

                Padding(
                  padding: const EdgeInsets.only(top:8.0),
                  child: Text("締め切り日：${_data.date.toString().substring(0,10)}"),
                ),
                RaisedButton(
                  child: const Text("締め切り日変更"),
                  onPressed: (){
                     print("締め切り日変更をタッチしました");
                  },
                ),
              ],
            ),
          ),
        ),
      );
    }
}
/*----------- Add End -----------*/
//}

入力画面を作成しました。
本来であれば次の画像のような画面が表示されるはずですが、これを実行しているタイミングでは確認することができません。

次の項目の画面遷移を作ってこの画面を確認してみましょう。

//image[input][入力画面の作成][scale=0.7]{
//}

=== 入力画面の解説

画面遷移を作成する前に簡単にこの入力画面について解説をします。

ユーザの入力によって表示が変化するので、@<code>{StatefulWidget}クラスを継承していきます。

==== @<code>{_FormData}クラス
入力する変数をまとめて管理するクラスです。

 * borrowOrLend → 貸したか借りたか
 * user       → 誰に貸したのか、借りたのか
 * stuff       → 何を貸したのか、借りたのか
 * date       → 締め切り日

==== @<code>{IconButton}
保存ボタンと削除ボタンを表示します。
機能の実装は後ほど行う為、ボタンが押された後にコンソール画面にボタンを押した旨の表示をしています。

他のIconは次のURLをご覧ください。

@<href>{https://docs.flutter.io/flutter/material/Icons-class.html}

==== @<code>{Form}
Webと同じようにFormを使ってデータの入力画面を作成します。

@<code>{key: _formKey}は、フォーム全体に対する制御を行うものであり、後ほど実装する入力チェックに利用します。

このKeyを使うことで簡単に複数のWidgetをコントロールすることができます。

==== フォームの構成

@<code>{RadioListTile}でラジオボタンを作成します。

「貸したのか、借りたのか」の情報を入力します。
この段階では、タッチしてもボタンは切り替りは有効化されていません。

@<code>{TextFormField}でテキストの入力画面を作成します。

 * 貸した、借りた相手の名前
 * 貸し借りした物の名前

この段階では、入力画面のみを作成しており、まだ、データの取り出し等は行えません。

== 一覧画面から入力画面への画面遷移

一覧画面から入力画面への画面遷移を作成します。

先ほど作成した一覧画面の新規作成ボタンにコードを追加します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input2][main.dart]{
  class _MyList extends State<List> {

    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
            title: const Text("リスト画面"),
        ),
        body: Padding(
          ...
        ),
        floatingActionButton: FloatingActionButton(
            child: const Icon(Icons.check),
            onPressed: () {
              print("新規作成ボタンを押しました");
              /*---------- Add Start ----------*/
              Navigator.push(
                context,
                MaterialPageRoute(
                    settings: const RouteSettings(name: "/new"),
                    builder: (BuildContext context) => InputForm()
                ),
              );
              /*----------- Add End -----------*/
            }
        ),
      );
    }
  }
//}

一覧画面から登録画面への画面遷移を作成しました。

次の画像で赤枠で囲われたボタンを押すと前の項目で作成した入力画面を開くことができるので試してみましょう。

//image[add][一覧画面で押すボタン][scale=0.7]{
//}

=== 入力画面への画面遷移の説明

Navigatorという機能を使って、画面遷移を実装します。

Navigatorを使うことで画面遷移を簡単に行うことができます。
基本的には次の２つを使って画面遷移を行います。

 * push
次のページを指定して移動します。

 * pop
表示されているページを閉じて、前に表示していた画面を描画します。


新規登録ボタン選択後、@<code>{Navigator.push()}を使用し、画面の遷移機能を実装しています。

==== MaterialPageRoute

 * @<code>{settings:}は、ルーティングの設定を行います。
 * @<code>{builder:}は、どこのクラスに遷移するのかを設定します。

== ラジオボタンの有効化

ラジオボタンを有効化するためにコードを修正します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input3][main.dart]{
  class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  /*---------- Add Start ----------*/
  void _setLendOrRent(String value){
    setState(() {
      _data.borrowOrLend = value;
    });
  }
  /*----------- Add End -----------*/

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        ...
      ),
      body: SafeArea(
        child:
          Form(
              key: _formKey,
              child: ListView(
                padding: const EdgeInsets.all(20.0),
                children: <Widget>[

                RadioListTile(
                  value: "borrow",
                  groupValue: _data.borrowOrLend,
                  title: Text("借りた"),
                  onChanged: (String value){
                    print("借りたをタッチしました");
                    /*---------- Add Start ----------*/
                    _setLendOrRent(value);
                    /*----------- Add End -----------*/
                  },
                ),

                RadioListTile(
                  value: "lend",
                  groupValue: _data.borrowOrLend,
                  title: Text("貸した"),
                  onChanged: (String value) {
                    print("貸したをタッチしました");
                    /*---------- Add Start ----------*/
                    _setLendOrRent(value);
                    /*----------- Add End -----------*/
                  }
                ),
                ...
              ],
            ),
          ),
      ),
    );
  }
}
//}

ラジオボタンをタッチすると切り替えができるので試してみましょう。

//image[button][ラジオボタン][scale=0.7]{
//}

=== ラジオボタン有効化の説明

ボタンを押した時に@<code>{onChanged:}が発火します。

@<code>{_data.borrowOrLend}に押された情報を入れることで表示を切り替えることができます。

== 入力チェック機能

テキストフォームで入力された文字のチェック機能を作成します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input4][main.dart]{

class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        ...
      ),
      body: SafeArea(
        child:
          Form(
              key: _formKey,
              child: ListView(
                padding: const EdgeInsets.all(20.0),
                children: <Widget>[
                ...

                TextFormField(
                    decoration: const InputDecoration(
                      icon: const Icon(Icons.person),
                      hintText: '相手の名前',
                      labelText: 'Name',
                    ),
                    /*---------- Add Start ----------*/
                    onSaved: (String value) {
                      _data.user = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '名前は必須入力項目です';
                      }
                    },
                    initialValue: _data.user,
                    /*----------- Add End -----------*/
                ),

                TextFormField(
                  decoration: const InputDecoration(
                      icon: const Icon(Icons.business_center),
                      hintText: '借りたもの、貸したもの',
                      labelText: 'loan',
                    ),
                    /*---------- Add Start ----------*/
                    onSaved: (String value) {
                      _data.stuff = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '借りたもの、貸したものは必須入力項目です';
                      }
                    },
                    initialValue: _data.stuff,
                    /*----------- Add End -----------*/
                  ),
                  ...
              ],
            ),
          ),
      ),
    );
  }
}
//}

空データのときに保存ボタンを押してみましょう。次のような画面になります。

//image[verify][入力チェック機能][scale=0.7]{
//}

=== 入力チェック機能説明

@<code>{TextFormField}に対して、入力チェック機能を実装していきます。

 * @<code>{validator:}で入力欄が空欄のときにエラー文を返すように設定します。
 * @<code>{onSaved:}で@<code>{_data}の各プロパティに対して、値の代入を行ないます。

 次の章で設定した関数を使っていきます。

== 日付選択画面作成

日付の選択画面を作成します。

日付ダイアログの応答を受け取るために非同期処理を使っていきます。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

//list[main_input5][main.dart]{
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
/*---------- Add Start ----------*/
import 'dart:async';
/*----------- Add End -----------*/

class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  /*---------- Add Start ----------*/
  Future <DateTime> _selectTime(BuildContext context) async {
    final DateTime picked = await showDatePicker(
      context: context,
      initialDate: _data.date,
      firstDate: DateTime(_data.date.year - 2),
      lastDate: DateTime(_data.date.year + 2)
    );
    return picked;
  }
  /*----------- Add End -----------*/

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        ...
      ),
      body: SafeArea(
        child:
          Form(
              key: _formKey,
              child: ListView(
                padding: const EdgeInsets.all(20.0),
                children: <Widget>[
                ...
                RaisedButton(
                  child: const Text("締め切り日変更"),
                  onPressed: (){
                    print("締め切り日変更をタッチしました");
                    /*---------- Add Start ----------*/
                    _selectTime(context).then((time){
                      if(time != null && time != _data.date){
                        setState(() {
                          _data.date = time;
                        });
                      }
                    });
                    /*----------- Add End -----------*/
                  },
                ),
              ],
            ),
          ),
      ),
    );
  }
}

//}

「締め切り日変更」と書かれたボタンを押してみましょう。

//image[time][日付選択画面作成][scale=0.7]{
//}

=== 日付選択画面作成説明

「締め切り日変更」と書かれたボタンを押すと時刻入力するために@<code>{_selectTime()}を呼び出します。

Fluuterがデフォルトで用意している、日時を入力するための@<code>{showDatePicker()}という関数を使用します。

==== showDatePicker()

この関数の戻り値はFuture型となっており、これは非同期処理を行うときに使用します。
そのため、async/awaitを利用し、非同期処理を実現しております。
そのため、ファイルの初めに@<code>{import 'dart:async'}”が追加になっているので、
忘れずに追加しましょう。

 * @<code>{initialDate:}で初期値の日付を設定します。
 * @<code>{firstDate:}で最小の日付を設定します。今回は２年前を設定しました。
 * @<code>{lastDate:}で最大の日付を設定します。今回は２年後を設定しました。
