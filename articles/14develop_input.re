=  登録画面の実装

この章を完了すると下記のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter8}

この章では貸借り情報の入力を画面を作成します。
具体的には次のデータを入力できるようにします。

 * 貸したのか、借りたのか
 * 誰から、誰になのか
 * 何を貸借りしたのか
 * 期限はいつなのか


登録画面は入力を伴い、ユーザからの入力や表示するの内容が他のデータに依存する為
（たとえば、データベースから登録してある情報を表示するなど）
statefullなページとして作成します。

Flutterではそのようなページを作成する場合、@<code>{StatefulWidget}クラスを継承しクラスの作成を行います。


== 画面の実装

//list[main_input1][main.dart]{
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
...
}

class List extends StatefulWidget {
...
}

class _MyList extends State<List> {
...
}

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
          )
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
//}

@<code>{InputForm}クラスを@<code>{StatefulWidget}を継承して作成しているのがポイントになります。この中で、
実際の実装を行う、@<code>{_MyInputFormState}の作成を行います。

@<code>{_formData}クラスは入力する変数を格納するために作成しています。
それぞれ

 * borrowOrLend → 貸したか借りたか
 * user       → 誰に貸したのか、借りたのか
 * stuff       → 何を貸したのか、借りたのか
 * date       → 締め切り日

 に対応しています。

@<code>{_MyInputFormState}内では、まず、@<code>{appBar:}にて@<code>{IconButton}を使用し、保存ボタンと削除ボタンを
設定します。機能の実装は後ほど行う為、ボタンが押された後にコンソール画面にボタンを押した旨の表示をしています。

@<code>{body:}においては、@<code>{Form}を利用し、データの入力画面を作成します。
@<code>{key: _formKey}では、フォーム全体に対する制御を行うものであり、後ほど、実装する入力チェックに利用します。
@<code>{RadioListTile}で「貸したのか、借りたのか」の情報を入力しています。
まだ、この段階では、ボタンは有効化されていません。

@<code>{TextFormField}を使用し、
 * 貸した、借りた相手の名前
 * 貸し借りした物の名前
の入力を実現しています。この段階では、入力画面のみを作成しており、まだ、データの取り出し等は行えません。


== 登録後の画面遷移
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
              Navigator.push(
                context,
                MaterialPageRoute(
                    settings: const RouteSettings(name: "/new"),
                    builder: (BuildContext context) => InputForm()
                ),
              );
            }
        ),
      );
    }
  }
//}

一覧画面から登録画面への画面遷移機能の実装になります。
新規登録ボタン選択後、@<code>{Navigator.push()}を使用し、画面の遷移機能を実装しています。
@<code>{settings:}では、ルーティングの設定、@<code>{builder:}では、どこのクラスに遷移するのかを設定します。

== RadioListTile有効化
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
                    _setLendOrRent(value);
                  },
                ),

                RadioListTile(
                  value: "lend",
                  groupValue: _data.borrowOrLend,
                  title: Text("貸した"),
                  onChanged: (String value) {
                    print("貸したをタッチしました");
                    _setLendOrRent(value);
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



== 入力チェック機能追加
//list[main_input4][main.dart]{

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
                ...

                TextFormField(
                    decoration: const InputDecoration(
                    icon: const Icon(Icons.person),
                    hintText: '相手の名前',
                    labelText: 'Name',
                    ),
                    onSaved: (String value) {
                      _data.user = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '名前は必須入力項目です';
                      }
                    },
                    initialValue: _data.user,
                ),

                TextFormField(
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.business_center),
                    hintText: '借りたもの、貸したもの',
                    labelText: 'loan',
                    ),
                    onSaved: (String value) {
                      _data.stuff = value;
                    },
                    validator: (value) {
                      if (value.isEmpty) {
                        return '借りたもの、貸したものは必須入力項目です';
                      }
                    },
                      initialValue: _data.stuff,
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
import 'dart:async';

class _MyInputFormState extends State<InputForm> {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  final _FormData _data = _FormData();

  Future <DateTime> _selectTime(BuildContext context) async {
  final DateTime picked = await showDatePicker(
      context: context,
      initialDate: _data.date,
      firstDate: DateTime(_data.date.year - 2),
      lastDate: DateTime(_data.date.year + 2)
  );
  return picked;
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
                ...
                RaisedButton(
                  child: const Text("締め切り日変更"),
                  onPressed: (){
                    print("締め切り日変更をタッチしました");
                    _selectTime(context).then((time){
                      if(time != null && time != _data.date){
                        setState(() {
                          _data.date = time;
                        });
                      }
                    });
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
そのため、async/awaitを利用し、非同期処理を実現しております。
そのため、ファイルの初めに@<code>{import 'dart:async'}”が追加になっているので、
忘れずに追加しましょう。

@<code>{initialDate:}は初期値の値、@<code>{firstDate:}が入力できる日付の最小値、@<code>{lastDate:}が入力できる値の最大値となっております。

== データ保存
//list[main_input6][main.dart]{
class _MyInputFormState extends State<InputForm> {

  @override
  Widget build(BuildContext context) {
  DocumentReference _mainReference;
  _mainReference = Firestore.instance.collection('kasikari-memo').document();

  return Scaffold(
  appBar: AppBar(
    title: const Text('かしかり入力'),
    actions: <Widget>[
      IconButton(
          icon: Icon(Icons.save),
          onPressed: () {
            print("保存ボタンを押しました");
            if (_formKey.currentState.validate()) {
              _formKey.currentState.save();
              _mainReference.setData(
                  {
                    'borrowOrLend': _data.borrowOrLend,
                    'user': _data.user,
                    'stuff': _data.stuff,
                    'date': _data.date
                  });
              Navigator.pop(context);
            }
          }
      ),
      IconButton(
        ...
      )
    ],
  ),
  ...
  )
  }
}
//}

Firestoreにデータを登録するために、@<code>{Firestore.instance.collection('コレクション名').document();}
を使用し、インスタンスを生成します。

保存ボタンを選択後、@<code>{_formKey}を使用し、入力チェックを行います。
入力チェクを行い、問題なければ、@<code>{_mainReference.setData()}を使用し、Firestoreへデータの登録を行います。

「"キー":"値"」の形式で、Firestoreへデータの登録を行い、４つのデータを保存したら、@<code>{Navigator.pop}を利用し
元の一覧画面に戻ります。

この状態で、アプリを実行すると、一覧画面が表示され、右下の新規作成ボタンを押すことで、新規作成画面に遷移し、新規登録が可能になります。
