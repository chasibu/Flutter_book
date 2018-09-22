=  登録画面の実装
この章では貸借り情報の入力を画面を作成します。
具体的には次のデータを入力できるようにします。

 * 貸したのか、借りたのか
 * 誰から、誰になのか
 * 何を貸借りしたのか
 * 期限はいつなのか


登録画面は入力を伴い、ユーザからの入力や表示するの内容が他のデータに依存する（たとえば、データベースから登録してある情報を表示するなど）
ページをステートフルなページと呼びます。

Flutterではそのようなステートフルなページを作成する場合、「StatefulWidget」クラスを継承しクラスの作成を行います。

それでは、前章でコードを書いた「main.dart」ファイルにコードを書いて行きましょう。

//list[main_input][main.dart][Dart]{
  import 'package:flutter/material.dart';
  import 'dart:async';

  void main() => runApp(new MyApp());

  class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return new MaterialApp(
            title: ("貸し借りメモタイトル"),
            home: InputForm(),
      );
    }
  }

  class InputForm extends StatefulWidget {
    @override
    _MyInputFormState createState() => new _MyInputFormState();
  }

  class _formData {
    String lendorrent;
    String user;
    String loan;
    DateTime date;
  }

  class _MyInputFormState extends State<InputForm> {
    final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
    _formData _data = new _formData();
    String lendorrent = "rent";
    DateTime date = new DateTime.now();

    void _setLendorRent(String value){
      setState(() {
        lendorrent = value;
      });
    }

    Future <Null> _selectTime(BuildContext context) async {
      final DateTime picked = await showDatePicker(
          context: context,
          initialDate: date,
          firstDate: new DateTime(2018),
          lastDate: new DateTime(2020)
      );

      if(picked != null && picked != date){
        setState(() {
          date = picked;
          print(date);
        });
      }
    }

    @override
    Widget build(BuildContext context) {

      Widget titleSection;
      titleSection = Scaffold(
        appBar: AppBar(
          title: const Text('かしかりめも'),
          actions: <Widget>[
            // action button
            IconButton(
              icon: Icon(Icons.save),
              onPressed: () {
                print("保存ボタンを押しました");
                }
      ),
            IconButton(
              icon: Icon(Icons.delete),
              onPressed: (){
                print("削除ボタンを押しました");
    },
            )
          ],
        ),
        body: new SafeArea(
          child:
          new Form(
            key: this._formKey,
            child: new ListView(
              padding: const EdgeInsets.all(20.0),
              children: <Widget>[

                RadioListTile(
                  value: "rent",
                  groupValue: lendorrent,
                  title: new Text("借りた"),
                  onChanged: (String value){
                    _setLendorRent(value);
                    print("借りたに設定しました");
                  },
                ),

                RadioListTile(
                    value: "lend",
                    groupValue: lendorrent,
                    title: new Text("貸した"),
                    onChanged: (String value) {
                      _setLendorRent(value);
                      print("貸したに設定しました");
                    }
                ),
                new TextFormField(
                  //controller: _myController,
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.person),
                    hintText: '相手の名前',
                    labelText: 'Name',
                  ),
                  onSaved: (String value) {
                    this._data.user = value;
                  },
                  validator: (value) {
                    if (value.isEmpty) {
                      return '名前は必須入力項目です';
                    }
                  },
                  initialValue: _data.user,
                ),

                new TextFormField(
                  //controller: _myController2,
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.business_center),
                    hintText: '借りたもの、貸したもの',
                    labelText: 'loan',
                  ),
                  onSaved: (String value) {
                    this._data.loan = value;
                  },
                  validator: (value) {
                    if (value.isEmpty) {
                      return '借りたもの、貸したものは必須入力項目です';
                    }
                  },
                  initialValue: _data.loan,
                ),

                new Text("締め切り日：${date.toString()}"),
                new RaisedButton(
                    child: new Text("締め切り日変更"),
                    onPressed: (){_selectTime(context);}
                ),
              ],
            ),
          ),
        ),
      );
      return titleSection;
    }
  }
//}


== コードの説明

//list[main_input1][main.dart]{
  import 'package:flutter/material.dart';
  import 'dart:async';

  void main() => runApp(new MyApp());

  class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return new MaterialApp(
            title: ("貸し借りメモタイトル"),
            home: InputForm(),
      );
    }
  }
//}

前章との大きな変更点はMaterialAppのhomeに対して直接Widgetを設定するのではなく
InputForm()というクラスを用意して入力画面を表示しているところです。

また、importするパッケージも増えていますので、忘れずに追加しておきましょう。

//list[main_input2][main.dart]{
  import 'package:flutter/material.dart';
  import 'dart:async';

  void main() => runApp(new MyApp());

  class MyApp extends StatelessWidget {
  ...
  }

class InputForm extends StatefulWidget {
  @override
  _MyInputFormState createState() => new _MyInputFormState();
}

class _formData {
  String lendorrent;
  String user;
  String loan;
  DateTime date;
}

class _MyInputFormState extends State<InputForm> {
}
//}

InputFormクラスをStatefulWidgetを継承して作成しているのがポイントになります。この中で、
実際の実装を行う、_MyInputFormStateの作成を行います。
次の行で作成している_formDataクラスは入力する変数を格納するために作成しています。
それぞれ

 * lendorrent → 貸したか借りたか
 * user       → 誰に貸したのか、借りたのか
 * loan       → 何を貸したのか、借りたのか
 * date       → 締め切り日

 に対応しています。

//list[main_input3][main.dart]{
   import 'package:flutter/material.dart';
   import 'dart:async';

   void main() => runApp(new MyApp());

   class MyApp extends StatelessWidget {
   ...
   }
  ...

class _MyInputFormState extends State<InputForm> {

  final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
  _formData _data = new _formData();
  String lendorrent = "rent";
  DateTime date = new DateTime.now();

  ...

  @override
  Widget build(BuildContext context) {

    Widget titleSection;
    titleSection = Scaffold(
      appBar: AppBar(
        title: const Text('かしかりめも'),
        actions: <Widget>[
          // action button
          IconButton(
            icon: Icon(Icons.save),
            onPressed: () {
              print("保存ボタンを押しました");
              }
          ),
          IconButton(
            icon: Icon(Icons.delete),
            onPressed: (){
              print("削除ボタンを押しました");
              },
          )
        ],
      ),
      body: new SafeArea(
        child:
        new Form(
          key: this._formKey,
          child: new ListView(
            padding: const EdgeInsets.all(20.0),
            children: <Widget>[

              RadioListTile(
                value: "rent",
                groupValue: lendorrent,
                title: new Text("借りた"),
                onChanged: (String value){
                  _setLendorRent(value);
                  print("借りたに設定しました");
                },
              ),

              RadioListTile(
                  value: "lend",
                  groupValue: lendorrent,
                  title: new Text("貸した"),
                  onChanged: (String value) {
                    _setLendorRent(value);
                    print("貸したに設定しました");
                  }
              ),
              new TextFormField(
                decoration: const InputDecoration(
                  icon: const Icon(Icons.person),
                  hintText: '相手の名前',
                  labelText: 'Name',
                ),
              ),

              new TextFormField(
                decoration: const InputDecoration(
                  icon: const Icon(Icons.business_center),
                  hintText: '借りたもの、貸したもの',
                  labelText: 'loan',
                ),
              ),

              new RaisedButton(
                  color: Colors.blue,
                  child: new RichText(
                      text: new TextSpan(
                          children: <TextSpan>[
                            new TextSpan(
                              text: '日付変更',
                              style: new TextStyle(color: Colors.white),
                            )
                          ]
                      )
                  ),
                  onPressed: (){_selectTime(context);}
              ),
              new Text("締め切り日：${date.toString()}"),
            ],
          ),
        ),
      ),
    );
    return titleSection;
  }
}
//}

buildメソッドの前に、いくつかメソッドがあるのですが、先にbuildメソッドの中身から解説します。

このメソッドの中身は次の図のとおりとなっております。

※説明に必要な部分のみ抜粋して表示しております。
//image[MyInputForm_build][buildクラスの中身]{
//}

図のような入れ子状にWidget等を配置し、アプリを作って行きます。次から各ポイントごとに解説を記載して行きます。

//list[input_scafold][appBar:について]{
appBar: AppBar(
  title: const Text('かしかりめも'),
  actions: <Widget>[
    // action button
    IconButton(
      icon: Icon(Icons.save),
      onPressed: () {
        print("保存ボタンを押しました");
        }
),
    IconButton(
      icon: Icon(Icons.delete),
      onPressed: (){
        print("削除ボタンを押しました");
},
    )
  ],
),
//}

ここでは後に実装する保存機能と削除機能のためのボタンを配置しています。
onPressed：の中にボタンを押した後の処理を記載できるのですが、
正しく動いていることを確認するために、ボタンが押された後にコンソール画面にボタンを押した旨の表示をしています。


//list[input_appBar:][appBar:について]{
appBar: AppBar(
  title: const Text('かしかりめも'),
  actions: <Widget>[
    // action button
    IconButton(
      icon: Icon(Icons.save),
      onPressed: () {
        print("保存ボタンを押しました");
        }
),
    IconButton(
      icon: Icon(Icons.delete),
      onPressed: (){
        print("削除ボタンを押しました");
},
    )
  ],
),
//}


//list[input_RadioListTile][RadioListTileについて]{
  RadioListTile(
    value: "rent",
    groupValue: lendorrent,
    title: new Text("借りた"),
    onChanged: (String value){
      _setLendorRent(value);
      print("借りたに設定しました");
    },
  ),

  RadioListTile(
      value: "lend",
      groupValue: lendorrent,
      title: new Text("貸した"),
      onChanged: (String value) {
        _setLendorRent(value);
        print("貸したに設定しました");
      }
  ),
//}

valueで実際に設定する値、groupValueに値の格納先の変数名を記載します。
groupValueの値は事前に宣言しておくのがポイントになります。
今回の例では「class _MyInputFormState」の先頭で「String lendorrent = "rent";」
と宣言しています。
ボタンを押した後の実際の値の代入の処理は「onChanged:」の中にある「_setLendorRent()」にて実装しています。

//list[input_setLendorRent][_setLendorRentについて]{
  void _setLendorRent(String value){
    setState(() {
      lendorrent = value;
    });
  }
//}

ここで、先ほど設定した、groupValueのlendorrentに対して値の代入を行います。

//list[input_TextFormField][TextFormFieldについて]{
  new TextFormField(
    decoration: const InputDecoration(
      icon: const Icon(Icons.business_center),
      hintText: '借りたもの、貸したもの',
      labelText: 'loan',
    ),
  ),
//}

文字入力可能なテキストフォームを作成します。「decoration:」でラベルやアイコンの設定を行うことができます。

//list[input_RaiseButton][RaiseButtonについて]{
new RaisedButton(
    color: Colors.blue,
    child: new RichText(
        text: new TextSpan(
            children: <TextSpan>[
              new TextSpan(
                text: '日付変更',
                style: new TextStyle(color: Colors.white),
              )
            ]
        )
    ),
    onPressed: (){_selectTime(context);}
),
//}

日付を入力するためのボタンの設定をしています。ボタンを押すと先ほど解説をいったん飛ばした
「selectTime()」に処理が遷移します。

//list[input_selectTime][selectTimeについて]{
  Future <Null> _selectTime(BuildContext context) async {
    final DateTime picked = await showDatePicker(
        context: context,
        initialDate: date,
        firstDate: new DateTime(2018),
        lastDate: new DateTime(2020)
    );

    if(picked != null && picked != date){
      setState(() {
        date = picked;
        print(date);
      });
    }
  }
//}

日時の入力を行うために、用意されている「showDatePicker」という関数を使用します。
この関数の戻り値はFuture型となっており、これは非同期処理を行うときに使用します。
そのため、async/awaitを利用し、非同期処理を実現しております。
nitialDate:は初期値の値、firstDate:が入力できる日付の最小値、lastDate:が入力できる値の最大値となっております。
（今回の例だと2018／01／01 〜 2020／01／01が入力できます。）
dateに対して日時の代入はsetState()で実現しています。


この状態でアプリを起動すると次のような画面が立ち上がり、無事に文字の入力が可能になっていると思います。
