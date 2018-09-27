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

@<code>{RadioListTile}で「貸したのか、借りたのか」の情報を入力しています。
まだ、この段階では、ボタンは有効化されていません。

@<code>{TextFormField}を使用し、次の入力を実現しています。

 * 貸した、借りた相手の名前
 * 貸し借りした物の名前

この段階では、入力画面のみを作成しており、まだ、データの取り出し等は行えません。

== 入力画面への画面遷移

入力画面への画面遷移をします。

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

一覧画面から登録画面への画面遷移機能の実装になります。
新規登録ボタン選択後、@<code>{Navigator.push()}を使用し、画面の遷移機能を実装しています。
@<code>{settings:}では、ルーティングの設定、@<code>{builder:}では、どこのクラスに遷移するのかを設定します。

== ラジオボタンの有効化
//list[main_input3][main.dart]{
  class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  void _setLendOrRent(String value){
    setState(() {
      _data.borrowOrLend = value;
    });
  }

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
@<code>{RadioListTile}において、ボタンを押した後の実際の値の代入の処理は
@<code>{onChanged:}の中にある@<code>{_setLendorRent()}にて実装しています。
@<code>{_data.borrowOrLend}に対して値の代入を行います。



== 入力チェック機能
//list[main_input4][main.dart]{

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

貸し借りした相手の名前、貸し借りしたものの名前を入力する@<code>{TextFormField}に対して、
入力チェック機能とを実装しています。@<code>{onSaved:}にて、@<code>{_data}の各プロパティに対して、値の代入を行なっています。
また、@<code>{validator:}を使用し、登録時に空欄である場合、エラー文を返すように設定しています。

== 日付選択
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
@<code>{RaisedButton}の@<code>{onPressed:}のおいて、時刻入力するための関数、@<code>{_selectTime()}を呼び出します。
@<code>{_selectTime()}では、Fluuterがデフォルトで用意している、日時を入力するための@<code>{showDatePicker()}という
関数を使用します。

この関数の戻り値はFuture型となっており、これは非同期処理を行うときに使用します。
非同期処理とは、ある関数を呼び出した時に、関数の結果を返す前に、関数を終了し、結果を返せる状態になったら
その結果を返す処理のことです。

Flutterでは、@<code>{async/await}を利用し、非同期処理を実現します。
非同期処理を行いたい場合は@<code>{async}を使用します。@<code>{async}で呼び出された関数は自身の処理が完了する前に
後続の処理を行います。また、非同期処理の動作完了を待ちたい場合には@<code>{await}を使用します。
今回では、非同期処理を行いつつ、日付入力の画面が表示されるのを待つため、@<code>{async/await}を使用します。

また、@<code>{async/await}を使用するには、@<code>{import 'dart:async'}”を追記する必要があるので忘れずに追加しましょう。
@<code>{initialDate:}は初期値の値、@<code>{firstDate:}が入力できる日付の最小値、@<code>{lastDate:}が入力できる値の最大値となっております。
