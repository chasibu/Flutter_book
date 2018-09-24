= 一覧画面の実装



== pubspec.yamlの変更
1. 「pubspec.yaml」を開き、次のように変更を加えます。

//list[pubspec-connectfirebase][pubspec.yamlの変更]{
  dependencies:
    flutter:
      sdk: flutter
    cloud_firestore: ^0.7.3     # new
//}

2. コンソール画面から次のコマンドを入力します。

//cmd{
flutter packages get
//}

以上で、Firebaseとの連携の準備は完了です。


この章ではFirestoreに保存されている貸し借りデータを一括で表示する機能の実装を行います。
今まで、「_MyInputFormState()」を呼び出し、データ入力画面を表示させていましたが、
ここでは、「_List」を作成し、一覧の表示を行います。

この章でも同様に「main.dart」にコードを記述していきます。

//list[main_show][main.dart]{
  import 'package:flutter/material.dart';
  import 'dart:async';
  import 'package:cloud_firestore/cloud_firestore.dart';

  void main() => runApp(MyApp());

  class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return MaterialApp(
        title: "かしかりメモ",
        home: List(),
      );
    }
  }

  class _formData {
    String borrowOrLend = "borrow";
    String user;
    String loan;
    DateTime date = new DateTime.now();
  }

  class InputForm extends StatefulWidget {
    @override
    _MyInputFormState createState() => _MyInputFormState();
  }

  class _MyInputFormState extends State<InputForm> {
    final _formData _data = _formData();
    final GlobalKey<FormState> _formKey = GlobalKey<FormState>();

    void _setLendOrRent(String value){
      setState(() {
        _data.borrowOrLend = value;
      });
    }

    Future <Null> _selectTime(BuildContext context) async {
      final DateTime picked = await showDatePicker(
          context: context,
          initialDate: _data.date,
          firstDate: DateTime(_data.date.year - 2),
          lastDate: DateTime(_data.date.year + 2)
      );

      if(picked != null && picked != _data.date){
        setState(() {
          _data.date = picked;
        });
      }
    }

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
              onPressed: (){
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
                    _setLendOrRent(value);
                    print("借りたに設定しました");
                  },
                ),

                RadioListTile(
                    value: "lend",
                    groupValue: _data.borrowOrLend,
                    title: Text("貸した"),
                    onChanged: (String value) {
                      _setLendOrRent(value);
                      print("貸したに設定しました");
                    }
                ),
                TextFormField(
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

                TextFormField(
                  decoration: const InputDecoration(
                    icon: const Icon(Icons.business_center),
                    hintText: '借りたもの、貸したもの',
                    labelText: 'loan',
                  ),
                  onSaved: (String value) {
                    _data.loan = value;
                  },
                  validator: (value) {
                    if (value.isEmpty) {
                      return '借りたもの、貸したものは必須入力項目です';
                    }
                  },
                  initialValue: _data.loan,
                ),

                Padding(
                  padding: const EdgeInsets.only(top:8.0),
                  child: Text("締め切り日：${_data.date.toString()}"),
                ),
                RaisedButton(
                  child: const Text("締め切り日変更"),
                  onPressed: (){_selectTime(context);},
                ),
              ],
            ),
          ),
        ),
      );
    }
  }

  class List extends StatefulWidget {
    @override
    _MyList createState() => _MyList();
  }

  class _MyList extends State<List> {

    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
          title: Text("リスト画面"),
        ),
        body: Padding(
          padding: const EdgeInsets.all(8.0),
          child: StreamBuilder<QuerySnapshot>(
              stream: Firestore.instance.collection('kasikari-memo').snapshots(),
              builder: (BuildContext context, AsyncSnapshot<QuerySnapshot> snapshot) {
                if (!snapshot.hasData) return const Text('Loading...');
                return ListView.builder(
                  scrollDirection: Axis.vertical,
                  itemCount: snapshot.data.documents.length,
                  padding: const EdgeInsets.only(top: 10.0),
                  itemBuilder: (context, index) =>
                      _buildListItem(context, snapshot.data.documents[index]),
                );
              }
          ),
        ),
        floatingActionButton: new FloatingActionButton(
            child: new Icon(Icons.check),
            onPressed: () {
              print("新規作成ボタンを押しました");
            }),
      );
    }

    Widget _buildListItem(BuildContext context, DocumentSnapshot document){
      return Card(
        child: Column(
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              ListTile(
                leading: const Icon(Icons.android),
                title: Text("【 " + (document['borrowOrLend'] == "lend"?"借":"貸") +" 】"+ document['stuff']),
                subtitle: Text('期限 ： ' + document['date'].toString() + '\n'
                    "相手 ： " + document['user']),
              ),
              ButtonTheme.bar(
                  child: ButtonBar(
                    children: <Widget>[
                      FlatButton(
                          child: const Text("へんしゅう"),
                          onPressed: ()
                          {
                            print("編集ボタンを押しました");
                          }
                      ),
                    ],
                  )
              ),
            ]
        ),
      );
    }
  }
//}
この章からアプリを起動した時に表示する画面を「_MyList」に変更しており、「MyApp」の「home:」の値も変更しております。

==　コードの説明
//list[main_show1][main.dart]{
class _List extends StatefulWidget {
  @override
  _MyList createState() => new _MyList();
}

class _MyList extends State<_List> {

  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("一覧"),
      ),
      body: Padding(
          padding: const EdgeInsets.all(8.0),
          child: new StreamBuilder<QuerySnapshot>(),
      ),
      floatingActionButton: new FloatingActionButton(
          child: new Icon(Icons.check),
          onPressed: () {
            print("新規作成ボタンを押しました");
          }),
    );
  }
}
//}

一覧画面はFirebaseから毎回データを取得し、画面に表示しています。その為、Firebaseのデータの状態により
表示される画面の内容が変化する為、StatefulWidgetクラスを継承し、クラスを作成します。

今回も、「_MyList」クラスの「build」メソッド内で「Scaffold」を使用し、画面の描写を行います。
「body:」にはPaddingを代入し、表示する貸し借り情報に対してpaddingを設けます。
実際にここの数値を変更するとどのような変化が生じるのかは次の画像をみてください。

//comment{
  画像
//}

Firebaseからデータを取得し、表示する機能は「StreamBuilder<QuerySnapshot>()」の中で実装します。

また、「floatingActionButton:」は次の章で説明する、新規作成ボタンになります。
ここでは、新規作成画面への実装は行わないので、いったん、ボタンを押したら「新規作成ボタンを押しました」と
表示するようにしておきます。


//list[main_show2][main.dart]{
  class _MyList extends State<_List> {

  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("一覧"),
      ),
      body: Padding(
          padding: const EdgeInsets.all(10.0),
          child: new StreamBuilder<QuerySnapshot>(
              stream: Firestore.instance.collection('kasikari-memo').snapshots(),
              builder: (BuildContext context, AsyncSnapshot<QuerySnapshot> snapshot) {
                if (!snapshot.hasData) return const Text('Loading...');
                return new ListView.builder(
                  scrollDirection: Axis.vertical,
                  itemCount: snapshot.data.documents.length,
                  padding: const EdgeInsets.only(top: 10.0),
                  itemBuilder: (context, index) =>
                      _buildListItem(context, snapshot.data.documents[index]),
                );
              }
          ),
      ),
    ...
  }
}
//}

「StreamBuilder」は「_buildListItem」を使用し、Firebaseから取得したデータを表示させます。
「stream:」は、非同期に接続しているstreamを代入し使用します。
非同期に接続するデータはFirestoreから「Firestore.instance.collection('コレクション名').snapshots()」
で入手することが可能です。
「builder:」内では「snapshot」がデータを持っていない状態（Firestoreからデータを取得している状態）では
「Loading...」と表示し、データを一件でも取得し始めたら、ListViewの形式で表示しています。
データを取得した時のListView.builderのプロパティは次のとおりです。

//table[ListView.builder][ListView.builderのプロパティ]{
プロパティ 値 説明
--------------------------------------------------------------
scrollDirection:  Axis.vertical スクロールの方向を決める。垂直方向に画面をスクロールできるように設定。
itemCount:  snapshot.data.documents.length  表示するアイテムの数を決める。snapshotから取得したドキュメントの数を設定。
padding:  const EdgeInsets.only(top: 10.0)  一番初めに表示されるアイテムのパディングを決定。
itemBuilder:  (context, index) => _buildListItem(context, snapshot.data.documents[index]) 次の項目にて説明
//}

//list[main_show3][main.dart]{

  class _MyList extends State<_List> {

  Widget build(BuildContext context) {
    ...
      body: Padding(
        ...
                return new ListView.builder(
                  ...
                  itemBuilder: (context, index) =>
                      _buildListItem(context, snapshot.data.documents[index]),
                );
              }
          ),
      ),
  }

  Widget _buildListItem(BuildContext context, DocumentSnapshot document){
  return new Card(
    child: new Column(
        mainAxisSize: MainAxisSize.min,
        children: <Widget>[
          ListTile(
            leading: const Icon(Icons.android),
            title: Text(document['name']),
            subtitle: Text(document['loan']),
          ),
          new ButtonTheme.bar(
              child: new ButtonBar(
                children: <Widget>[
                  new FlatButton(
                    child: const Text("へんしゅう"),
                    onPressed: ()
                      {
                        print("編集ボタンを押しました");
                      }
                      ),
                ],
              )
          ),
        ]
    ),
  );
  }
//}

「_buildListItem」クラスでは引数として「DocumentSnapshot document」を設定し、「ListTile」を使用して
一件ごとの貸し借りの情報を表示しています。貸し借りの相手と貸し借りした品を表示するように設定します。
また、Columnの下に「ButtonTheme.bar」を設け、のちの章で作成する編集機能用のボタンを設置します。
ここではいったん、ボタンを押すとログに「編集ボタンを押しました」と表示するように設定します。

この状態で、アプリを実行すると次のように、テスト入力したデータがリストとなって表示されます。

//comment{
  画像
//}
